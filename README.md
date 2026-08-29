# GBA Emu Switch

Homebrew emulator for the Game Boy Advance, targeting Nintendo Switch. No ROMs are bundled or distributed with this project — users must supply their own dumps.

## Status

Early-stage skeleton: boots, handles input, renders a scaled framebuffer, and loads a ROM file from disk. The core (`source/core/gba_core.cpp`) does not yet interpret ARM7TDMI instructions — CPU, PPU, APU, timers and DMA are still to be implemented.

## Build

CI is configured via GitHub Actions (`.github/workflows/build.yml`) using the `devkitpro/devkita64` container. Every push to `main` produces a `.nro` artifact.

Local builds require [devkitPro](https://devkitpro.org/) with the `switch-dev` package group installed:

```bash
export DEVKITPRO=/opt/devkitpro
make
```

## Usage

The emulator looks for a ROM at a fixed path:

```
sdmc:/switch/gba-emu-switch/rom.gba
```

No in-app file picker is implemented by design. Hold `+` and `-` together to exit.

## Project structure

```
source/
├── main.cpp                 # entry point, main loop
├── core/
│   ├── gba_core.h/.cpp      # emulation core (CPU/PPU/APU)
└── platform/
    ├── input_switch.h/.cpp  # controller → GBA button mapping
    └── video_switch.h/.cpp  # framebuffer scaling
```

## Roadmap

- ARM/Thumb CPU interpreter, validated against `jsmolka/gba-tests`
- PPU (video modes 0–5, tiles, sprites)
- APU (4 PSG channels + DMA audio) via libnx `audout`
- Timers, DMA, interrupts

## License

No copyrighted ROM data is included or distributed by this project.
