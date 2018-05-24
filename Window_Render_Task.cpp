#include "Window_Render_Task.hpp"

#include <Cube.hpp>
#include <Light.hpp>
#include <Model.hpp>
#include <OpenGL.hpp>
#include <Model_Obj.hpp>
#include <Render_Node.hpp>

#include <SFML/Window.hpp>

using namespace glt;

RaghallaighEngine::Window_Render_Task::Window_Render_Task(unsigned int & _heigth, unsigned int & _width) :
															heigth(_heigth), width(_width), Task(0),
	window(new sf::Window(sf::VideoMode(width, heigth),
		"OpenGL Toolkit Simple Example",
		sf::Style::Default,
		sf::ContextSettings(24, 0, 0, 3, 2, sf::ContextSettings::Core))),
		scene(shared_ptr< glt::Render_Node >(new glt::Render_Node)),
		camera(shared_ptr< glt::Camera >(new glt::Camera(20.f, 1.f, 50.f, 1.f))),
		light(shared_ptr< glt::Light >(new glt::Light))
{
	glt::initialize_opengl_extensions();
	window->setVerticalSyncEnabled(true);

	scene->add("camera", camera);
	scene->add("light", light);

	glt::Render_Node & refScene = * scene;

	refScene["light"]->translate(Vector3(10.f, 10.f, 10.f));

	reset_viewport(*window, *scene);

	//add_model("../../assets/bunny.obj");
}

void RaghallaighEngine::Window_Render_Task::reset_viewport(const sf::Window & window, glt::Render_Node & scene)
{
	GLsizei width = GLsizei(window.getSize().x);
	GLsizei height = GLsizei(window.getSize().y);

	scene.get_active_camera()->set_aspect_ratio(float(width) / height);

	glViewport(0, 0, width, height);
}

shared_ptr< glt::Model > RaghallaighEngine::Window_Render_Task::add_model(const std::string path, glt::Matrix44 & transform)
{
	shared_ptr< glt::Model > model(new Model_Obj(path));

	scene->add("model", model);

	glt::Render_Node & refScene = *scene;

	model->set_transformation(transform);

	return model;
}

void RaghallaighEngine::Window_Render_Task::initialize(){}

void RaghallaighEngine::Window_Render_Task::finalize(){}

void RaghallaighEngine::Window_Render_Task::run()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	scene->render();

	window->display();
}
