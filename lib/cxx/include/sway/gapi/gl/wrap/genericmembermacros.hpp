#ifndef SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP
#define SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP

#include <sway/namespacemacros.hpp>

#include <utility>  //std::forward

NS_BEGIN_SWAY()
NS_BEGIN(gapi)

#define DECLARE_GENERIC_MEMBER(RET, OBJ, FUNC_NAME, ...)       \
private:                                                       \
  typedef RET (OBJ::*FUNC_NAME##CallbackFunc)(__VA_ARGS__);    \
  FUNC_NAME##CallbackFunc FUNC_NAME##_;                        \
                                                               \
public:                                                        \
  template <typename... ARGS>                                  \
  RET FUNC_NAME(ARGS... args) {                                \
    return (this->*FUNC_NAME##_)(std::forward<ARGS>(args)...); \
  }

#define DECL_GENERIC_CALLBACK_FUNC(RET, OBJ, FUNC_NAME, ...) \
private:                                                     \
  typedef RET (OBJ::*FUNC_NAME##CallbackFunc)(__VA_ARGS__);  \
  FUNC_NAME##CallbackFunc FUNC_NAME##_;

NS_END()  // namespace gapi
NS_END()  // namespace sway

#endif  // SWAY_GAPI_GL_WRAP_GENERICMEMBERMACROS_HPP
