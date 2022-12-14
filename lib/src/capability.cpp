#include <sway/gapi/gl/capability.hpp>
#include <sway/gapi/gl/extensions.hpp>

#include <dlfcn.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

void *dlGetProcAddress(const char *name) {
  static void *h = NULL;
  static void *gpa;

  if (h == NULL) {
    if ((h = dlopen(NULL, RTLD_LAZY | RTLD_LOCAL)) == NULL) {
      return NULL;
    }

    gpa = dlsym(h, "glXGetProcAddress");
  }

  if (gpa != NULL) {
    return ((void *(*)(const unsigned char *))gpa)((const unsigned char *)name);
  } else {
    return dlsym(h, (const char *)name);
  }
}

auto Capability::createInstance() -> CapabilityRef_t {
  auto instance = std::make_shared<Capability>();
  return instance;
}

Capability::Capability() {
  _initializeVersion();
  _initializeExtensions();
  _initLimits();

  printf("Graphics card and driver information:\n");
  printf("\tOpenGL (%s) version: %s\n", _vendor.c_str(), _version.c_str());
  printf("\tOpenGL Renderer: %s\n", _renderer.c_str());
  printf("\tOpenGL shading language version: %s\n", _shadingLanguageVersion.c_str());
}

auto Capability::getVersion() const -> core::Version { return core::Version(_majorVersion, _minorVersion); }

void Capability::_initializeVersion() {
  _renderer = reinterpret_cast<lpcstr_t>(glGetString(GL_RENDERER));
  _vendor = reinterpret_cast<lpcstr_t>(glGetString(GL_VENDOR));
  _version = reinterpret_cast<lpcstr_t>(glGetString(GL_VERSION));
  _shadingLanguageVersion = reinterpret_cast<lpcstr_t>(glGetString(GL_SHADING_LANGUAGE_VERSION));

  sscanf(_version.c_str(), "%d.%d", &_majorVersion, &_minorVersion);
}

void Capability::_initializeExtensions() {
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

void Capability::_initLimits() {
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
