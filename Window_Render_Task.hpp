#pragma once
#ifndef WINDOW_RENDER_HEADER
#define WINDOW_RENDER_HEADER

#include <memory>

#include "Transform\TransformComponet.hpp"
#include "Tasks.hpp"

namespace sf
{
	class Window;
}

namespace glt
{
	class Render_Node;
	class Camera;
	class Light;
	class Node;
	class Model;
}

using namespace std;
using namespace glt;

namespace RaghallaighEngine
{

	class Window_Render_Task : public Task
	{
	private:

		unsigned int & heigth;
		unsigned int & width;

		shared_ptr< glt::Render_Node > scene;
		shared_ptr< glt::Camera      > camera;
		shared_ptr< glt::Light       > light;

		void reset_viewport(const sf::Window & window, glt::Render_Node & scene);

	public:

		shared_ptr< sf::Window > window;

		Window_Render_Task(unsigned int & _heigth, unsigned int & _width);

		void initialize();
		void finalize();
		void run();

		shared_ptr< glt::Model > add_model(const std::string path, glt::Matrix44 & transform);
	};
}
#endif