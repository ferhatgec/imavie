// MIT License
//
// Copyright (c) 2022 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//

#ifndef IMAVIE_IMAVIE_HPP
#define IMAVIE_IMAVIE_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../libs/climage/include/climage.hpp"

class imavie {
    std::string file_data;
    climage parse;
    std::vector<std::vector<climage_rgb>> data;
public:
    int res_x = 128, res_y = 128, scale = 16, comp, argc = 0;
public:
    imavie() = default; ~imavie() = default;

    void run(std::string const file_name) noexcept;
};

#endif // IMAVIE_IMAVIE_HPP
