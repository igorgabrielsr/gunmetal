/**
 * @file gm_platform.h
 * @brief Gunmetal Platform Abstraction
 *
 * @details Platform-agnostic window creation and event handling.
 *
 * @version 0.1.0
 * @date 2025-11-27
 * @author Igor Gabriel
 *
 * LICENSE: Public Domain (Unlicense)
 */
#ifndef GM_PLATFORM_H
#define GM_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

/* ---- TYPES ---- */

typedef enum {
  GM_PLATFORM_BACKEND_UNKNOWN = 0,
  GM_PLATFORM_BACKEND_X11,
  GM_PLATFORM_BACKEND_WAYLAND,
} gm_platform_backend_t;

typedef struct {
  const char *window_title;
  uint32_t window_width;
  uint32_t window_height;
  bool window_resizable;
  bool window_fullscreen;
} gm_platform_desc_t;

// Opaque native handle
typedef struct {
  void *display;
  void *window;
  uint32_t backend_type;
} gm_platform_native_handle_t;

// Surface info for graphics initialization
typedef struct {
  gm_platform_native_handle_t native_handle;
  uint32_t width;
  uint32_t height;
} gm_platform_surface_t;

/* ---- PLATFORM API ---- */

// Initialize platform
bool gm_platform_init(const gm_platform_desc_t *desc);

// Shutdown platform
void gm_platform_shutdown(void);

// Poll events
void gm_platform_poll_events(void);

// Check if running
bool gm_platform_running(void);

// Request quit
void gm_platform_request_quit(void);

// Get surface for graphics (backend-agnostic)
gm_platform_surface_t gm_platform_get_surface(void);

// Get current backend type
gm_platform_backend_t gm_platform_get_backend_type(void);

// Window operations
void gm_platform_set_title(const char *title);
void gm_platform_get_size(uint32_t *width, uint32_t *height);
void gm_platform_set_size(uint32_t width, uint32_t height);

/* ---- IMPLEMENTATION ---- */

#if defined(GM_PLATFORM_X11_IMPL)
#include "gm_platform_x11.h"
#elif defined(GM_PLATFORM_WAYLAND_IMPL)
#include "gm_platform_wayland.h"
#else
#if defined(__linux__)
#warning                                                                       \
    "No platform backend defined. Use GM_PLATFORM_X11_IMPL or GM_PLATFORM_WAYLAND_IMPL"
#endif
#endif

#ifdef __cplusplus
}
#endif

#endif // GM_PLATFORM_H
