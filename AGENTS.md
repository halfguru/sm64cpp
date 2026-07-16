# AGENTS.md - Super Mario 64 C++ Port Project

This file contains the guidelines, build commands, and refactoring roadmap for AI agents working on this repository.

## 1. Project Overview & Architecture
* **Goal:** Port the C-based PC port of Super Mario 64 (`sm64plus`) to modern C++.
* **Base Codebase:** Unlicensed SM64 PC port (forked at `https://github.com/halfguru/sm64cpp`).
* **Graphics/Windowing Backend:** SDL2 + OpenGL + GLEW.
* **Build System:** CMake (configured with Ninja or Unix Makefiles).

---

## 2. Environment & Tools
* **Shell:** Windows PowerShell (pwsh) or command prompt.
* **Compilers:** MinGW64 `g++` / `clang++`.
* **Python Interpreter:** Windows `python.exe` (mapped from `C:\Program Files\Python314\python.exe`).
* **Game ROM:** US version named `baserom.us.z64` in the workspace root (used for asset extraction).

---

## 3. Standard Build & Run Commands

CMake commands can be run directly from Windows PowerShell (pwsh).

### Build Commands
* **Clean Build Output:**
  ```powershell
  cmake --build build_cmake --target clean
  ```
* **Compile PC Executable (CMake build):**
  ```powershell
  cmake --build build_cmake
  ```

### Run Command
Launch the compiled standalone executable in the background (preventing PowerShell block):
```powershell
Start-Process -FilePath "build_cmake\sm64cpp.exe" -WorkingDirectory "build_cmake"
```

### Game Asset Path
The game standalone executable reads assets from `%LOCALAPPDATA%\SM64Plus\gfx`. After compiling or updating assets, make sure they are copied:
```powershell
New-Item -ItemType Directory -Force -Path "$env:LOCALAPPDATA\SM64Plus"
Copy-Item -Path "build_cmake\gfx" -Destination "$env:LOCALAPPDATA\SM64Plus\" -Recurse -Force
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

---

## 5. Porting & Testing Workflow (Test-Driven Transition)
To ensure that behavior does not change or break during porting/refactoring to C++23, follow this strict transition workflow:
1. **Establish a Unit Test Baseline:** Before modifying a C file or refactoring code, write/extend Catch2 unit tests to cover the current behavior.
2. **Verify the Old Implementation:** Compile and run the unit test suite against the original C implementation, verifying that all tests pass.
3. **Refactor / Port to C++23:** Modernize the file to C++23.
4. **Verify the New Implementation:** Compile and execute the exact same Catch2 tests against the new C++23 implementation to guarantee 100% behavioral parity.
5. **Modern Porting Style & Documentation:**
   * **Modernize Logic:** Eliminate C preprocessor macros where possible, replacing them with modern, type-safe C++ equivalents (e.g., `constexpr` values, `inline` helper functions, `std::size`, standard templates, and namespaces).
     * Avoid preprocessor `#define` macros for constants and calculations. Use type-safe `constexpr` values, inline helper functions, or scoped enum classes (`enum class`) instead to preserve scoping and type checking.
   * **Encapsulate Global State:** Avoid raw `extern` global variables. Encapsulate configurations, states, and subsystems inside modern C++ classes/structures (e.g. singletons, monostates, or dependency-injected objects) to ensure namespace safety and initialization order correctness. For legacy C file compatibility, use bridging patterns (like C++17 `inline` reference aliases inside a bridge header) rather than cluttering the global namespace.
     * Prefer **non-static member initializers (NSDMI)** directly in the class header declaration over constructor initialization lists where possible to make default states self-documenting and prevent uninitialized member variables.
   * **Mandatory Documentation:** Every header (`.hpp`) and source file (`.cpp`) being ported must be fully documented:
      * Add descriptive file-level Doxygen comments (`@file`, `@brief`).
      * Document structures, classes, and public functions (`@struct`, `@class`, `@brief`, `@param`, `@return`).
      * Include clear inline comments explaining complex, type-safe operations (such as visitor patterns, templates, or lambdas).
   * **Header Inclusion Guards:** Modern C++23 ported headers must use `#pragma once` at the top instead of the legacy `#ifndef`/`#define`/`#endif` include-guard idiom. When converting an existing header, replace its include guard with `#pragma once` (retaining any file-level Doxygen comment above it). New `.hpp` headers must always start with `#pragma once`.
   * **C++ Header File Extension:** The long-term target for the C++23 port is `.hpp` (not `.h`) for all C++ headers. During the transitional port most headers are still `.h` and are included as such by C++ translation units, which is acceptable. When a header is ported/created as a C++-only header (classes, `enum class`, templates, `std::` usage) it should be named `.hpp`. A repo-wide `.h` → `.hpp` rename will be done as a single coordinated pass once the port is more mature, rather than renaming headers one at a time (to avoid churning every `#include` site prematurely).
   * **Clang-Tidy Validation:** Run `clang-tidy` checks on all modified or newly created files, and resolve all reported warnings to ensure static analysis compliance and high code quality.
