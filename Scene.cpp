#include "Scene.hpp"

#include <SFML/Graphics.hpp>
#include <stdio.h>

namespace RaghallaighEngine
{
	Scene::Scene(const std::string & scene_description_path, const std::string & Inputs_description_path)
		:
		instance(this),
		kernel(),
		windowTask(width, heigth),
		inputTask(Inputs_description_path, windowTask.window, dispatcher)
	{
			kernel.Add(windowTask);
			kernel.Add(inputTask);
			LoadScene(scene_description_path);
	}

	Scene::~Scene()
	{
	}

	bool Scene::LoadScene(const string & sceneInfo)
	{
		//Se lee el contenido del archivo
		fstream xml_file(sceneInfo, fstream::in);

		if (xml_file.good())
		{
			// Se carga en un vector el contenido del archivo XML

			vector< char > xml_content;

			bool finished = false;

			do
			{
				int character = xml_file.get();

				if (character != -1)
				{
					xml_content.push_back((char)character);
				}
				else
				{
					// Fin del archivo
					finished = true;
					xml_content.push_back(0);
				}


			} while (!finished);

			// Se crea el modelo de documento (DOM)

			xml_document< > document;

			document.parse< 0 >(xml_content.data());

			// Se comprueba si el parseo ha sido correcto

			xml_node< > * node = document.first_node();

			if (node && std::string(node->name()) == "scene")
			{
				PaseScene(node);
			}

		}

		return false;

	}

	void Scene::StartKernel()
	{
		for (auto & module : modules)
		{
			Task * task = module.second->GetTask();

			if (task)
			{
				kernel.Add(*task);
			}

		}
	}

	bool Scene::PaseScene(xml_node<> * sceneNode)
	{
		// Busca las entidades en el XML.
		for (xml_node<> * child = sceneNode->first_node(); child; child = child->next_sibling())
		{
			if (child->type() == node_element)
			{
				if (string(child->name()) == "entities")
				{
					ParseEntities(child);
				}
			}
		}

		return true;
	}

	bool Scene::ParseEntities(xml_node<> * entitiesNode)// estoy en entidades
	{
		// Busca las entidades de la escena.
		for (xml_node<> * entityTag = entitiesNode->first_node(); entityTag; entityTag = entityTag->next_sibling())
		{
			if (entityTag->type() == node_element)
			{
				// Si no encuentra la entidad, se devuelve.
				if (string(entityTag->name()) != "entity")
					return false;

				string id;

				// Buscamos el nombre del atributo.
				for (xml_attribute<> * attribute = entityTag->first_attribute(); attribute; attribute = attribute->next_attribute())
				{
					if (string(attribute->name()) == "id")
					{
						id = attribute->value();
					}
				}

				puts(id.c_str ());

				// Si no hay nombre, se devuelve.
				if (id.empty())
					return false;

				// Si encuentra la entidad, la crea.
				//shared_ptr<Entity> entity(new Entity (this));
				shared_ptr<Entity> entity(new Entity(instance));

				// Busca los componentes de la entidad
				for (xml_node<> * child = entityTag->first_node(); child; child = child->next_sibling())
				{
					if (child->type() == node_element)
					{
						if (string(child->name()) == "components")
						{
							if (!ParseComponents(child, *entity))
								return false;
						}
					}
				}

				// Guarda la entidad en el mapa.
				entities[id] = entity;
			}
		}
		return true;
	}

