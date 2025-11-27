/**
 * @file gm.h
 * @brief Gunmetal Framework v0.1.0
 *
 * @details TODO
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
#endif // __cplusplus

#endif // GM_H
