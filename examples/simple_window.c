/**
 * @file simple_window.c
 * @brief Simple X11 Window Example
 *
 * Demonstrates basic window creation with Gunmetal.
 */

// Define implementation flags BEFORE including headers
#define GM_IMPL
#define GM_PLATFORM_X11_IMPL

#include "gunmetal/gm.h"
#include <stdio.h>

int main(void) {
  printf("---- Gunmetal Simple Window ----\n");
  printf("Version: %s\n\n", gm_get_version());

  gm_platform_desc_t platform_desc = {
      .window_title = "Simple X11 Window",
      .window_width = 800,
      .window_height = 600,
      .window_resizable = true,
      .window_fullscreen = false,
  };

  if (!gm_platform_init(&platform_desc)) {
    fprintf(stderr, "Failed to initialize platform\n");
    return 1;
  }

  printf("Window created successfully!\n");
  printf("Press ESC to quit\n\n");

  while (gm_platform_running()) {
    gm_platform_poll_events();
    // Here you would typically do rendering
  }

  printf("Shutting down...\n");
  gm_platform_shutdown();

  return 0;
}
