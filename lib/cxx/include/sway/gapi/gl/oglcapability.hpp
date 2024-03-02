#ifndef SWAY_GAPI_GL_OGLCAPABILITY_HPP
#define SWAY_GAPI_GL_OGLCAPABILITY_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglshaderprogramextension.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

class OGLCapability : public Capability {
public:
  static auto createInstance() -> CapabilityPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLCapability();

  /**
   * @brief Деструктор класса.
   */
  virtual ~OGLCapability() = default;

  /**
   * @brief Возвращает версию OpenGL.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getVersion() const -> core::Version);  // clang-format on

  [[nodiscard]]
  auto toStr() const -> std::string;

  static auto getExtensions() -> lpcstr_t { return reinterpret_cast<lpcstr_t>(glGetString(GL_EXTENSIONS)); }

  static auto isExtensionSupported(lpcstr_t extensions, lpcstr_t name) -> bool {
    if (strstr(extensions, name) == nullptr) {
      std::cout << "(!) Extension " << name << " is not supported." << std::endl;
      return false;
    }

    return true;
  }

private:
  /**
   * @brief Инициализирует версию.
   */
  void initializeVersion_();

  /**
   * @brief Инициализирует расширения.
   */
  void initializeExtensions_();

  void initLimits_();

  std::string renderer_;
  std::string vendor_;
  std::string version_;
  std::string shadingLanguageVersion_;
  s32_t majorVersion_;
  s32_t minorVersion_;

  s32_t maxVertexAttributes_;
  s32_t maxVertexOutputComponents_;
  s32_t maxVertexTextureImageUnits_;
  s32_t maxVertexUniformComponents_;
  s32_t maxVertexUniformVectors_;

  s32_t maxDrawBuffers_;

  s32_t maxFragmentInputComponents_;
  s32_t maxFragmentUniformComponents_;
  s32_t maxFragmentUniformVectors_;

  s32_t maxTextureImageUnits_;
  s32_t maxCombineTextureImageUnits_;
  s32_t maxTextureMaxAnisotropyExt_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLCAPABILITY_HPP
