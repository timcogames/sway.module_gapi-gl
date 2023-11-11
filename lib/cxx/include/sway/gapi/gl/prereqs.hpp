#ifndef SWAY_GAPI_GL_PREREQS_HPP
#define SWAY_GAPI_GL_PREREQS_HPP

#include <sway/core.hpp>
#include <sway/gapi.hpp>
#include <sway/math.hpp>

#define GL_GLEXT_PROTOTYPES 1
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include <memory>  // std::shared_ptr, std::make_shared
#include <set>  // std::set
#include <string.h>  // std::string, strstr

#define BUFFER_OFFSET(x) ((lpstr_t)NULL + (x))

#endif  // SWAY_GAPI_GL_PREREQS_HPP
