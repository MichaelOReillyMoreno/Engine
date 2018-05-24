#include "ControllerComponent.hpp"

void RaghallaighEngine::ControllerComponent::handle(const Message & message)
{

	if (message.action_id == Inputs::JUMP)
	{
		transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(0, 0, 0.8));
		renderComponent.SetTransformation(transform_mtrx);
	}
	else if (message.action_id == Inputs::RIGHT)
	{
		transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(-0.1, 0, 0));
		renderComponent.SetTransformation(transform_mtrx);
	}
	else if (message.action_id == Inputs::LEFT)
	{
		transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(0.1, 0, 0));
		renderComponent.SetTransformation(transform_mtrx);
	}

	else if (message.action_id == Inputs::DOWN)
	{
		transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(0, -0.1, 0));
		renderComponent.SetTransformation(transform_mtrx);
	}
	if (message.action_id == Inputs::UP)
	{
		transform_mtrx = glt::translate(transform_mtrx, glt::Vector3(0, 0.1, 0));
		renderComponent.SetTransformation(transform_mtrx);
	}
}
