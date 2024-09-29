#ifndef SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP
#define SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP

#include <sway/gapi/gl/prereqs.hpp>
#include <sway/gapi/gl/wrap/ogltexturehelper.hpp>
#include <sway/gapi/idgenerator.hpp>

#include <queue>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

#define TEXTURE_IDS_CHUNK_CAPACITY 10

using TextureIdType = u32_t;
using TextureIdContainer = std::deque<TextureIdType>;

class OGLTextureIdGenerator : public std::queue<TextureIdType, TextureIdContainer>, public IdGenerator {
public:
  static auto createInstance() -> IdGeneratorPtr_t;

  OGLTextureIdGenerator();

  virtual ~OGLTextureIdGenerator();

  [[nodiscard]]
  auto getNextUid() -> TextureIdType;

private:
  OGLTextureHelper helper_;
  i32_t chunkCapacity_;
  std::vector<u32_t> used_;
};

NAMESPACE_END(gapi)
NAMESPACE_END(sway)

#endif  // SWAY_GAPI_GL_OGLTEXTUREIDGENERATOR_HPP
