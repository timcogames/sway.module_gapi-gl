#ifndef SWAY_GAPI_PREREQS_H
#define SWAY_GAPI_PREREQS_H

#include <sway/core.h>
#include <sway/math.h>

#include <string.h> // std::string, strstr
#include <set> // std::set

#include <boost/make_unique.hpp> // boost::make_unique
#include <boost/unordered_map.hpp> // boost::unordered_map

#include <GL/gl.h>
#include <GL/glx.h>
#include <GL/glu.h>
#include <GL/glext.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

using ResourceId_t = u32_t;
using ResourceIdSet_t = std::set<ResourceId_t>;

typedef boost::unordered_map<std::string, math::vec4f_t> UniformVec4fUmap_t;

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif // SWAY_GAPI_PREREQS_H
