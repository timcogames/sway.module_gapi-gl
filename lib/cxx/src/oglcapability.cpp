#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/wrap/oglbufferextension.hpp>
#include <sway/gapi/gl/wrap/oglframebufferextension.hpp>
#include <sway/gapi/gl/wrap/oglgenericshaderextension.hpp>
#include <sway/gapi/gl/wrap/oglinfoextension.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>
#include <sway/gapi/gl/wrap/oglvertexarrayextension.hpp>
#include <sway/gapi/gl/wrap/oglvertexattriblayoutextension.hpp>

#include <dlfcn.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

void *dlGetProcAddress(lpcstr_t name) {
  static void *handle = nullptr;
  static void *gpa;

  if (handle == nullptr) {
    if ((handle = dlopen(nullptr, RTLD_LAZY | RTLD_LOCAL)) == nullptr) {
      return nullptr;
    }

    gpa = dlsym(handle, "glXGetProcAddress");
  }

  if (gpa != nullptr) {
    return ((void *(*)(const u8_t *))gpa)((const u8_t *)name);
  }

  return dlsym(handle, (lpcstr_t)name);
}

auto OGLCapability::createInstance() -> CapabilityPtr_t {
  auto *instance = new OGLCapability();
  return instance;
}

OGLCapability::OGLCapability() {
#ifdef _STUB
  printf("Graphics card and driver information:\n");
  printf("\tAs stub\n");
#else

  initializeVersion_();
  initializeExtensions_();
  initLimits_();

#endif
}

auto OGLCapability::getVersion() const -> core::Version { return core::Version(majorVersion_, minorVersion_); }

auto OGLCapability::toStr() const -> std::string {
  std::stringstream stream;
  // clang-format off
  stream << "Graphics card and driver information:\n" 
         <<        "\tOpenGL (" << vendor_.c_str() << ") version: " << version_.c_str() << "\n"
         <<        "\tOpenGL Renderer: " << renderer_.c_str() << "\n"
         <<        "\tOpenGL shading language version: " << shadingLanguageVersion_.c_str();
  // clang-format on
  return stream.str();
}

void OGLCapability::initializeVersion_() {
  renderer_ = reinterpret_cast<lpcstr_t>(glGetString(GL_RENDERER));
  vendor_ = reinterpret_cast<lpcstr_t>(glGetString(GL_VENDOR));
  version_ = reinterpret_cast<lpcstr_t>(glGetString(GL_VERSION));
  shadingLanguageVersion_ = reinterpret_cast<lpcstr_t>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  sscanf(version_.c_str(), "%d.%d", &majorVersion_, &minorVersion_);
}

void OGLCapability::initializeExtensions_() {
  const auto *exts = reinterpret_cast<lpcstr_t>(glGetString(GL_EXTENSIONS));
  printf("OpenGL extensions:\n%s\n", exts);
  auto func = [&](ExtensionInitList_t probes) -> core::binding::ProcAddress_t {
    for (const auto &probe : probes) {
      if (strstr(exts, probe.first) != nullptr) {
        return reinterpret_cast<core::binding::ProcAddress_t>(dlGetProcAddress((const char *)probe.second));
      }
    }

    return nullptr;
  };

  OGLInfoExtension::define(func);
  OGLShaderProgramExtension::define(func);
  OGLGenericShaderExtension::define(func);
  OGLBufferExtension::define(func);
  OGLVertexArrayExtension::define(func);
  OGLVertexAttribLayoutExtension::define(func);
  OGLTextureExtension::define(func);
  OGLFramebufferExtension::define(func);
}

void OGLCapability::initLimits_() {
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxVertexAttributes_);
  glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &maxVertexOutputComponents_);
  glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &maxVertexTextureImageUnits_);
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &maxVertexUniformComponents_);
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &maxVertexUniformVectors_);

  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &maxDrawBuffers_);

  glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &maxFragmentInputComponents_);
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &maxFragmentUniformComponents_);
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &maxFragmentUniformVectors_);

  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureImageUnits_);
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &maxCombineTextureImageUnits_);
  glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxTextureMaxAnisotropyExt_);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
