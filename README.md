# Uranium Shell (ush) 

**ush** is a minimal Unix-like shell written in C.

![Status](https://img.shields.io/badge/status-active-brightgreen?style=flat)
![Language](https://img.shields.io/badge/language-C-00599C?style=flat)
![Compliance](https://img.shields.io/badge/compliance-POSIX-FFD100?style=flat)
![Memory](https://img.shields.io/badge/memory-safe-32CD32?style=flat)
![License](https://img.shields.io/badge/license-GPLv3-007acc?style=flat)

## 💻 Compatibility & Environment  
This project is designed to be **platform-independent across Unix-like systems**, adhering to *POSIX standards*.

- **Development OS:** *macOS*  
- **Testing Environment:** Verified on **Fedora** (via *Podman container*)  
- **Standards:** Fully **POSIX compliant**  
- **Windows Support:** *Not natively supported.* Recommended to use **WSL2** or *Podman/Docker* for a seamless experience.

## Features

- Proper backslash escaping (`\\` → `\`, `\n`, `\t`)
- Builtin `echo` 
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

#### Via Homebrew (macOS)
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
| Fedora 43          | x86_64      | gcc 15.2.1     | CMake + Ninja    

## 🛡️ Memory Safety & Valgrind

This project is developed with a **strict focus on memory safety**. The codebase is verified to be free of any *"definitely lost"* or *"indirectly lost"* memory leaks.

The *"still reachable"* blocks reported by **Valgrind** are exclusively related to the internal implementation of the *readline* library.

### 📊 Summary

| Category                | Status        | Description |
|------------------------|--------------|-------------|
| **Definitely Lost**    | ✅ None       | No memory leaks caused by application logic |
| **Indirectly Lost**    | ✅ None       | No chained or dependent leaks detected |
| **Still Reachable**    | ⚠️ Expected   | Caused by *readline* internal static buffers |

### 📌 Details

- **Zero Leaks:** All memory allocated by the application logic is properly deallocated.  
- **Readline Artifacts:** *readline* and *add_history* use internal static buffers that persist until process termination.  
  These are **standard library behaviors** and do **not** indicate a flaw in the project's memory management.

## License

Uranium Shell (ush) is licensed under the **GNU General Public License v3.0 (GPLv3)**.

See [LICENSE](LICENSE) for details.
