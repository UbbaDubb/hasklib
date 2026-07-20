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

# Compiled library target. Sources are globbed since the project is still
# growing quickly; CONFIGURE_DEPENDS re-runs the glob on each build so new
# .cpp files are picked up without having to re-run cmake by hand.
file(GLOB_RECURSE HASKLIB_SOURCES CONFIGURE_DEPENDS
     ${CMAKE_CURRENT_SOURCE_DIR}/include/hasklib/*.cpp)

add_library(hasklib STATIC ${HASKLIB_SOURCES})
target_include_directories(hasklib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(hasklib PUBLIC Boost::math)

enable_testing()
add_subdirectory(tests)