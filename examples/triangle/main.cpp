#include <sway/glx11/xscreenconnection.h>
#include <sway/glx11/canvas.h>
#include <sway/core.h>
#include <sway/math.h>
#include <sway/gapi/gl/extensions.h>
#include <sway/gapi/gl.h>

#include <boost/shared_ptr.hpp> // boost::shared_ptr
#include <boost/make_shared.hpp> // boost::make_shared

using namespace sway;

int main(int argc, char * argv[]) {
	glx11::WindowInitialParams params;
	params.title = "examples";
	params.sizes[glx11::kWindowSize] = math::size2i_t(800, 600);
	params.fullscreen = false;
	params.resizable = false;

	auto connection = boost::make_shared<glx11::XScreenConnection>();
	auto canvas = boost::make_shared<glx11::Canvas>(connection, params);

	canvas->show();
	canvas->getContext()->makeCurrent();

	gapi::Extensions::define();

	auto shaderProgram = boost::make_shared<gapi::ShaderProgram>();

	gapi::ShaderObjectCreateInfo vsoCreateInfo;
	vsoCreateInfo.type = gapi::kShaderType_Vertex;
	vsoCreateInfo.source = 
		"attribute vec3 attr_position; \
		void main() { \
			gl_Position = vec4(attr_position, 1.0); \
		}";

	shaderProgram->attach(gapi::ShaderObject::create(vsoCreateInfo));

	gapi::ShaderObjectCreateInfo fsoCreateInfo;
	fsoCreateInfo.type = gapi::kShaderType_Fragment;
	fsoCreateInfo.source = 
		"void main() { \
			gl_FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f); \
		}";

	shaderProgram->attach(gapi::ShaderObject::create(fsoCreateInfo));
	
	shaderProgram->link();
	shaderProgram->validate();

	gapi::BufferCreateInfo vboCreateInfo;
	vboCreateInfo.description.target = gapi::kBufferTarget_Array;
	vboCreateInfo.description.usage = gapi::kBufferUsage_Static;
	vboCreateInfo.description.byteStride = sizeof(math::VertexPosition);
	vboCreateInfo.description.capacity = 3;
	float vertices[] = {
		-0.5f,-0.5f, 0.0f,
		 0.5f,-0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f
	};
	vboCreateInfo.data = vertices;

	auto vbo = gapi::BufferObject::create(vboCreateInfo);
	auto vlayout = boost::make_shared<gapi::VertexLayout>(shaderProgram.get());
	vlayout->addAttribute<math::vec3f_t>(gapi::VertexSemantic_t::kPosition, false, true);

	gapi::BufferDrawCall drawCall;

	while (canvas->eventLoop(true)) {
		canvas->getContext()->makeCurrent();

		shaderProgram->use();

		vbo->bind();
		vlayout->enable();

		drawCall.update(gapi::kPrimitiveTopology_TriangleList, 3, Type_t::kNone, false);
		drawCall.execute(NULL);

		vlayout->disable();
		vbo->unbind();

		shaderProgram->unuse();

		canvas->getContext()->present();
		canvas->getContext()->doneCurrent();
	}

	return 0;
}
