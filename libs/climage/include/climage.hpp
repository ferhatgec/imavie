// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
// climage - an image format for commandline.
//
// github.com/ferhatgec/climage
//

#ifndef CLIMAGE_CLIMAGE_HPP
#define CLIMAGE_CLIMAGE_HPP

#include <string>
#include <vector>
#include <iostream>
#include "climage_markers.hpp"

class climage_rgb {
public:
    unsigned r, g, b;
public:
    climage_rgb() = default;
    ~climage_rgb()= default;

    void from_hex(std::string hex) noexcept {
        if(hex.front() == '#') { hex.pop_back(); }

        int __hex = std::stol(hex, nullptr, 16);

        this->r = (__hex >> 16) & 0xFF;
        this->g = (__hex >> 8) & 0xFF;
        this->b = __hex & 0xFF;
    }
};


class climage {
public:
    unsigned width, height;
    climage_rgb init;
    std::vector<climage_rgb> layer_1d;

    std::vector<std::vector<climage_rgb>> layer;

    bool sof = false,
         sof2 = false,
         sof3 = false,
         sof4 = false,
         sof5 = false,
         sof6 = false,
         ok = false,
         sow = false,
         soh = false,
         color_start = false;

    std::string current_hex;

    std::string generated_text_image;

    const std::string color = "\x1b[48;2;";
    const std::string character = "░░";
public:
    climage() = default;
    ~climage()= default;

    std::string color_generate(climage_rgb& color) noexcept {
        return this->color + std::to_string(color.r) + ";"
                           + std::to_string(color.g) + ";"
                           + std::to_string(color.b) + "m";
    }

    void generate() noexcept {
        for(auto& line : this->layer) {
            for(auto& child : line) {
                this->generated_text_image.append(
                        this->color_generate(child) + this->character + "\x1b[0m");
            }

            this->generated_text_image.push_back('\n');
        } this->generated_text_image.append("\x1b[0m");

        std::cout << this->generated_text_image << '\n';
    }

    void parse(const std::string data) noexcept {
        for(auto& ch : data) {
            if(ch == '\n' && this->layer_1d.size() > 0) {
                this->layer.push_back(this->layer_1d);
                this->layer_1d.clear();
                continue;
            }

            if(this->color_start) {
                if(ch != Continue)
                    this->current_hex.push_back(ch);
                else {
                    this->init.from_hex(this->current_hex);
                    this->layer_1d.push_back(this->init);
                    this->color_start = false;
                    this->current_hex.clear();
                }

                continue;
            }

            switch(ch) {
                case SOF: {
                    this->sof = true;
                    break;
                }

                case SOF2: {
                    this->sof2 = true;
                    break;
                }

                case SOF3: {
                    this->sof3 = true;
                    break;
                }

                case SOF4: {
                    this->sof4 = true;
                    break;
                }

                case SOF5: {
                    this->sof5 = true;
                    break;
                }

                case SOF6: {
                    this->sof6 = true;

                    if(this->sof
                    && this->sof2
                    && this->sof3
                    && this->sof4
                    && this->sof5
                    && this->sof6) {
                        this->ok = true;
                    } else {
                        std::cerr << "SOF markers are not defined\n";
                    }

                    break;
                }

                case SOW: {
                    this->sow = true;
                    break;
                }

                case SOH: {
                    this->soh = true;
                    break;
                }

                case Pixel8:
                case Pixel16:
                case Pixel32:
                case Pixel64: {
                    if(this->sow || this->soh) {
                        switch(ch) {
                            case Pixel8: {
                                if(this->sow)
                                    this->width = 8;
                                else
                                    this->height = 8;

                                break;
                            }

                            case Pixel16: {
                                if(this->sow)
                                    this->width = 16;
                                else
                                    this->height = 16;

                                break;
                            }

                            case Pixel32: {
                                if(this->sow)
                                    this->width = 32;
                                else
                                    this->height = 32;

                                break;
                            }

                            case Pixel64: {
                                if(this->sow)
                                    this->width = 64;
                                else
                                    this->height = 64;

                                break;
                            }
                        }
                    }

                    break;
                }

                case ColorStart: {
                    this->color_start = true;
                    break;
                }
            }
        }

        // for(auto& x : this->layer) {
        //    for(auto& y : x) {
        //        std::cout << "(" << y.r << ", " << y.g << ", " << y.b << ") ";
        //    }
        //    std::cout << '\n';
        //}
    }
};

#endif // CLIMAGE_CLIMAGE_HPP
