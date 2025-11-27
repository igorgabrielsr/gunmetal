# Gunmetal

Minimal game framework for 2D games in C.

[![License](https://img.shields.io/badge/license-Unlicense-blue.svg)](LICENSE)

---

## Quick Start

```c
#define GM_IMPL
#include "gunmetal/gm.h"

int main() {
    gm_platform_desc_t p = {
        .window_title = "Game",
        .window_width = 800,
        .window_height = 600
    };
    
    gm_platform_init(&p);
    
    while (gm_platform_running()) {
        gm_platform_poll_events();
    }
    
    gm_platform_shutdown();
}
```

```bash
make && make run
```

---

## Modules

**Core** — Platform, Graphics, Audio, Input, Time  
**Extensions** — Camera, Sprite, Math, Collision, Particles

---

## License

Public Domain ([Unlicense](LICENSE))

---

Inspired by [Sokol](https://github.com/floooh/sokol), [Gunslinger](https://github.com/MrFrenik/gunslinger), and [stb](https://github.com/nothings/stb).
