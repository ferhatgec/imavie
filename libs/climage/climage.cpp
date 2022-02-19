// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
// climage - an image format for commandline.
//
// github.com/ferhatgec/climage
//

#include "include/climage.hpp"
#include <fstream>

int main(int argc, char** argv) noexcept {
    if(argc < 2) {
        std::cout << "climage - an image format for commandline\n"
                     "\n" <<
                     argv[0] << " {file}\n";

        return 1;
    }

    std::ifstream file(argv[1]);
    std::string data;

    for(std::string temp; std::getline(file, temp); data.append(temp + "\n"))
        ; file.close();

    climage x;

    x.parse(data);
    x.generate();
}