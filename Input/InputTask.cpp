#include "InputTask.hpp"
#include "../Message.hpp"
#include "../Dispatcher.hpp"

void RaghallaighEngine::InputTask::initialize()
{

}

void RaghallaighEngine::InputTask::finalize()
{

}

void RaghallaighEngine::InputTask::run()
{
	sf::Event event_sf;

	while (window->pollEvent(event_sf))
	{
		if (event_sf.type == sf::Event::Closed)
		{
			Message message(0);	//kernel stop();
		}
		else if (event_sf.type == sf::Event::KeyPressed)
		{
			Check_InputKey_Events(event_sf.key.code);
		}
	}
}

void RaghallaighEngine::InputTask::Check_InputKey_Events(sf::Keyboard::Key keyEvent)
{
	for (InputEvent const& event : events)
	{
		if (event.CheckAssignedKeys(keyEvent))
		{
			Message message(event.id);
			string s = std::to_string(event.id);

			dispacher.send(message);
		}
	}
}

bool RaghallaighEngine::InputTask::LoadInputSettings(const std::string & sceneInfo)
{
	fstream xml_file(sceneInfo, fstream::in);

	if (xml_file.good())
	{
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
				finished = true;
				xml_content.push_back(0);
			}


		} while (!finished);

		xml_document< > document;
		document.parse< 0 >(xml_content.data());
		xml_node< > * node = document.first_node();

	
		if (node)
			PaseInputSettings(node);
	}

	return false;
}

bool RaghallaighEngine::InputTask::PaseInputSettings(xml_node<>* inputNode)
{
	for (xml_node<> * eventKeys = inputNode->first_node(); eventKeys; eventKeys = eventKeys->next_sibling())
	{
		if (eventKeys->type() == node_element)
		{
			if (string(eventKeys->name()) == "event")
			{
				PaseEvent(eventKeys);
			}
		}
	}

	return true;
}

bool RaghallaighEngine::InputTask::PaseEvent(xml_node<>* eventKeys) 
{
	if (eventKeys->first_attribute("id")->value())
	{
		string strId = eventKeys->first_attribute("id")->value();
		InputEvent inputEvent(atoi(strId.c_str()));

		for (xml_node<> * key = eventKeys->first_node(); key; key = key->next_sibling())
		{
			if (key->type() == node_element)
			{
				if (string(key->name()) == "key")
				{
					inputEvent.AddKey(std::stoi(key->value()));
				}
			}
		}

		events.push_back(inputEvent);
		return true;
	}

	return false;
}
