#pragma once
#include <chrono>
#include <functional>

namespace hui {
    namespace tools {

        class SocpeTimeCounter
        {
            using _stdTP = decltype(std::chrono::high_resolution_clock::now());
        public:
            using TPDif = decltype(_stdTP() - _stdTP());

            SocpeTimeCounter(const std::function<void(TPDif)>& func)
                : _begin_time(std::chrono::high_resolution_clock::now()), _cb(func)
            {}

            static inline int64_t milli(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::milliseconds>(dif).count();
            }

            static inline int64_t micro(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::microseconds>(dif).count();
            }

            static inline int64_t nano(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::nanoseconds>(dif).count();
            }

            static inline int64_t seconds(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::seconds>(dif).count();
            }

            static inline int64_t minutes(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::minutes>(dif).count();
            }

            static inline int64_t hours(TPDif dif)
            {
                return std::chrono::duration_cast<std::chrono::hours>(dif).count();
            }

            ~SocpeTimeCounter()
            {
                if (_cb) _cb(std::chrono::high_resolution_clock::now() - _begin_time);
            }

        private:
            _stdTP _begin_time;
            std::function<void(TPDif)> _cb;
        };

    }
}