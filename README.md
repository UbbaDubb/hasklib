# hasklib

A header-only C++17 quant library. Link it via CMake and get the include path — no compilation step for the library itself.

## Requirements

- CMake 3.16+
- A C++17 compiler (MSVC 2022, GCC 10+, or Clang 12+)
- Internet access on first build (Boost 1.85.0 is fetched automatically)

## Structure

```
hasklib/
├── include/hasklib/
│   ├── core/
│   │   ├── types.hpp       # Real, Size, Vector type aliases
│   │   ├── constants.hpp   # pi, two_pi, sqrt_two_pi, sqrt_two
│   │   └── result.hpp      # Result<T, E> — ok/err type
│   └── stats/
│       └── normal.hpp      # norm_pdf, norm_cdf, norm_inv_cdf
└── tests/
    ├── test_core.cpp
    └── test_stats.cpp
```

## Building

### Linux / macOS

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Boost is downloaded automatically on first configure (~124 MB). Subsequent builds use the cached copy.

### Windows

CMake's bundled curl uses Windows Schannel, which has a known bug with HTTP/2 connections to GitHub's release CDN and will fail to download Boost. Work around it by downloading the archive manually first.

**Step 1 — download Boost** (run once, from any terminal):

```powershell
$out = "$env:TEMP\boost-1.85.0-cmake.tar.gz"
$url = "https://github.com/boostorg/boost/releases/download/boost-1.85.0/boost-1.85.0-cmake.tar.gz"
do { curl.exe --http1.1 -L -C - -o $out $url } while ((Get-Item $out).Length -lt 124000000)
```

**Step 2 — extract**:

```powershell
$dest = "$env:TEMP\boost-1.85.0-cmake"
New-Item -ItemType Directory -Force $dest | Out-Null
Push-Location $dest
cmake -E tar xf "$env:TEMP\boost-1.85.0-cmake.tar.gz"
Pop-Location
```

**Step 3 — configure and build** (point CMake at the local source):

```powershell
cmake -S . -B build -DFETCHCONTENT_SOURCE_DIR_BOOST="$env:TEMP\boost-1.85.0-cmake\boost-1.85.0"
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

`FETCHCONTENT_SOURCE_DIR_BOOST` is only needed on the first configure. After that, CMake caches the extracted source in `build/_deps/` and subsequent builds work without it.

> **Using Visual Studio?** Open a *Developer PowerShell for VS 2022* before running these commands so that `cmake` and `ctest` are on your PATH. Alternatively, use the VS Code tasks (`Ctrl+Shift+B` to build, `Ctrl+Shift+P` → *Tasks: Run Test Task* to test) — the `.vscode/` config is intentionally not tracked in git, so set it up locally as needed.

## Using the library in your own project

```cmake
# In your CMakeLists.txt
include(FetchContent)
FetchContent_Declare(
  hasklib
  GIT_REPOSITORY https://github.com/UbbaDubb/hasklib.git
  GIT_TAG        main
)
FetchContent_MakeAvailable(hasklib)

target_link_libraries(my_target PRIVATE hasklib)
```

Then include headers directly:

```cpp
#include "hasklib/core/types.hpp"
#include "hasklib/core/constants.hpp"
#include "hasklib/core/result.hpp"
#include "hasklib/stats/normal.hpp"
```

## Running the tests

```bash
ctest --test-dir build -C Debug --output-on-failure
```

Expected output:

```
1/2 Test #1: core .............................   Passed
2/2 Test #2: stats ............................   Passed

100% tests passed, 0 tests failed out of 2
```
