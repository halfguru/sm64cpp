# AGENTS.md - Super Mario 64 C++ Port Project

This file contains the guidelines, build commands, and refactoring roadmap for AI agents working on this repository.

## 1. Project Overview & Architecture
* **Goal:** Port the C-based PC port of Super Mario 64 (`sm64plus`) to modern C++.
* **Base Codebase:** Unlicensed SM64 PC port (forked at `https://github.com/halfguru/sm64cpp`).
* **Graphics/Windowing Backend:** SDL2 + OpenGL + GLEW.
* **Build System:** Makefile (compiled under MinGW64 GCC/G++).

---

## 2. Environment & Tools
* **Shell:** Windows PowerShell (pwsh) for general tasks, and **MSYS2 Bash** for running compilation.
* **Compilers:** MinGW64 `gcc` / `g++`.
* **Python Interpreter:** Windows `python.exe` (mapped from `C:\Program Files\Python314\python.exe`).
* **Game ROM:** US version named `baserom.us.z64` in the workspace root (used for asset extraction).

---

## 3. Standard Build & Run Commands

All make-based compilation commands **must** be executed through the MSYS2 Bash wrapper to resolve Unix utilities like `sh`, `find`, and `printf`.

### Build Commands
* **Clean Build Output:**
  ```powershell
  C:\msys64\usr\bin\bash.exe -c "export PATH=/mingw64/bin:/usr/bin:$PATH && mingw32-make clean"
  ```
* **Compile PC Executable (C baseline):**
  ```powershell
  C:\msys64\usr\bin\bash.exe -c "export PATH=/mingw64/bin:/usr/bin:$PATH && mingw32-make -j4 PYTHON=python"
  ```

### Run Command
Launch the compiled standalone executable in the background (preventing PowerShell block):
```powershell
Start-Process -FilePath "build\us_pc\sm64.us.exe" -WorkingDirectory "build\us_pc"
```

### Game Asset Path
The game standalone executable reads assets from `%LOCALAPPDATA%\SM64Plus\gfx`. After compiling or updating assets, make sure they are copied:
```powershell
New-Item -ItemType Directory -Force -Path "$env:LOCALAPPDATA\SM64Plus"
Copy-Item -Path "build\us_pc\gfx" -Destination "$env:LOCALAPPDATA\SM64Plus\" -Recurse -Force
```

---

## 4. Refactoring Roadmap (C to C++ Transition)
1. **Transition Build Pipeline:** Configure the `Makefile` to compile all `.c` files using `g++` and `-std=c++17` (or higher) to treat all code as C++.
2. **Resolve Compile Errors:** Resolve errors stemming from C++'s stricter syntax:
   * Explicitly cast `void*` pointers.
   * Address designated initializers syntax differences.
   * Wrap standard library headers or declare C-linkage (`extern "C"`) where necessary.
   * Check for identifiers naming conflicts with C++ keywords (e.g. `class`, `template`, `private`, `using`).
3. **Object-Oriented Refactoring:** Convert core engine components (such as Mario's action state machine, actors, levels, and renderer) into modern C++ classes.
