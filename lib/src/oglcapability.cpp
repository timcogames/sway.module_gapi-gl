#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>
#include <sway/gapi/gl/wrap/ogltextureextension.hpp>

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

auto OGLCapability::createInstance() -> CapabilityRef_t {
  auto instance = std::make_shared<OGLCapability>();
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

  printf("Graphics card and driver information:\n");
  printf("\tOpenGL (%s) version: %s\n", vendor_.c_str(), version_.c_str());
  printf("\tOpenGL Renderer: %s\n", renderer_.c_str());
  printf("\tOpenGL shading language version: %s\n", shadingLanguageVersion_.c_str());

#endif
}

auto OGLCapability::getVersion() const -> core::Version { return core::Version(majorVersion_, minorVersion_); }

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

  Extension::define(func);
  OGLTextureExtension::define(func);
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
