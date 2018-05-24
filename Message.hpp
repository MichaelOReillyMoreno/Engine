#pragma once



#include <unordered_map>
#include "Variant.hpp"

using namespace std;

namespace RaghallaighEngine
{
	/*
	* Representa un mensaje que recive el dispacher y que es a su vez enviado a los listeners
	*/
	class Message
	{
	public:
		int action_id;

	private:
		typedef std::unordered_map< int, Variant > Paramer_List;

		/*
		* parametros que contiene(de tipo variant)
		*/
		Paramer_List parameters;

	public:

		Message(int id) : action_id(id){}

		Variant & operator [] (int key)
		{
			return parameters[key];
		}

		bool operator == (const Message & other) const
		{
			return this->action_id == other.action_id;
		}

		bool operator != (const Message & other) const
		{
			return this->action_id != other.action_id;
		}

		operator int() const
		{
			return action_id;
		}

	};
}