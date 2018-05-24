#ifndef RENDER_COMPONENT_HEADER
#define RENDER_COMPONENT_HEADER

#include "Component.hpp"

#include <memory>

using namespace std;

namespace glt
{
	class Model;
}

namespace RaghallaighEngine
{
	/*
	* Represesta un componente Render de una entidad, es decir, contiene el modelo glt.
	*/
	class RenderComponent : public Component
	{
		shared_ptr< glt::Model > model;

	public:

		RenderComponent(Entity * entity, shared_ptr< glt::Model > _model) : Component(entity), model(_model){}

		/*
		* Aplica una transformacion sobre el modelo 3D el modelo glt.
		*/
		void SetTransformation(glt::Matrix44 & transform);

		void  Initialize() {}

		void Update(float deltaTime) {}
		bool Parse(const xml_node<> * node) { return true; }

	};

}

#endif
