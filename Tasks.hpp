#pragma once
#ifndef TASK_HEADER
#define TASK_HEADER

#include <list>
#include <string>
#include <iostream>

namespace RaghallaighEngine
{
	class Task
	{

	protected:
		int  priority;
		bool finished;

	public:

		Task(int priority, bool finished = false) : priority(priority), finished(finished) { }

		bool is_finished() const
		{
			return finished;
		}

		virtual void initialize() = 0;
		virtual void finalize() = 0;
		virtual void run() = 0;

		bool operator < (const Task & other) const
		{
			return this->priority < other.priority;
		}

		bool operator > (const Task & other) const
		{
			return this->priority > other.priority;
		}
	};
}
#endif