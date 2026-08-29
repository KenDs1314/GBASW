# GBA Emu Switch

Emulador de Game Boy Advance para Nintendo Switch (homebrew), sin ninguna ROM
incluida. Compilado automáticamente vía GitHub Actions con el toolchain
devkitPro/devkitA64.

## Estado actual

Esto es un **esqueleto funcional**: compila, corre, muestra pantalla e input,
pero el core (`source/core/gba_core.cpp`) todavía es un placeholder — no
interpreta instrucciones ARM7TDMI reales todavía. Es la base sobre la que se
va agregando el CPU interpreter, PPU, APU, timers, etc.

## Cómo compilar (vía GitHub Actions, sin instalar nada local)

1. Subí este repo a GitHub (podés hacerlo entero desde el celular con la app
   o el sitio web de GitHub: "Add file" → "Upload files").
2. Cada `push` a `main` dispara el workflow en
   `.github/workflows/build.yml`, que:
   - Usa el contenedor oficial `devkitpro/devkita64` (ya trae devkitA64 +
     libnx instalados).
   - Corre `make`.
   - Sube el `.nro` resultante como **artifact** de la Action.
3. Andá a la pestaña **Actions** del repo → entrá al run más reciente →
   descargá el artifact `gba-emu-switch-nro` (es un `.zip` con el `.nro`
   adentro).

Si preferís dispararlo manualmente sin hacer push, el workflow también tiene
`workflow_dispatch`, así que podés lanzarlo a mano desde la pestaña Actions.

## Cómo probar en tu Switch

> Esto asume que ya tenés Homebrew Launcher instalado en una consola que vos
> mismo configuraste (fuera del alcance de este repo).

1. Copiá el `.nro` descargado a `sdmc:/switch/gba-emu-switch/` en la SD.
2. Dumpeá tu propia ROM (de un cartucho que poseas) y copiala como
   `sdmc:/switch/gba-emu-switch/rom.gba` — el nombre y ruta son fijos, no
   hay selector de archivo.
3. Abrí el Homebrew Launcher y lanzá "GBA Emu Switch".
4. Mantené `+` y `-` juntos para salir en cualquier momento.

## Estructura del proyecto

```
source/
├── main.cpp                 # entry point, loop principal
├── core/
│   ├── gba_core.h/.cpp       # core de emulación (CPU/PPU/APU van acá)
└── platform/
    ├── input_switch.h/.cpp   # mapeo de Joy-Con/Pro Controller -> botones GBA
    └── video_switch.h/.cpp   # escalado del framebuffer 240x160 a pantalla nativa
```

## Próximos pasos sugeridos

1. Implementar el **CPU interpreter** (ARM + Thumb) en `gba_core.cpp`,
   validando contra test ROMs libres como `jsmolka/gba-tests` (GitHub).
2. Implementar la **PPU** (modos de video 0–5, tiles, sprites).
3. **APU** (4 canales PSG + DMA de audio) usando la API `audout` de libnx.
4. Timers, DMA, IRQs.

## Licencia / legal

Este repositorio no incluye, ni incluirá, ninguna ROM ni material con
copyright. Cada usuario es responsable de usar únicamente ROMs dumpeadas de
cartuchos de su propiedad.
