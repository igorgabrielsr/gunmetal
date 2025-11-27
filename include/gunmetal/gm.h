/**
 * @file gm.h
 * @brief Gunmetal Framework v0.1.0
 *
 * @details A minimal, modular game framework for 2D games.
 *
 * @version 0.1.0
 * @date 2025-11-27
 * @author Igor Gabriel
 *
 * LICENSE: Public Domain (Unlicense)
 */
#ifndef GM_H
#define GM_H

#ifdef __cplusplus
extern "C" {
#endif

/* ---- VERSION MACROS ---- */
#define GM_VERSION_MAJOR 0
#define GM_VERSION_MINOR 1
#define GM_VERSION_PATCH 0
#define GM_VERSION_STRING "0.1.0"

/* ---- GM_IMPL: Auto-select backends BEFORE including modules ---- */
#ifdef GM_IMPL
// Auto-select default backends if not specified
#if !defined(GM_PLATFORM_X11_IMPL) && !defined(GM_PLATFORM_WAYLAND_IMPL)
#define GM_PLATFORM_X11_IMPL
#endif

#if !defined(GM_GRAPHICS_GL_IMPL) && !defined(GM_GRAPHICS_VK_IMPL)
#define GM_GRAPHICS_GL_IMPL
#endif

#if !defined(GM_AUDIO_PULSE_IMPL) && !defined(GM_AUDIO_ALSA_IMPL)
#define GM_AUDIO_PULSE_IMPL
#endif

#define GM_INPUT_IMPL
#define GM_TIME_IMPL
#endif

/* ---- CORE MODULES ---- */
#include "gunmetal/core/gm_platform.h"

/* ---- VERSION INFO ---- */
static inline const char *gm_get_version(void) { return GM_VERSION_STRING; }

static inline void gm_get_version_parts(int *major, int *minor, int *patch) {
  if (major)
    *major = GM_VERSION_MAJOR;
  if (minor)
    *minor = GM_VERSION_MINOR;
  if (patch)
    *patch = GM_VERSION_PATCH;
}

#ifdef __cplusplus
}
#endif

#endif // GM_H