	bool Scene::ParseComponents(xml_node<> * componentsTag, Entity & entity)
	{
		for (xml_node<> * componentTag = componentsTag->first_node(); componentTag; componentTag = componentTag->next_sibling())
		{
			if (componentTag->type() == node_element)
			{
				string type;
				printf(type.c_str());
				// Busca el tipo del componente.
				for (xml_attribute<> * attribute = componentTag->first_attribute(); attribute; attribute = attribute->next_attribute())
				{
					printf(" / ");
					printf(attribute->value());
					printf(" / ");

					if (string(attribute->name()) == "type")//ESTE BULBE SOLO COGE EL PRIMERO de los componets*********************???????????
					{
						type = attribute->value();

						if (string(attribute->value()) == "transform")
						{
							ParseTransform(componentTag, entity);
						}
						else if (string(attribute->value()) == "render")
						{
							ParseRender(componentTag, entity);
						}
						else if (string(attribute->value()) == "controller")
						{
							ParseInputMove(entity);
						}

		
					}
				}

				// No hay tipo.
				if (type.empty()) return false;

			
			/*// Se crea el módulo. Tal vez haya sustituir todo esto
				if (modules.count(type) == 0)
				{
					modules[type] = Module::Create(type, instance);
				}

				// Se guarda el módulo.
				Module * module = modules[type].get();

				if (!module) return false;

				// Crea un componente a partir del módulo.
				shared_ptr<Component> component(module->CreateComponent(&entity));

				if (!component || !component->Parse(componentTag)) return false;

				// Añade el componente a la entidad.
				entity.AddComponent(type, component);*/

			}
		}

		return true;
	}

	vector<float> Split(const std::string &text)
	{
		char sep = ',';

		vector<float> tokens;
		std::size_t start = 0, end = 0;

		while ((end = text.find(sep, start)) != std::string::npos) {
			tokens.push_back(stof(text.substr(start, end - start)));
			start = end + 1;
		}

		tokens.push_back(stof(text.substr(start)));

		return tokens;
	}

	bool Scene::ParseRender(xml_node<> * render, Entity & entity)
	{
		string obj_file_path = "";

		for (xml_node<> * child = render->first_node(); child; child = child->next_sibling())
		{
			if (string(child->name()) == "mesh")
			{
				for (xml_attribute<> * attribute = child->first_attribute(); attribute; attribute = attribute->next_attribute())
				{
					if (string(attribute->name()) == "path")
					{
						obj_file_path = attribute->value();
					}
				}
				if (obj_file_path != "")
					ParseMesh(obj_file_path, entity);
			}
		}
		return true;
	}

	bool Scene::ParseInputMove(Entity & entity)
	{
		std::shared_ptr<TransformComponent> componentTr = dynamic_pointer_cast<TransformComponent>(entity.SetComponent("transform"));

		std::shared_ptr<RenderComponent> componentRnd = dynamic_pointer_cast<RenderComponent>(entity.SetComponent("render"));

		ControllerComponent * controllerComponent = new ControllerComponent(&entity, componentTr->GetTransform(), * componentRnd);

		std::shared_ptr<Component> component(controllerComponent);

		entity.AddComponent("controller", component);

		dispatcher.add_listener(2, *controllerComponent);
		dispatcher.add_listener(3, *controllerComponent);
		dispatcher.add_listener(4, *controllerComponent);
		dispatcher.add_listener(5, *controllerComponent);
		dispatcher.add_listener(6, *controllerComponent);

		return true;
	}

	bool Scene::ParseMesh(string obj_file_path, Entity & entity)
	{
		std::shared_ptr<Component> componet = entity.SetComponent("transform");

		std::shared_ptr<TransformComponent> componentTr = dynamic_pointer_cast<TransformComponent>(componet);

		std::shared_ptr<Component> component(new RenderComponent(&entity, windowTask.add_model(obj_file_path, componentTr->GetTransform())));

		entity.AddComponent("render", component);

		return true;
	}

	bool Scene::ParseTransform(xml_node<> * transform, Entity & entity)//sacar atributos transform,transform hereda de componet, el componente se añade a la entity
	{																//como se pasa al transformcomponent que recive esto

		vector<float> pos;
		vector<float> rot;
		float scale;

		for (xml_node<> * child = transform->first_node(); child; child = child->next_sibling())
		{


			if (string(child->name()) == "position")
			{
				pos = Split(string(child->value()));
			}
			else if (string(child->name()) == "rotation")
			{
				rot = Split(string(child->value()));
			}
			else if (string(child->name()) == "scale")
			{
				scale = stof(string(child->value()));
			}
		}
		
		std::shared_ptr<Component> component(new TransformComponent(&entity, pos, rot, scale));

		entity.AddComponent("transform", component);

		return true;
	}
}

