lazy-winapi.cpp
=============

Simple and lazy wrapper over WinAPI

Requirements
------------

* C++ compiler;
* Windows platform;
* CMake (to build from source).

Usage
-----

#### Build from source

Headers are together with source code in `src/lazy_winapi`

```bash
mkdir build
cd build/
cmake ../
cmake --build .
```

**Options:**

* `UNIT_TEST` - build unit tests;
* `BUILD_SHARED` - build shared library instead of static.

