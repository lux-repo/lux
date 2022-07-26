/*
 * File:   SafeQueue.hpp
 * Author: chenhui yu
 * Created on December 27, 2020, 11:22 AM
 */
#pragma once

#include <condition_variable>
#include <mutex>
#include <queue>

namespace lux {
	namespace container {
		template <typename T>
		class SafeQueue
		{
			// ADD TIME OUT
		public:
			void push(const T& item)
			{
				{
					std::scoped_lock lock(_mtx);
					_queue.push(item);
				}
				_cond.notify_one();
			}

			void push(T&& item)
			{
				{
					std::scoped_lock lock(_mtx);
					_queue.push(std::move(item));
				}
				_cond.notify_one();
			}

			bool pop(T& item)
			{
				std::unique_lock lock(_mtx);
				_cond.wait(lock,
					[&]() { return !_queue.empty() || _stop; }
				);
				if (_queue.empty() || _stop)
					return false;
				item = std::move(_queue.front());
				_queue.pop();
				return true;
			}

			std::size_t size() const
			{
				std::scoped_lock lock(_mtx);
				return _queue.size();
			}

			bool empty() const
			{
				std::scoped_lock lock(_mtx);
				return _queue.empty();
			}

			void stop()
			{
				{
					std::scoped_lock lock(_mtx);
					_stop = true;
				}
				_cond.notify_all();
			}

		private:
			std::condition_variable _cond;
			mutable std::mutex _mtx;
			std::queue<T> _queue;
			bool _stop{ false };
		};
	}
}