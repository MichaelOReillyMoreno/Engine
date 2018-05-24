#pragma once
#ifndef EVENT_HEADER
#define EVENT_HEADER

#include <string>
#include <vector>

#include <SFML\Graphics.hpp>

using namespace std;
using namespace sf;

namespace RaghallaighEngine
{
	/*
	* Evento de tipo input, al que le corresponde unas lista de teclas y que se identifica por su id
	*/
	class InputEvent
	{
	public:

		int id;
		vector <Keyboard::Key> keys;

	public:

		InputEvent(int _id): id(_id){}

		/*
		* Asigna una nueva tecla a este evento
		*/
		void AddKey(int keyValue);

		/*
		* Comprueba si alguna de las teclas asignadas a este evento han sido pulsadas
		*/
		const bool CheckAssignedKeys(const int & keyValue) const;

	};
}
#endif