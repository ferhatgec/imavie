// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_ERROR_HPP
#define SDL4CPP_ERROR_HPP

#include <iostream>
#include "sdl4.hpp"

namespace sdl4 {
    namespace error {
        void clear() {
            SDL_ClearError();
        }

        const std::string get() {
            return sdl4::convert(SDL_GetError());
        }

#if __cplusplus >= 201703L
        template<typename... Arg>
        constexpr int set(Arg... val) noexcept {
            ((std::cout << val), ...); return -1;
        }
#else
        // from https://github.com/libsdl-org/SDL/blob/main/include/SDL_error.h
        extern DECLSPEC int SDLCALL set(SDL_PRINTF_FORMAT_STRING const char *fmt, ...) SDL_PRINTF_VARARG_FUNC(1);
#endif
    }
}

#endif // SDL4CPP_ERROR_HPP
