// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
// sdl4cpp - heavily work in progress c++ wrapper around sdl2.
//
// github.com/ferhatgec/sdl4cpp

#ifndef SDL4CPP_SDL4_HPP
#define SDL4CPP_SDL4_HPP

#include <string>
#include <SDL2/SDL.h>

namespace sdl4 {
    using main_func = SDL_main_func;

    namespace math {
        double acos(double x) noexcept {
            return SDL_acos(x);
        }
    }

    class SDL4 {
    public:
    public:
        SDL4() = default; ~SDL4() = default;
    };

    template<typename Arg>
    const std::string convert(Arg value) {
        return std::string(value);
    }

    int init(std::uint32_t flags) {
        return SDL_Init(flags);
    }

    int init_subsystem(std::uint32_t flags) {
        return SDL_InitSubSystem(flags);
    }

    void quit() {
        SDL_Quit();
    }

    void quit_subsystem(std::uint32_t flags) {
        return SDL_QuitSubSystem(flags);
    }

    void set_main_ready() {
        SDL_SetMainReady();
    }

    std::uint32_t was_init(std::uint32_t flags) {
        return SDL_WasInit(flags);
    }

    template<typename Arg>
    int winrt_run_app(sdl4::main_func main_function, Arg reserved) {
        return SDL_WinRTRunApp(main_function, reserved);
    }
}

#endif // SDL4CPP_SDL4_HPP
