#include "include/climage.hpp"
#include <fstream>

int main() noexcept {
    std::ifstream file("example.climg");
    std::string data;
    for(std::string temp; std::getline(file, temp); data.append(temp + "\n"))
        ; file.close();

    climage x;

    x.parse(data);
    x.generate();
}