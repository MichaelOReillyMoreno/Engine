#include <Model.hpp>
#include "RenderComponent.hpp"

void RaghallaighEngine::RenderComponent::SetTransformation(glt::Matrix44 & transform)
{
	model->set_transformation(transform);
}
