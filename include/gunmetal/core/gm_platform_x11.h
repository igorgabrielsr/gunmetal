/**
 * @file gm_platform_x11.h
 * @brief X11 Platform Implementation
 *
 * @details Pure X11 implementation - no graphics API dependencies.
 *
 * @version 0.1.0
 * @date 2025-11-27
 * @author Igor Gabriel
 *
 * LICENSE: Public Domain (Unlicense)
 */
#ifndef GM_PLATFORM_X11_H
#define GM_PLATFORM_X11_H

#ifdef __cplusplus
extern "C" {
#endif

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

typedef struct {
  Display *display;
  Window window;
  Atom wm_delete_window;
  bool running;
  gm_platform_desc_t desc;
} gm_platform_state_x11_t;

static gm_platform_state_x11_t _gm_platform_x11 = {0};

bool gm_platform_init(const gm_platform_desc_t *desc) {
  if (!desc)
    return false;

  memcpy(&_gm_platform_x11.desc, desc, sizeof(gm_platform_desc_t));

  // Open X11 display
  _gm_platform_x11.display = XOpenDisplay(NULL);
  if (!_gm_platform_x11.display) {
    fprintf(stderr, "[Platform/X11] Failed to open X11 display\n");
    return false;
  }

  int screen = DefaultScreen(_gm_platform_x11.display);
  Window root = RootWindow(_gm_platform_x11.display, screen);

  // Create window
  _gm_platform_x11.window = XCreateSimpleWindow(
      _gm_platform_x11.display, root, 0, 0, desc->window_width,
      desc->window_height, 0, BlackPixel(_gm_platform_x11.display, screen),
      BlackPixel(_gm_platform_x11.display, screen));

  if (!_gm_platform_x11.window) {
    XCloseDisplay(_gm_platform_x11.display);
    fprintf(stderr, "[Platform/X11] Failed to create window\n");
    return false;
  }

  // Select events
  XSelectInput(_gm_platform_x11.display, _gm_platform_x11.window,
               ExposureMask | KeyPressMask | KeyReleaseMask | ButtonPressMask |
                   ButtonReleaseMask | PointerMotionMask | StructureNotifyMask);

  // Set window properties
  XStoreName(_gm_platform_x11.display, _gm_platform_x11.window,
             desc->window_title);

  // Setup close protocol
  _gm_platform_x11.wm_delete_window =
      XInternAtom(_gm_platform_x11.display, "WM_DELETE_WINDOW", False);
  XSetWMProtocols(_gm_platform_x11.display, _gm_platform_x11.window,
                  &_gm_platform_x11.wm_delete_window, 1);

  // Size hints for non-resizable windows
  if (!desc->window_resizable) {
    XSizeHints hints = {0};
    hints.flags = PMinSize | PMaxSize;
    hints.min_width = hints.max_width = desc->window_width;
    hints.min_height = hints.max_height = desc->window_height;
    XSetWMNormalHints(_gm_platform_x11.display, _gm_platform_x11.window,
                      &hints);
  }

  // Map window
  XMapWindow(_gm_platform_x11.display, _gm_platform_x11.window);
  XFlush(_gm_platform_x11.display);

  _gm_platform_x11.running = true;
  return true;
}

void gm_platform_shutdown(void) {
  if (_gm_platform_x11.display) {
    if (_gm_platform_x11.window) {
      XDestroyWindow(_gm_platform_x11.display, _gm_platform_x11.window);
    }
    XCloseDisplay(_gm_platform_x11.display);
    _gm_platform_x11.display = NULL;
    _gm_platform_x11.window = 0;
  }
  _gm_platform_x11.running = false;
}

void gm_platform_poll_events(void) {
  if (!_gm_platform_x11.display)
    return;

  XEvent event;
  while (XPending(_gm_platform_x11.display) > 0) {
    XNextEvent(_gm_platform_x11.display, &event);

    switch (event.type) {
    case ClientMessage:
      if ((Atom)event.xclient.data.l[0] == _gm_platform_x11.wm_delete_window) {
        _gm_platform_x11.running = false;
      }
      break;

    case KeyPress: {
      KeySym keysym = XLookupKeysym(&event.xkey, 0);
      if (keysym == XK_Escape) {
        _gm_platform_x11.running = false;
      }
      break;
    }

    case ConfigureNotify:
      _gm_platform_x11.desc.window_width = event.xconfigure.width;
      _gm_platform_x11.desc.window_height = event.xconfigure.height;
      break;
    }
  }
}

bool gm_platform_running(void) { return _gm_platform_x11.running; }

void gm_platform_request_quit(void) { _gm_platform_x11.running = false; }

gm_platform_surface_t gm_platform_get_surface(void) {
  gm_platform_surface_t surface = {0};

  surface.native_handle.display = _gm_platform_x11.display;
  surface.native_handle.window = (void *)(uintptr_t)_gm_platform_x11.window;
  surface.native_handle.backend_type = GM_PLATFORM_BACKEND_X11;

  surface.width = _gm_platform_x11.desc.window_width;
  surface.height = _gm_platform_x11.desc.window_height;

  return surface;
}

gm_platform_backend_t gm_platform_get_backend_type(void) {
  return GM_PLATFORM_BACKEND_X11;
}

void gm_platform_set_title(const char *title) {
  if (_gm_platform_x11.display && _gm_platform_x11.window) {
    XStoreName(_gm_platform_x11.display, _gm_platform_x11.window, title);
  }
}

void gm_platform_get_size(uint32_t *width, uint32_t *height) {
  if (width)
    *width = _gm_platform_x11.desc.window_width;
  if (height)
    *height = _gm_platform_x11.desc.window_height;
}

void gm_platform_set_size(uint32_t width, uint32_t height) {
  if (_gm_platform_x11.display && _gm_platform_x11.window) {
    XResizeWindow(_gm_platform_x11.display, _gm_platform_x11.window, width,
                  height);
    _gm_platform_x11.desc.window_width = width;
    _gm_platform_x11.desc.window_height = height;
  }
}

#ifdef __cplusplus
}
#endif

#endif // GM_PLATFORM_X11_H
