#ifndef ENTITY_HEADER
#define ENTITY_HEADER
#pragma once

#include <map>
#include <string>
#include <memory>
#include "Component.hpp"

namespace RaghallaighEngine
{
	class Scene;

	/**
	* Representa una entidad del juego, hace las veces de contenedor de componentes
	*/
	class Entity
	{
		/**
		* mapa de sus componentes
		*/
		std::map<std::string, std::shared_ptr<Component>> components;

		/** 
		* escena a la que pertenece
		*/
		Scene * parent;

	public:

		Entity(Scene * scene) : parent(scene)
		{
		}

		/**
		* inicializa sus componentes
		*/
		void Initialize()
		{
			for (auto & component : components)
			{
				component.second->Initialize();
			}
		}

		/**
		* actualiza sus componentes
		*/
		void Update(float deltaTime)
		{
			for (auto & component : components)
			{
				component.second->Update(deltaTime);
			}
		}

		/**
		* añade un nuevo componente
		*/
		void AddComponent(const std::string & name, std::shared_ptr<Component> & component)
		{
			components.insert(std::make_pair(name, component));
		}

		std::shared_ptr<Component> SetComponent(const std::string & name)
		{
			return components.find(name)->second;
		}

	};
}
#endif