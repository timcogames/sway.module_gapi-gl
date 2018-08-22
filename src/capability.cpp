#include <sway/gapi/gl/capability.h>
#include <sway/gapi/gl/extensions.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

DLLAPI_EXPORT CapabilityRef_t createCapability() {
	auto instance = boost::make_shared<Capability>();
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

	printf("OpenGL extensions:\n");
}

Capability::~Capability() {
	// Empty
}

core::Version Capability::getVersion() const {
	return core::Version(_majorVersion, _minorVersion);
}

void Capability::_initializeVersion() {
	_renderer = reinterpret_cast<lpcstr_t>(glGetString(GL_RENDERER));
	_vendor = reinterpret_cast<lpcstr_t>(glGetString(GL_VENDOR));
	_version = reinterpret_cast<lpcstr_t>(glGetString(GL_VERSION));
	_shadingLanguageVersion = reinterpret_cast<lpcstr_t>(glGetString(GL_SHADING_LANGUAGE_VERSION));

	sscanf(_version.c_str(), "%d.%d", &_majorVersion, &_minorVersion);
}

void Capability::_initializeExtensions() {
	auto exts = reinterpret_cast<lpcstr_t>(glGetString(GL_EXTENSIONS));
	auto func = [&](ExtensionInitList_t probes) -> core::binding::ProcAddress_t {
		for (const auto & probe : probes) {
			if (strstr(exts, probe.first) != nullptr)
				return reinterpret_cast<core::binding::ProcAddress_t>(glXGetProcAddress((const u8_t *) probe.second));
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
