lazy-winapi.cpp
=============

[![Build status](https://ci.appveyor.com/api/projects/status/a8j2d8bvcky81k9y/branch/master?svg=true)](https://ci.appveyor.com/project/DoumanAsh/lazy-winapi-cpp/branch/master)

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

Modules
-------

Each module has a corresponding `.cpp` & `.hpp` files.
Module are independent of each other so you're free to take a particular module sources.
And import it into your project.

### Clipboard

Windows Clipboard Utility.

### Error

WinAPI Error wrapper.
