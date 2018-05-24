#ifndef COMPONENT_HEADER
#define COMPONENT_HEADER
#pragma once


#include "RapidXML/rapidxml.hpp"

using namespace rapidxml;

namespace RaghallaighEngine
{

	class Entity;

	/**
	* Represesta un componente de una entidad (virtual).
	*/
	class Component
	{

	protected:

		/**
		* Entidad a la que pertenece
		*/
		Entity * parent;

	public:

		Component(Entity * entity) : parent(entity)
		{

		}

		virtual void Initialize() = 0;
		virtual void Update(float deltaTime) = 0;
		virtual bool Parse(const xml_node<> * node) = 0;

	};
}
#endif
