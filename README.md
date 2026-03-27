# Uranium Shell (ush) 

**ush** is a minimal Unix-like shell written in C.

![Status](https://img.shields.io/badge/status-active-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)

## Features

- Proper backslash escaping (`\\` → `\`, `\n`, `\t`)
- Builtin `echo` (fixes macOS BSD echo `\c` bug)
- Tokenization supporting single and double quotes
- Pipe (`|`) support

## Quick Start
 
### 1. Clone the repository (Download)

```bash
git clone https://github.com/selimozturk13/ush.git
cd ush
```
### 2. Build

#### With CMake + Ninja (Recommended & Faster)

```bash
cmake -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
ninja -C build
```
#### With Cmake and Makefile 

```bash
mkdir -p build && cd build
cmake .. -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release
make
```

### 3. Run

```bash
# If you used Ninja
./build/ush

# If you used Makefile
./build/ush
```

## License

Uranium Shell (ush) is licensed under the **GNU General Public License v3.0 (GPLv3)**.

See [LICENSE](LICENSE) for details.