#ifndef SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
#define SWAY_GAPI_GL_OGLGENERICBUFFER_HPP

#include <sway/gapi/gl/oglbufferidgenerator.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

/**
 * @brief Представление аппаратного буфера.
 */
class OGLGenericBuffer final : public Buffer {
public:
#pragma region "Преобразование внутренних типов к GLenum"

  static auto usageToGLenum(BufferUsage usage) -> GLenum;

#pragma endregion

  static auto createInstance(IdGeneratorPtr_t idQueue, const BufferCreateInfo &createInfo) -> BufferPtr_t;

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLGenericBuffer(IdGeneratorPtr_t idQueue, const BufferDescriptor &desc);

  virtual ~OGLGenericBuffer() { std::cout << "DCTOR" << std::endl; }

  /**
   * @brief Устанавливает данные в аппаратный буфер.
   *
   * @param[in] data Первоначальный данные.
   */
  // clang-format off
  MTHD_OVERRIDE(auto allocate(const void *data) -> bool);  // clang-format on

  /**
   * @brief Изменяет данные в уже существующем буфере.
   *
   * @param[in] desc Описание конкретной заполняемой области.
   * @sa updateSubdata(const void *)
   */
  MTHD_OVERRIDE(void updateSubdata(BufferSubdataDescriptor desc));

  /**
   * @brief Изменяет данные в уже существующем буфере.
   *
   * @param[in] src Область памяти, содержащая новые значения.
   * @sa updateSubdata(u32_t, u32_t, const void *)
   */
  MTHD_OVERRIDE(void updateSubdata(const void *src));

  MTHD_OVERRIDE(void flush(s32_t offset, s32_t length));

  // clang-format off
  MTHD_OVERRIDE(auto map(BufferMapAccess flags) -> void *);  // clang-format on

  // clang-format off
  MTHD_OVERRIDE(auto mapRange(s32_t offset, s32_t length, core::detail::EnumClassBitset<BufferMapRangeAccess> bitset) -> void *);  // clang-format on

  MTHD_OVERRIDE(void unmap());

  MTHD_OVERRIDE(void bindRange(u32_t buffer, ptrdiff_t offset, ptrdiff_t size));

  /**
   * @brief Делает буфер текущим.
   *
   * @sa unbind()
   */
  MTHD_OVERRIDE(void bind());

  /**
   * @brief Делает текущим пустой буфер.
   *
   * @sa bind()
   */
  MTHD_OVERRIDE(void unbind());

  /**
   * @brief Получает целевой тип буфера.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getTarget() const -> BufferTarget) {  // clang-format on
    return target_;
  }

  /**
   * @brief Получает режим работы с данными.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getUsage() const -> BufferUsage) {  // clang-format on
    return usage_;
  }

  /**
   * @brief Получает количество элементов в массиве.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getCapacity() const -> s32_t) {  // clang-format on
    return capacity_;
  }

  /**
   * @brief Получает размер структуры данных.
   */
  // clang-format off
  MTHD_OVERRIDE(auto getByteStride() const -> s32_t) {  // clang-format on
    return byteStride_;
  }

private:
  OGLGenericBufferHelper helper_;
  BufferTarget target_;
  BufferUsage usage_;
  s32_t capacity_;
  s32_t byteStride_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
