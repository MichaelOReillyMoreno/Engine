#pragma once
#ifndef DISPACHER_HEADER
#define DISPACHER_HEADER

#include "Message.hpp"

namespace RaghallaighEngine
{
	/**
	* Escuchador de mensajes
	*/
	class Listener
	{
	public:
		virtual  ~Listener() {}
		virtual void handle(const Message & message) = 0;
	};

	/**
	* Se encarga de gestinar los mensajes del juego. Cada vez que recibe un mensaje comprueba si hay algun escuchador que lo procese
	*/
	class Dispatcher
	{

	private:

		typedef std::unordered_multimap< int, Listener * > Listener_Map;

		/**
		* Mapa de listeners
		*/
		Listener_Map listeners;

	public:

		/**
		* Añade un nuevo escuchador
		*/
		void add_listener(int message_id, Listener & listener)
		{
			listeners.insert(std::pair< int, Listener * >(message_id, &listener));
		}

		/**
		* Borra un escuchador
		*/
		void remove_listener(Listener & listener)
		{
			for (Listener_Map::iterator i = listeners.begin(); i != listeners.end(); ++i)
			{
				if (i->second == &listener)
				{
					listeners.erase(i);
				}
			}
		}

		/**
		* Envia un mensaje a todos los escuchadores
		*/
		void send(const Message & message)
		{
			for (Listener_Map::iterator i = listeners.lower_bound(message), end = listeners.upper_bound(message); i != end; ++i)
			{
				i->second->handle(message);
			}
		}

	};
}
#endif