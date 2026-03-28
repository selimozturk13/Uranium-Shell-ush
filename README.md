# Uranium Shell (ush) 

**ush** is a minimal Unix-like shell written in C.

![Status](https://img.shields.io/badge/status-active-brightgreen)
![Language](https://img.shields.io/badge/language-C-blue)

## Features

- Proper backslash escaping (`\\` → `\`, `\n`, `\t`)
- Builtin `echo` (fixes macOS BSD echo `\c` bug)
- Tokenization supporting single and double quotes
- Pipe (`|`) support

## Dependencies

Before building and running Uranium-Shell (ush), make sure the following dependencies are installed on your system:

- **GCC** – the GNU Compiler Collection for compiling C/C++ code.
- **CMake** – used to configure and generate build files.
- **Ninja** *(recommended)* or **Make** – build system for compiling the project.
- **readline-devel** – development libraries for command-line input editing and history support.

### Installation Examples

#### On Fedora / RHEL
```bash
sudo dnf install gcc cmake ninja-build make readline-devel
```

#### On Debian / Ubuntu
```bash
sudo apt update
sudo apt install build-essential cmake ninja-build libreadline-dev
```

#### On Arch Linux
```bash
sudo pacman -Syu gcc cmake ninja make readline
```

### Via Homebrew (macOS)
```bash
brew install gcc cmake ninja readline
```

## Quick Start

### 1. Clone the repository (Download)

```bash
git clone https://github.com/selimozturk13/Uranium-Shell-ush.git
cd Uranium-Shell-ush
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
./ush
```
## Tested Environments

Uranium-Shell (ush) has been tested on the following systems:

| OS / Distro        | Architecture | Compiler      | Build System       |
|:-------------------|:-------------:|:---------------:|:------------------:|
| macOS 13 Ventura        | x86_64      | clang 14.0.3    | CMake + Ninja     |
| Fedora 43          | x86_64      | gcc 15.2.1     | CMake + Make      |

## License

Uranium Shell (ush) is licensed under the **GNU General Public License v3.0 (GPLv3)**.

See [LICENSE](LICENSE) for details.