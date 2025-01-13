# **OpenGL-Minimal**

Rendering a simple triangle with OpenGL.

## Summary
- [Getting started](#getting-started)
    - [Installation](#installation)
- [Third-parties](#third-parties)

# Getting started

## Installation
This is a CMake-based project so make sure to install CMake ([portable version](https://github.com/Kitware/CMake/releases/download/v3.26.0-rc5/cmake-3.26.0-rc5-windows-x86_64.zip) : do not forget to add bin directory to PATH).

glad files are generated using Python and the Jinja2 package, [install Python](https://www.python.org/ftp/python/3.11.2/python-3.11.2-amd64.exe) and run the command :
```
pip install -U Jinja2
```

# Third-parties
- glad 2
    - https://github.com/Dav1dde/glad
    - https://gen.glad.sh/
- GLFW
    - https://www.glfw.org/
- Python
    - https://www.python.org/
- CMake
    - https://cmake.org/