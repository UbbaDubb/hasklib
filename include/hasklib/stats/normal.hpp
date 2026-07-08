#pragma once
#include <boost/math/distributions/normal.hpp>
#include "hasklib/core/types.hpp"

namespace hasklib::stats {

using hasklib::core::Real;

namespace detail {
inline const boost::math::normal_distribution<Real>& std_normal() {
    static const boost::math::normal_distribution<Real> dist{0.0, 1.0};
    return dist;
}
}

inline Real norm_pdf(Real x)     { return boost::math::pdf(detail::std_normal(), x); }
inline Real norm_cdf(Real x)     { return boost::math::cdf(detail::std_normal(), x); }
inline Real norm_inv_cdf(Real p) { return boost::math::quantile(detail::std_normal(), p); }

}  // namespace hasklib::stats
