cmake_minimum_required(VERSION 3.16)
project(hasklib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

set(BOOST_INCLUDE_LIBRARIES math)
set(BOOST_ENABLE_CMAKE ON)

FetchContent_Declare(
  Boost
  URL https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.gz
  DOWNLOAD_EXTRACT_TIMESTAMP ON
)
FetchContent_MakeAvailable(Boost)

FetchContent_Declare(
  pybind11
  GIT_REPOSITORY https://github.com/pybind/pybind11.git
  GIT_TAG v2.13.6
)
FetchContent_MakeAvailable(pybind11)

# Compiled library target. Sources are globbed since the project is still
# growing quickly; CONFIGURE_DEPENDS re-runs the glob on each build so new
# .cpp files are picked up without having to re-run cmake by hand.
# bindings/*.cpp is excluded here — those need pybind11 headers and belong
# to the hasklib_py module target below, not the plain C++ static library.
file(GLOB_RECURSE HASKLIB_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/hasklib/*.cpp)
list(FILTER HASKLIB_SOURCES EXCLUDE REGEX "/bindings/")

add_library(hasklib STATIC ${HASKLIB_SOURCES})
target_include_directories(hasklib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(hasklib PUBLIC Boost::math)

# Python bindings module (pybind11). Target name must match the name passed
# to PYBIND11_MODULE(...) in bindings/module.cpp.
file(GLOB HASKLIB_BINDINGS_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/hasklib/bindings/*.cpp)

pybind11_add_module(hasklib_py ${HASKLIB_BINDINGS_SOURCES})
target_link_libraries(hasklib_py PRIVATE hasklib)

enable_testing()
add_subdirectory(tests)