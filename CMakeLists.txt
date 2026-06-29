cmake_minimum_required(VERSION 3.16)
project(hasklib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Header-only library target. Anything that links `hasklib` gets the include path.
add_library(hasklib INTERFACE)
target_include_directories(hasklib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
add_subdirectory(tests)