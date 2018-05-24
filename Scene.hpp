/*
@author: Michael O'Reilly Moreno
*/
#pragma once
#ifndef SCENE_HEADER
#define SCENE_HEADER

#include <fstream>
#include <memory>
#include <vector>
#include "Window_Render_Task.hpp"
#include "Input\InputTask.hpp"
#include "Kernel.hpp"
#include "Module.hpp"
#include "RapidXML/rapidxml.hpp"
#include "Entity.hpp"

#include "Input\InputTask.hpp"
#include "ControllerComponent.hpp"

using namespace rapidxml;
using namespace std;

namespace RaghallaighEngine
{
	class Entity;
	class Task;
	class Module;


	/*
	*Representa una escena del juego. Contiene todo lo necesario para que una escena descrita en un XML pueda ser mostrada por pantalla
	*/
	class Scene
	{

	private:

		unsigned int width = 800;
		unsigned int heigth = 800;

		/* Mapa de entidades de la escena*/
		map<string, shared_ptr<Entity>> entities;

		/* Mapa de modulos de la escena*/
		map<string, shared_ptr<Module>> modules;

		Kernel kernel;
		Scene * instance;

		Window_Render_Task windowTask;

		Dispatcher dispatcher;
		InputTask inputTask;

	public:

		Scene(const std::string & scene_description_path, const std::string & Inputs_description_path);
		~Scene();

		void run()
		{
			kernel.execute();
		}

	private:

		/*
		*Carga una escena a partir de la ruta de un XML
		*/
		bool LoadScene(const string & sceneInfo);

		/*
		*Parsea dicha escena
		*/
		bool PaseScene(xml_node<> * sceneNode);

		/*
		*Parsea una entidad y la añade al mapa de las mismas
		*/
		bool ParseEntities(xml_node<> * entityNode);

		/*
		*Parsea un componente de una entidad y lo añade al mapa de los mismos
		*/
		bool ParseComponents(xml_node<> * componentTag, Entity & entity);

		/*
		*Parsea un componente de una entidad y en funcion de su tipo a un parser especifico
		*/
		bool ParseTransform(xml_node<> * componentTag, Entity & entity);

		/*
		*Parsea un componente render y lo añade a su entidad
		*/
		bool ParseRender(xml_node<> * componentTag, Entity & entity);

		/*
		*Parsea un componente que recive inputs para mover un personaje
		*/
		bool ParseInputMove(Entity & entity);

		/*
		*Parsea una mesh
		*/
		bool ParseMesh(string path, Entity & entity);

		/*
		*Inicia el kernel
		*/
		void StartKernel();
	};
}

#endif