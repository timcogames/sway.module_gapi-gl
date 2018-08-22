#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/canvas.h>
#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi.h>
#include <sway/gapi/gl.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

using namespace sway;

int main(int argc, char * argv[]) {
	glx11::WindowInitialParams params;
	params.title = "examples";
	params.sizes[core::detail::toUnderlying(glx11::WindowSize_t::kOrigin)] = math::size2i_t(800, 600);
	params.fullscreen = false;
	params.resizable = false;

	auto connection = boost::make_shared<glx11::XScreenConnection>();
	auto canvas = boost::make_shared<glx11::Canvas>(connection, params);

	canvas->show();
	canvas->getContext()->makeCurrent();

	auto capability = gapi::createCapability();

	gapi::ShaderCreateInfo vsoCreateInfo;
	vsoCreateInfo.type = gapi::ShaderType_t::kVertex;
	vsoCreateInfo.code =
		"attribute vec3 attr_position; \
		void main() { \
			gl_Position = vec4(attr_position, 1.0); \
	 	}";

	gapi::ShaderCreateInfo fsoCreateInfo;
	fsoCreateInfo.type = gapi::ShaderType_t::kFragment;
	fsoCreateInfo.code =
		"void main() { \
			gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
		}";

	auto program = gapi::createShaderProgram();
	program->attach(gapi::createShader(vsoCreateInfo));
	program->attach(gapi::createShader(fsoCreateInfo));

	try {
		program->link();
		program->validate();
	}
	catch (std::exception & exception) {
		throw;
	}

	gapi::BufferCreateInfo vboCreateInfo;
	vboCreateInfo.desc.target = gapi::BufferTarget_t::kArray;
	vboCreateInfo.desc.usage = gapi::BufferUsage_t::kStatic;
	vboCreateInfo.desc.byteStride = sizeof(math::VertexPosition);
	vboCreateInfo.desc.capacity = 3;
	float vertices[] = {
		-0.5f,-0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};
	vboCreateInfo.data = vertices;

	auto vbo = gapi::createBuffer(vboCreateInfo);
	auto vlayout = gapi::createVertexLayout(program);
	vlayout->addAttribute(gapi::VertexAttribute::merge<math::vec3f_t>(gapi::VertexSemantic_t::kPosition, false, true));

	auto drawCall = gapi::createDrawCall();

	while (canvas->eventLoop(true)) {
		canvas->getContext()->makeCurrent();

		program->use();

		vbo->bind();
		vlayout->enable();

		drawCall->execute(gapi::PrimitiveType_t::kTriangleList, 3, NULL, Type_t::kNone);

		vlayout->disable();
		vbo->unbind();

		program->unuse();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	return 0;
}
