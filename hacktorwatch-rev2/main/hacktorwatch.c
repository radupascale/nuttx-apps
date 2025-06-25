/****************************************************************************
 * apps/examples/lab04si/lab04si.c
 *
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.  The
 * ASF licenses this file to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance with the
 * License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <nuttx/config.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <sys/boardctl.h>

#ifdef CONFIG_GRAPHICS_LVGL
#include <lvgl/lvgl.h>
#endif
/****************************************************************************
 * Private Functions
 ****************************************************************************/

#ifdef CONFIG_GRAPHICS_LVGL
static int lvgl_handler(int argc, char *argv[])
{
  while (1) {
    lv_timer_handler();
    usleep(20000);
  }

  return EXIT_FAILURE;
}
#endif

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: main
 *
 * Description:
 *
 * Input Parameters:
 *   Standard argc and argv
 *
 * Returned Value:
 *   Zero on success; a positive, non-zero value on failure.
 *
 ****************************************************************************/

int main(int argc, FAR char *argv[])
{
  int ret;
#ifdef CONFIG_GRAPHICS_LVGL
  lv_nuttx_dsc_t info;
  lv_nuttx_result_t result;
#endif

#ifdef CONFIG_GRAPHICS_LVGL
  lv_init();
  lv_nuttx_dsc_init(&info);

#ifdef CONFIG_LV_USE_NUTTX_LCD
  info.fb_path = "/dev/lcd0";
#endif

  lv_nuttx_init(&info, &result);

  if (result.disp == NULL) {
    LV_LOG_ERROR("lv_demos initialization failure!");
    return 1;
  }
#endif

#ifdef CONFIG_GRAPHICS_LVGL
  lv_obj_t *screen = lv_obj_create(NULL);
  lv_scr_load(screen);
  lv_obj_set_style_bg_color(lv_screen_active(), lv_color_hex(0x003a57), LV_PART_MAIN);

  /* Create a white label, set its text and align it to the center */

  lv_obj_t *label = lv_label_create(lv_screen_active());
  lv_label_set_text(label, "Hello!");
  lv_obj_set_style_text_color(lv_screen_active(), lv_color_hex(0xffffff), LV_PART_MAIN);
  lv_obj_align(label, LV_ALIGN_CENTER, 0, 0);
#endif

#ifdef CONFIG_GRAPHICS_LVGL
  ret = task_create("lvgl_handler", 110, 4096, lvgl_handler,
                    NULL);
#endif /* CONFIG_GRAPHICS_LVGL */

  while (1) {
    usleep(100000);
  }

#ifdef CONFIG_GRAPHICS_LVGL
  lv_disp_remove(result.disp);
  lv_deinit();
#endif

  return 0;
}
