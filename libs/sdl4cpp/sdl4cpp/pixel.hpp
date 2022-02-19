// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef SDL4CPP_PIXEL_HPP
#define SDL4CPP_PIXEL_HPP

#include "sdl4.hpp"

namespace sdl4 {
    namespace pixel {
        class pixel_format {
        public:
            SDL_PixelFormat* main;
        public:
            pixel_format() = default; ~pixel_format() { this->free_format(); };

            void alloc_format(std::uint32_t pixel_format) { this->main = SDL_AllocFormat(pixel_format); }
            void free_format() { SDL_FreeFormat(this->main); }

            std::uint32_t map_rgb(std::uint8_t r, std::uint8_t g, std::uint8_t b) {
                return SDL_MapRGB(this->main, r, g, b);
            }

            std::uint32_t map_rgba(std::uint8_t r, std::uint8_t g, std::uint8_t b, std::uint8_t a) {
                return SDL_MapRGBA(this->main, r, g, b, a);
            }
        };

        class color {
        public:
            std::uint8_t r, g, b, a;
        public:
            color() = default; ~color() = default;

            static SDL_Color* to(color cl) {
                SDL_Color* sdl_color;
                sdl_color->r = cl.r;
                sdl_color->g = cl.g;
                sdl_color->b = cl.b;
                sdl_color->a = cl.a; return sdl_color;
            }

            static color from(SDL_Color* cl) {
                return color {
                    .r = cl->r,
                    .g = cl->g,
                    .b = cl->b,
                    .a = cl->a
                };
            }
        };

        class palette {
        public:
            int n_colors;
            color colors;
            std::uint32_t version;
            int ref_count;
        public:
            palette() = default; ~palette() = default;

            static SDL_Palette* to(palette pl) {
                SDL_Palette* sdl_palette;
                sdl_palette->ncolors = pl.n_colors;
                sdl_palette->colors = sdl4::pixel::color::to(pl.colors),
                sdl_palette->version = pl.version,
                sdl_palette->refcount = pl.ref_count; return sdl_palette;
            }

            static palette from(SDL_Palette* pl) {
                return palette {
                    .n_colors = pl->ncolors,
                    .colors = sdl4::pixel::color::from(pl->colors),
                    .version = pl->version,
                    .ref_count = pl->refcount
                };
            }

            int set_palette_colors(const sdl4::pixel::color colors, int first_color, int n_colors) {
                return SDL_SetPaletteColors(this->to(palette {
                    .n_colors = this->n_colors,
                    .colors = this->colors,
                    .version = this->version,
                    .ref_count = this->ref_count
                }), sdl4::pixel::color::to(colors), first_color, n_colors);
            }
        };

        sdl4::pixel::palette palette(int n_colors) { return sdl4::pixel::palette::from(SDL_AllocPalette(n_colors)); }

        void free_palette(SDL_Palette* palette) { SDL_FreePalette(palette); }

        void calculate_gamma_ramp(float gamma, std::uint16_t* ramp) { SDL_CalculateGammaRamp(gamma, ramp); }

        const std::string get_pixel_format_name(std::uint32_t format) {
            return sdl4::convert(SDL_GetPixelFormatName(format));
        }

        std::uint32_t masks_to_pixel_format_enum(int bpp, std::uint32_t r, std::uint32_t g, std::uint32_t b, std::uint32_t a) {
            return SDL_MasksToPixelFormatEnum(bpp, r, g, b, a);
        }

        bool pixel_format_enum_to_masks(std::uint32_t format, int* bpp,
                                        std::uint32_t* r, std::uint32_t* g, std::uint32_t* b, std::uint32_t* a) {
            return ((SDL_PixelFormatEnumToMasks(format, bpp, r, g, b, a) == SDL_bool::SDL_TRUE) ? true : false);
        }
    }
}


#endif // SDL4CPP_PIXEL_HPP
