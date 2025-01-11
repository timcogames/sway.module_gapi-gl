#ifndef SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP
#define SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP

#include <sway/namespacemacros.hpp>

#include <utility>  //std::forward

namespace sway::gapi {

// clang-format off
#define DECLARE_GENERIC_CALLBACK_FUNC(RET, OBJ, FUNC_NAME, ...)   \
private:                                                          \
  typedef RET (OBJ::*FUNC_NAME##CallbackFunc)(__VA_ARGS__);       \
  FUNC_NAME##CallbackFunc FUNC_NAME##_;

#define DECLARE_GENERIC_MEMBER(RET, OBJ, FUNC_NAME, ...)          \
  DECLARE_GENERIC_CALLBACK_FUNC(RET, OBJ, FUNC_NAME, __VA_ARGS__) \
                                                                  \
public:                                                           \
  template <typename... ARGS>                                     \
  RET FUNC_NAME(ARGS... args) {                                   \
    return (this->*FUNC_NAME##_)(std::forward<ARGS>(args)...);    \
  }
// clang-format on

}  // namespace sway::gapi

#endif  // SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP
