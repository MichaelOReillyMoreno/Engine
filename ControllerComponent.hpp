#ifndef MOVE_COMPONENT_HEADER
#define MOVE_COMPONENT_HEADER

#include "Component.hpp"
#include "Dispatcher.hpp"
#include "Transform\TransformComponet.hpp"
#include "RenderComponent.hpp"

#include <memory>
#include <stdio.h>

namespace RaghallaighEngine
{
	/*
	* Mueve un personaje.
	* Ejemplo de como seria un listener
	*/
	class ControllerComponent : public Component, public Listener
	{

	private:

		enum Inputs { JUMP = 2, RIGHT = 3, LEFT = 4, DOWN = 5, UP = 6 };

		//referencia a matrix del componente tranform
		glt::Matrix44 & transform_mtrx;

		//referencia al componente render sobre el que al recibir inputs aplicará el movimiento
		RenderComponent & renderComponent;
	public:

		ControllerComponent(Entity * entity, Matrix44 & _transform_mtrx, RenderComponent & _renderComponent) :
							Component(entity), transform_mtrx(_transform_mtrx), renderComponent(_renderComponent){}

		~ControllerComponent()
		{
			int i = 0;
		}

		void  Initialize() {}

		void Update(float deltaTime) {}
		bool Parse(const xml_node<> * node) { return true; }

		void handle(const Message & message) override;

	};

}

#endif
