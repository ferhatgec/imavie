// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_TIMER_HPP
#define SDL4CPP_TIMER_HPP

#include "sdl4.hpp"

namespace sdl4 {
    namespace timer {
        template<typename Param>
        SDL_TimerID add_timer(std::uint32_t interval, SDL_TimerCallback cb, Param param) {
            return SDL_AddTimer(interval, cb, param);
        }

        void delay(std::uint32_t ms) { SDL_Delay(ms); }

        std::uint64_t get_performance_counter() { return SDL_GetPerformanceCounter(); }
        std::uint64_t get_performance_frequency() { return SDL_GetPerformanceFrequency(); }
        std::uint32_t get_ticks() { return SDL_GetTicks(); }
        bool remove_timer(SDL_TimerID id) { return ((SDL_RemoveTimer(id) == SDL_bool::SDL_TRUE) ? true : false); }
    }
}

#endif // SDL4CPP_TIMER_HPP
