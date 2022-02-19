// MIT License
//
// Copyright (c) 2022 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#include <fstream>
#include "../include/imavie.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../libs/stb_image.h"
#include "../libs/sdl4cpp/sdl4cpp/sdl4.hpp"
#include "../libs/sdl4cpp/sdl4cpp/video.hpp"
#include "../libs/sdl4cpp/sdl4cpp/timer.hpp"

void imavie::run(std::string const file_name) noexcept {
    const std::string extension = file_name.substr(file_name.find_last_of(".") + 1);
    if(extension == "climg") {
        std::ifstream stream(file_name);

        for(std::string temp; std::getline(stream, temp);
            this->file_data.append(temp + "\n"))
        ; stream.close();

        this->parse.parse(this->file_data);
        this->data = this->parse.layer;
    } else if(extension != "png") {
        int w = 0, h = 0, glob_y = 0;
        unsigned char* val = stbi_load(file_name.c_str(), &w, &h, &this->comp, STBI_default);
        this->data.resize(w, std::vector<climage_rgb>(h, climage_rgb {
            .r = 0, .g = 0, .b = 0
        }));

        for(unsigned x = 0; x < w; x++) {
            for(unsigned y = 0; y < h; y++) {
                this->data[x][y].r = static_cast<unsigned>(val[glob_y++]);
                this->data[x][y].g = static_cast<unsigned>(val[glob_y++]);
                this->data[x][y].b = static_cast<unsigned>(val[glob_y++]);
            }
        }

        this->parse.layer = this->data;
        this->parse.generate();

        // for(auto& val : this->data) {
        //    for(auto& qq : val) {
        //        std::cout << "(" << qq.r << " " << qq.g << " " << qq.b << ") ";
        //    }
        //
        //    std::cout << '\n';
        //}

        stbi_image_free(val);
    } else {
        int w = 0, h = 0, glob_y = 0;
        unsigned char* val = stbi_load(file_name.c_str(), &w, &h, &this->comp, STBI_default);
        this->data.resize(w, std::vector<climage_rgb>(h, climage_rgb {
            .r = 0, .g = 0, .b = 0
        }));

        for(unsigned x = 0; x < w; x++) {
            for(unsigned y = 0; y < h; y++) {
                this->data[x][y].r = static_cast<unsigned>(val[glob_y++]);
                this->data[x][y].g = static_cast<unsigned>(val[glob_y++]);
                this->data[x][y].b = static_cast<unsigned>(val[glob_y++]);

                ++glob_y;
            }
        }

        this->parse.layer = this->data;
        this->parse.generate();

        stbi_image_free(val);
    }

    sdl4::video::window::window wnd;
    sdl4::video::window::renderer::renderer renderer;


    if(sdl4::init(SDL_INIT_VIDEO) != 0) return;

    if(wnd.create_window_and_renderer(this->res_x,
                                      this->res_y,
                                      0,
                                      &renderer) == 0) {
        wnd.set_window_title("imavie - " + file_name);
        unsigned x = 0, y = 0, i = 0;
        for(auto& line: this->data) {
            va: for(auto& child: line) {
                renderer.set_render_draw_color(child.r, child.g, child.b, SDL_ALPHA_OPAQUE);
                renderer.render_draw_point(x, y);

                for(unsigned f = 0; f < this->scale; f++)
                    renderer.render_draw_point(++x, y);

            } ++i; x = 0; ++y; if(i < this->scale) goto va; i = 0;
        }

        renderer.render_present();
        sdl4::timer::delay(3500);
    }

    sdl4::quit();
}

int main(int argc, char const* const* argv) noexcept {
    if(argc < 2) {
        std::cout << "imavie - climage, jpeg and png viewer\n"
                    "------\n" <<
                    argv[0] << " {file}\n" <<
                    argv[0] << " {file} {x} {y} {scale_ratio}\n";
        return 1;
    }

    imavie x;

    if(argc > 3) {
        x.res_x = std::atoi(argv[2]);
        x.res_y = std::atoi(argv[3]);
        if(argc > 4) x.scale = std::atoi(argv[4]);
    }
    x.argc = argc;
    x.run(std::string(argv[1]));
}