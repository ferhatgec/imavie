// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_VERSION_HPP
#define SDL4CPP_VERSION_HPP

#include "sdl4.hpp"

namespace sdl4 {
    namespace version {
        class version {
        public:
            const std::uint8_t
                major = SDL_MAJOR_VERSION,
                minor = SDL_MINOR_VERSION,
                patch = SDL_PATCHLEVEL;
        public:
            version() = default; ~version() = default;

            const std::string revision() noexcept {
                return std::string(SDL_GetRevision());
            }

            int revision_number() noexcept {
                return SDL_GetRevisionNumber();
            }
        };
    }
}

#endif // SDL4CPP_VERSION_HPP
