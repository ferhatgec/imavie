// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_EVENT_HPP
#define SDL4CPP_EVENT_HPP

#include "sdl4.hpp"

namespace sdl4 {
    namespace event {
        class filter {
        public:
            SDL_EventFilter* main;
        public:
            filter() = default; ~filter() = default;

            template<typename Data>
            void add_event_watch(Data user_data) noexcept {
                SDL_AddEventWatch(this->main, user_data);
            }

            template<typename Data>
            void delete_event_watch(Data user_data) noexcept {
                SDL_DelEventWatch(this->main, user_data);
            }
        };

        std::uint8_t state(std::uint32_t type, int state) noexcept {
            return SDL_EventState(type, state);
        }
    }
}

#endif //SDL4CPP_SDL4EVENT_HPP
