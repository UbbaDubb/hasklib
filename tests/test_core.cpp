// Minimal dependency-free test. Each REQUIRE tracks failures;
// main() returns non-zero if any failed, which is what CTest checks.
#include <iostream>
#include <string>

#include "hasklib/core/constants.hpp"
#include "hasklib/core/result.hpp"
#include "hasklib/core/types.hpp"

static int g_failures = 0;

#define REQUIRE(cond)                                                    \
  do {                                                                   \
    if (!(cond)) {                                                       \
      std::cerr << "FAILED: " << #cond << "  (" << __FILE__ << ":"       \
                << __LINE__ << ")\n";                                    \
      ++g_failures;                                                      \
    }                                                                    \
  } while (0)

using namespace hasklib::core;

enum class ErrorCode { kNone, kBadInput };

int main() {
  REQUIRE(constants::two_pi > constants::pi);
  REQUIRE(constants::sqrt_two_pi > 2.5 && constants::sqrt_two_pi < 2.51);

  Result<Real, ErrorCode> ok = Result<Real, ErrorCode>::ok(1.5);
  REQUIRE(ok.is_ok());
  REQUIRE(!ok.is_err());
  REQUIRE(ok.value() == 1.5);

  Result<Real, ErrorCode> err = Result<Real, ErrorCode>::err(ErrorCode::kBadInput);
  REQUIRE(err.is_err());
  REQUIRE(err.error() == ErrorCode::kBadInput);

  bool threw = false;
  try { (void)err.value(); } catch (const std::logic_error&) { threw = true; }
  REQUIRE(threw);

  if (g_failures == 0) std::cout << "All core tests passed.\n";
  return g_failures == 0 ? 0 : 1;
}