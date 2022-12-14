#ifndef SWAY_GAPI_GL_WRAPSET_GENERICMEMBERMACROS_HPP
#define SWAY_GAPI_GL_WRAPSET_GENERICMEMBERMACROS_HPP

#include <sway/namespacemacros.hpp>

#include <utility>  //std::forward
#include <variant>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define DECLARE_GENERIC_MEMBER(classname, funcname, funcret, ...)    \
private:                                                             \
  typedef funcret (classname::*funcname##CallbackFunc)(__VA_ARGS__); \
  funcname##CallbackFunc funcname##_;                                \
                                                                     \
public:                                                              \
  template <typename... Args>                                        \
  funcret funcname(Args... args) {                                   \
    return (this->*funcname##_)(std::forward<Args>(args)...);        \
  }

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_WRAPSET_GENERICMEMBERMACROS_HPP
