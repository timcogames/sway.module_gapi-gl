#ifndef SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
#define SWAY_GAPI_GL_OGLGENERICBUFFER_HPP

#include <sway/gapi/buffercreateinfo.hpp>
#include <sway/gapi/bufferdescriptor.hpp>
#include <sway/gapi/buffermapaccesses.hpp>
#include <sway/gapi/buffermaprangeaccesses.hpp>
#include <sway/gapi/buffersubdatadescriptor.hpp>
#include <sway/gapi/buffertargets.hpp>
#include <sway/gapi/bufferusages.hpp>
#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/oglgenericbufferhelper.hpp>
#include <sway/gapi/idgenerator.hpp>

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

  static auto createInstance(IdGeneratorPtr_t idgen, const BufferCreateInfo &createInfo) -> BufferPtr_t;

#pragma region "Ctors/Dtor"

  /**
   * @brief Конструктор класса.
   *        Выполняет инициализацию нового экземпляра класса.
   */
  OGLGenericBuffer(IdGeneratorPtr_t idgen, const BufferDescriptor &desc);

  virtual ~OGLGenericBuffer() { std::cout << "DCTOR" << std::endl; }

#pragma endregion

  /**
   * @brief Устанавливает данные в аппаратный буфер.
   *
   * @param[in] data Первоначальный данные.
   */
  MTHD_OVERRIDE(auto allocate(const void *data) -> bool);

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

  MTHD_OVERRIDE(void flush(i32_t offset, i32_t len));

  MTHD_OVERRIDE(auto map(BufferMapAccess flags) -> void *);

  MTHD_OVERRIDE(auto mapRange(
                    i32_t offset, i32_t len, core::detail::EnumClassBitset<BufferMapRangeAccess> bitset) -> void *);

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
  MTHD_OVERRIDE(auto getTarget() const -> BufferTarget) {
    return target_;
  }

  /**
   * @brief Получает режим работы с данными.
   */
  MTHD_OVERRIDE(auto getUsage() const -> BufferUsage) {
    return usage_;
  }

  /**
   * @brief Получает количество элементов в массиве.
   */
  MTHD_OVERRIDE(auto getCapacity() const -> i32_t) {
    return capacity_;
  }

  /**
   * @brief Получает размер структуры данных.
   */
  MTHD_OVERRIDE(auto getByteStride() const -> i32_t) {
    return byteStride_;
  }

private:
  OGLGenericBufferHelper helper_;
  BufferTarget target_;
  BufferUsage usage_;
  i32_t capacity_;
  i32_t byteStride_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLGENERICBUFFER_HPP
