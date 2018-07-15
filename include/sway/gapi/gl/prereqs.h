#ifndef SWAY_GAPI_GL_PREREQS_H
#define SWAY_GAPI_GL_PREREQS_H

#include <sway/core.h>
#include <sway/math.h>

#include <string.h> // std::string, strstr
#include <set> // std::set

#include <boost/core/ignore_unused.hpp> // boost::ignore_unused
#include <boost/make_unique.hpp> // boost::make_unique
#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared
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

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

struct VertexAttribute;

using ResourceId_t = u32_t;
using ResourceIdSet_t = std::set<ResourceId_t>;

typedef boost::unordered_map<std::string, math::vec4f_t> UniformVec4fUmap_t;
typedef boost::unordered_map<std::string, VertexAttribute> VertexAttributeUmap_t;

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_GL_PREREQS_H
