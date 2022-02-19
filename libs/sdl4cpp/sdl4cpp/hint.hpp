// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_HINT_HPP
#define SDL4CPP_HINT_HPP

#include "sdl4.hpp"

namespace sdl4 {
    namespace hint {
        namespace priority {
            enum class priority {
                Default,
                Normal,
                Override
            };

            SDL_HintPriority from(sdl4::hint::priority::priority pr) {
                switch(pr) {
                    case sdl4::hint::priority::priority::Default:
                        return SDL_HintPriority::SDL_HINT_DEFAULT;


                    case sdl4::hint::priority::priority::Normal:
                        return SDL_HintPriority::SDL_HINT_NORMAL;

                    case sdl4::hint::priority::priority::Override:
                        return SDL_HintPriority::SDL_HINT_OVERRIDE;
                }

                return SDL_HintPriority::SDL_HINT_NORMAL;
            }
        }

        class callback {
        public:
            SDL_HintCallback* cb;
        public:
            callback() = default; ~callback() = default;

            template<typename Data>
            void add_hint_callback(const std::string name,
                                   Data user_data) {
                SDL_AddHintCallback(name.c_str(), this->cb, user_data);
            }

            template<typename Data>
            void delete_hint_callback(const std::string name,
                                      Data user_data) {
                SDL_DelHintCallback(name.c_str(), this->cb, user_data);
            }
        };

        void clear() {
            SDL_ClearHints();
        }

        const std::string get(const std::string name) {
            return std::string(SDL_GetHint(name.c_str()));
        }

        bool get_boolean(const std::string name,
                         bool default_value) {
            return ((SDL_GetHintBoolean(name.c_str(),
                                        (default_value == true) ?
                                        SDL_bool::SDL_TRUE :
                                        SDL_bool::SDL_FALSE) == SDL_bool::SDL_TRUE) ? true : false);
        }

        bool set(const std::string name,
                 const std::string value) {
            return (SDL_SetHint(name.c_str(), value.c_str()) == SDL_bool::SDL_TRUE ? true : false);
        }

        bool set_with_priority(const std::string name,
                               const std::string value,
                               sdl4::hint::priority::priority pr) {
            return (SDL_SetHintWithPriority(name.c_str(), value.c_str(),
                                            sdl4::hint::priority::from(pr)) == SDL_bool::SDL_TRUE ? true : false);
        }
    }
}

#endif // SDL4CPP_SDL4HINT_HPP
