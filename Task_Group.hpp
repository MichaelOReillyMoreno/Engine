#pragma once

#include "Tasks.hpp"

namespace RaghallaighEngine
{

	/*
	*Representa un grupo de tareas para el kernel, sirve de clase base para tipos de tareas agrupadas
	*/
	class Task_Group : public Task
	{
	protected:

		typedef std::list< Task * > Task_List;

		Task_List task_list;

	public:

		Task_Group(int priority) : Task(priority) { }

		/*
		*Añade una tarea
		*/
		void Add(Task & task)
		{
			task_list.push_back(&task);
		}

		/*
		*Iniciliza las tareas
		*/
		void initialize()
		{
			for (auto & task : task_list) task->initialize();
		}

		/*
		*Finaliza las tareas
		*/
		void finalize()
		{
			for (auto & task : task_list) task->finalize();
		}
	};
}