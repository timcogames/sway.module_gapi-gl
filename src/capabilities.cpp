#include <sway/gapi/capabilities.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

Capabilities::Capabilities() {
	// Empty
}

Capabilities::~Capabilities() {
	// Empty
}

core::Version Capabilities::getGLVersion() const {
	const GLubyte * version = glGetString(GL_VERSION);
	std::string versionStr = std::string((version != NULL ? reinterpret_cast<const char *>(version) : "INVALID"));

	auto majorVersion = 0, minorVersion = 0;
	sscanf(versionStr.c_str(), "%i.%i", &majorVersion, &minorVersion);

	return core::Version(majorVersion, minorVersion);
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
