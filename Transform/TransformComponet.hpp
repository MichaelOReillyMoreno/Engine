#ifndef TRANSFORM_COMPONENT_HEADER
#define TRANSFORM_COMPONENT_HEADER

#include <Math.hpp>
#include <vector>

#include "../Component.hpp"
using namespace glt;

	namespace RaghallaighEngine
	{
		/*
		* Represesta un componente transform de una entidad, es decir, contiene en una matriz de 4 x 4 su poscion, escala, rotacion.
		*/
		class TransformComponent : public Component
		{

			glt::Matrix44 transform_mtrx;

		public:

			TransformComponent(Entity * entity, std::vector<float> & pos, std::vector<float> & rot, float & scale) : Component(entity), transform_mtrx(glt::Matrix44())
			{
				transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(pos[0], pos[1], pos[2])) *
					glt::rotate_around_x(transform_mtrx, rot[0]) * glt::rotate_around_y(transform_mtrx, rot[1])
					* glt::rotate_around_z(transform_mtrx, rot[2]) * glt::scale(transform_mtrx, scale);
			}

			void  Initialize() {}

			void Update(float deltaTime) {}
			bool Parse(const xml_node<> * node) { return true; }

			glt::Matrix44 & GetTransform()
			{
				return transform_mtrx;
			}
		};

	}

#endif
