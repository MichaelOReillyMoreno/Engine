#pragma once
#ifndef INPUTTASK_HEADER
#define INPUTTASK_HEADER

#include <iostream>
#include <fstream>
#include <memory>

#include "InputEvent.hpp"
#include "../Tasks.hpp"

#include "../RapidXML/rapidxml.hpp"

using namespace rapidxml;
using namespace std;

namespace RaghallaighEngine
{
	class Dispatcher;

	/*
	* Clase que escucha los inputs del juego y los convierte en mensajes para el dispacher
	*/
	class InputTask : public Task
	{
	private:

		vector<InputEvent> events;
		shared_ptr< sf::Window > window;
		Dispatcher  & dispacher;
	public:

		InputTask(const string & scene_description_path, shared_ptr< sf::Window > _window, Dispatcher  & _dispacher) :
				  Task(0), window(_window), dispacher(_dispacher)
		{
			LoadInputSettings(scene_description_path);
		}

		void initialize();
		void finalize();

		/*
		* Por cada evento de sfml detectado comprueba si corresponde con alguno de los eventos del juego
		*/
		void run();

		/*
		* Comprueba si alguno de los eventos de SFML se corresponde con alguno de los eventos de juego de teclado
		*/
		void Check_InputKey_Events(sf::Keyboard::Key keyEvent);

		/*
		* Carga a partir de un XML los eventos de juego
		*/
		bool LoadInputSettings(const string & sceneInfo);

		/*
		* Parsea los eventos de input
		*/
		bool PaseInputSettings(xml_node<> * sceneNode);

		/*
		* Parsea un evento de input y crea un evento a partir de el
		*/
		bool PaseEvent(xml_node<>* event);
	};
}
#endif