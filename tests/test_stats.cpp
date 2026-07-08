#include <cmath>
#include <initializer_list>
#include <iostream>

#include "hasklib/stats/normal.hpp"

static int g_failures = 0;

#define REQUIRE(cond)                                                          \
  do {                                                                         \
    if (!(cond)) {                                                             \
      std::cerr << "FAILED: " << #cond << "  (" << __FILE__ << ":"            \
                << __LINE__ << ")\n";                                          \
      ++g_failures;                                                            \
    }                                                                          \
  } while (0)

#define REQUIRE_APPROX(a, b, tol)                                              \
  do {                                                                         \
    if (std::abs((a) - (b)) >= (tol)) {                                        \
      std::cerr << "FAILED: |" << #a << " - " << #b << "| < " << (tol)        \
                << "  got " << (a) << " vs " << (b)                            \
                << "  (" << __FILE__ << ":" << __LINE__ << ")\n";              \
      ++g_failures;                                                             \
    }                                                                           \
  } while (0)

using namespace hasklib::stats;
using hasklib::core::Real;

int main() {
  // --- norm_cdf ---
  REQUIRE_APPROX(norm_cdf(0.0),   0.5,   1e-10);
  REQUIRE_APPROX(norm_cdf(1.96),  0.975, 1e-4);
  REQUIRE_APPROX(norm_cdf(-1.96), 0.025, 1e-4);

  // symmetry: cdf(x) + cdf(-x) == 1
  for (Real x : {0.5, 1.0, 2.0, 3.0})
    REQUIRE_APPROX(norm_cdf(x) + norm_cdf(-x), 1.0, 1e-10);

  // --- norm_pdf ---
  REQUIRE_APPROX(norm_pdf(0.0), 0.3989423, 1e-6);

  // symmetry: pdf(x) == pdf(-x)
  for (Real x : {0.5, 1.0, 2.0, 3.0})
    REQUIRE(norm_pdf(x) == norm_pdf(-x));

  // --- norm_inv_cdf ---
  REQUIRE_APPROX(norm_inv_cdf(0.975), 1.95996, 1e-4);
  REQUIRE_APPROX(norm_inv_cdf(0.5),   0.0,     1e-15);

  // round-trip: cdf(inv_cdf(p)) ≈ p
  for (Real p : {0.1, 0.25, 0.5, 0.75, 0.9})
    REQUIRE_APPROX(norm_cdf(norm_inv_cdf(p)), p, 1e-10);

  if (g_failures == 0) std::cout << "All stats tests passed.\n";
  return g_failures == 0 ? 0 : 1;
}
