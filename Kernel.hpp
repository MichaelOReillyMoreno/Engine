#pragma once
#ifndef KERNEL_HEADER
#define KERNEL_HEADER
#include "Tasks.hpp"

namespace RaghallaighEngine
{
	/**
	* Gestiona todas las tareas del juego
	*/
	class Kernel
	{
		typedef std::list< Task * > Task_List;

		/**
		* lista de tareas del juego
		*/
		Task_List task_list;
		bool      exit;

	public:

		/**
		* ejecuta el kernel, inicializa sus tareas y comienza su buble principal
		*/
		void execute()
		{
			exit = false;

			for (auto iterator = task_list.begin(); iterator != task_list.end() && !exit; ++iterator)
			{
				Task * task = *iterator;

				task->initialize();
			}

			while (!exit)
			{
				for (auto iterator = task_list.begin(); iterator != task_list.end() && !exit; ++iterator)
				{
					Task * task = *iterator;

					task->run();

					if (task->is_finished())
					{
						task->finalize();

						task_list.erase(iterator);
					}
				}

				if (exit) break;
			}
		}

		/**
		* para el bucle del kernel
		*/
		void stop()
		{
			exit = true;
		}

		/**
		* añade una nueva tarea
		*/
		void Add(Task & task)
		{
			// Se añade la tarea a la lista de tareas:

			task_list.push_back(&task);

			// Se reordena la lista por prioridad de ejecución
			// de las tareas:

			task_list.sort(compare);
		}

		/**
		* compara dos tareas
		*/
		static bool compare(const Task * a, const Task * b)
		{
			return *a < *b;
		}

	};
}
#endif