#include <sway/gapi/gl/oglcapability.hpp>
#include <sway/gapi/gl/oglextensions.hpp>

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
  printf("\tOpenGL (%s) version: %s\n", _vendor.c_str(), _version.c_str());
  printf("\tOpenGL Renderer: %s\n", _renderer.c_str());
  printf("\tOpenGL shading language version: %s\n", _shadingLanguageVersion.c_str());

#endif
}

auto OGLCapability::getVersion() const -> core::Version { return core::Version(_majorVersion, _minorVersion); }

void OGLCapability::initializeVersion_() {
  _renderer = reinterpret_cast<lpcstr_t>(glGetString(GL_RENDERER));
  _vendor = reinterpret_cast<lpcstr_t>(glGetString(GL_VENDOR));
  _version = reinterpret_cast<lpcstr_t>(glGetString(GL_VERSION));
  _shadingLanguageVersion = reinterpret_cast<lpcstr_t>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  sscanf(_version.c_str(), "%d.%d", &_majorVersion, &_minorVersion);
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
}

void OGLCapability::initLimits_() {
  glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &_maxVertexAttributes);
  glGetIntegerv(GL_MAX_VERTEX_OUTPUT_COMPONENTS, &_maxVertexOutputComponents);
  glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &_maxVertexTextureImageUnits);
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_COMPONENTS, &_maxVertexUniformComponents);
  glGetIntegerv(GL_MAX_VERTEX_UNIFORM_VECTORS, &_maxVertexUniformVectors);

  glGetIntegerv(GL_MAX_DRAW_BUFFERS, &_maxDrawBuffers);

  glGetIntegerv(GL_MAX_FRAGMENT_INPUT_COMPONENTS, &_maxFragmentInputComponents);
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_COMPONENTS, &_maxFragmentUniformComponents);
  glGetIntegerv(GL_MAX_FRAGMENT_UNIFORM_VECTORS, &_maxFragmentUniformVectors);

  glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &_maxTextureImageUnits);
  glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &_maxCombineTextureImageUnits);
  glGetIntegerv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &_maxTextureMaxAnisotropyExt);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
