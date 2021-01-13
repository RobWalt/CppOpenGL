![C++](https://camo.githubusercontent.com/c59efb57803dde7f352f4932a468a7f39fa2fb5f/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f632532422532422d31312f31342f31372f32302d626c75652e737667)
![License](https://camo.githubusercontent.com/890acbdcb87868b382af9a4b1fac507b9659d9bf/68747470733a2f2f696d672e736869656c64732e696f2f62616467652f6c6963656e73652d4d49542d626c75652e737667)
[![Travis CI](https://travis-ci.org/github/RobWalt/CppOpenGL.svg?branch=master)](https://travis-ci.org/github/RobWalt/CppOpenGL)
[![codecov](https://codecov.io/gh/RobWalt/CppOpenGL/branch/master/graph/badge.svg)](https://codecov.io/gh/RobWalt/CppOpenGL)

# OpenGL Hobby Project

## Structure
``` text
├── CMakeLists.txt
├── app
│   ├── CMakesLists.txt
│   └── main.cpp
├── benchmarks
│   ├── CMakesLists.txt
│   └── main.cpp
├── docs
├── ├── Doxyfile
│   └── html...
├── external
│   ├── CMakesLists.txt
│   ├── glm
│   ├── glad
│   ├── glfw
│   ├── loguru...
│   └── Celero...
├── include
│   └── MyLib
│       └── my_lib.hpp
├── src
│   ├── CMakesLists.txt
│   └── MyLib
│       ├── CMakesLists.txt
│       └── my_lib.cpp
└── tests
    ├── CMakeLists.txt
    └── main.cpp
```

Sources go in [src/](src/), header files in [include/](include/), main programs in [app/](app),
tests go in [tests/](tests/) and benchmarks go in [benchmarks/](benchmarks/).

If you add a new executable, say `app/new_executable.cc`, you only need to add the following two lines to [CMakeLists.txt](CMakeLists.txt): 

``` cmake
add_executable(new_executable app/new_executable.cc)   # Name of exec. and location of file.
target_link_libraries(new_executable PRIVATE ${LIBRARY_NAME})  # Link the executable to lib built from src/*.cc (if it uses it).
```

You can find the example source code that builds the `main` executable in [app/main.cc](app/main.cc) under the `Build` section in [CMakeLists.txt](CMakeLists.txt). 
If the executable you made does not use the library in [src/](src), then only the first line is needed.
