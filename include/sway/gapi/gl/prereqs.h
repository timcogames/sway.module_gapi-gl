#ifndef SWAY_GAPI_GL_PREREQS_H
#define SWAY_GAPI_GL_PREREQS_H

#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>

#include <memory> // std::shared_ptr, std::make_shared
#include <string.h> // std::string, strstr
#include <set> // std::set

#include <boost/algorithm/string.hpp> // boost::to_upper
#include <boost/core/ignore_unused.hpp> // boost::ignore_unused
#include <boost/make_unique.hpp> // boost::make_unique
#include <boost/unordered_map.hpp> // boost::unordered_map
#include <boost/function.hpp> // boost::function
#include <boost/bind.hpp> // boost::bind
#include <boost/variant.hpp> // boost::variant
#include <boost/foreach.hpp> // BOOST_FOREACH
#include <boost/range/adaptor/map.hpp> // boost::adaptors::map_values

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

#define BUFFER_OFFSET(x) ((lpstr_t) NULL + (x))

#endif // SWAY_GAPI_GL_PREREQS_H
