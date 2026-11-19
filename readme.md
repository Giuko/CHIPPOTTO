# CHIPPOTTO

**CHIPPOTTO** is a [CHIP-8](https://en.wikipedia.org/wiki/CHIP-8) emulator written in C. It supports rendering output directly in the terminal as well as opening a dedicated graphical window using [raylib](https://github.com/raysan5/raylib).

## Features

- **Dual output backends:** Run in a standard terminal or open a dedicated window with raylib.
- **Input handling:** Supports keyboard input via raylib when graphical mode is enabled.
- **Written in C:** Lightweight and self-contained.

> **Note:** Terminal input is not currently supported; keyboard input is only available when running with raylib.

## Building

### Terminal Mode (Default)

Build without raylib to output directly to the terminal:

```sh
make
```
### Raylib Mode (Better supported)

Build with raylib:

```sh
make USE_RAYLIB=1
```
