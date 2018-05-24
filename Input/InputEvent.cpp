#include "InputEvent.hpp"


void RaghallaighEngine::InputEvent::AddKey(int keyValue)
{
	switch (keyValue)
	{
	case 57:
		keys.push_back(Keyboard::Escape);
		break;
	case 36:
		keys.push_back(Keyboard::Space);
		break;
	case 0:
		keys.push_back(Keyboard::A);
		break;
	case 3:
		keys.push_back(Keyboard::D);
		break;
	case 18:
		keys.push_back(Keyboard::S);
		break;
	case 22:
		keys.push_back(Keyboard::W);
		break;
	}
}

bool const RaghallaighEngine::InputEvent::CheckAssignedKeys(const int & keyValue) const
{
	for (Keyboard::Key const& key : keys)
	{
		if (key == keyValue)
			return true;
	}
	return false;
}
