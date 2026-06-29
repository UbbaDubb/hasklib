#pragma once
#include <stdexcept>
#include <utility>
#include <variant>

namespace hasklib::core {

// A tiny Result<T, E> for explicit, exception-light error handling.
//   Result<double, ErrorCode> r = Result<...>::ok(1.5);
//   if (r.is_ok()) use(r.value()); else handle(r.error());
//
// Uses in_place_index so it is well-formed even when T and E coincide.
template <class T, class E>
class Result {
 public:
  static Result ok(T value) {
    return Result(std::in_place_index<0>, std::move(value));
  }
  static Result err(E error) {
    return Result(std::in_place_index<1>, std::move(error));
  }

  bool is_ok()  const noexcept { return data_.index() == 0; }
  bool is_err() const noexcept { return data_.index() == 1; }

  const T& value() const {
    if (is_err()) throw std::logic_error("Result::value() called on an error");
    return std::get<0>(data_);
  }
  const E& error() const {
    if (is_ok()) throw std::logic_error("Result::error() called on an ok value");
    return std::get<1>(data_);
  }

 private:
  template <std::size_t I, class U>
  Result(std::in_place_index_t<I> idx, U&& u) : data_(idx, std::forward<U>(u)) {}

  std::variant<T, E> data_;
};

}  // namespace hasklib::core