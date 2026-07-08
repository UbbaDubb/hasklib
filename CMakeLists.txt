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

# Header-only library target. Anything that links `hasklib` gets the include path.
add_library(hasklib INTERFACE)
target_include_directories(hasklib INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(hasklib INTERFACE Boost::math)

enable_testing()
add_subdirectory(tests)