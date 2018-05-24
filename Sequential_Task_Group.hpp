#pragma once

#include "Task_Group.hpp"

namespace RaghallaighEngine
{
	/*
	*Lista de tareas secuencial, util para tareas que dependen unas de otras
	*/
	class Sequential_Task_Group : public Task_Group
	{
	public:

		Sequential_Task_Group(int priority) : Task_Group(priority) { }

		/*
		*Ejecuta la lista de tareas secuencialmente
		*/
		void run()
		{
			for (auto & task : task_list)
			{
				task->run();

				// Combrobamos si hay tareas finalizadas de la lista

				if (task->is_finished())
				{
					//si es asi, las finalizamos y sacamos de la lista
					task->finalize();
					task_list.remove(task);
				}
			}
		}
	};
}