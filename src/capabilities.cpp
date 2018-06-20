#include <sway/gapi/capabilities.h>

NAMESPACE_BEGIN(sway)
NAMESPACE_BEGIN(gapi)

Capabilities::Capabilities() {
	// Empty
}

Capabilities::~Capabilities() {
	// Empty
}

core::Version Capabilities::getVersion() {
	const GLubyte * glVersion = glGetString(GL_VERSION);
	std::string glVersionStr = std::string((glVersion != NULL ? reinterpret_cast<const char *>(glVersion) : "INVALID"));

	auto majorVersion = 0;
	auto minorVersion = 0;

	sscanf(glVersionStr.c_str(), "%d.%d", &majorVersion, &minorVersion);

	const auto version = core::Version(
		static_cast<u8_t>(majorVersion & 255), 
		static_cast<u8_t>(minorVersion & 255));

	return version;
}

NAMESPACE_END(gapi)
NAMESPACE_END(sway)
