#include <sstream>

#include <cstdlib>

#include "utils.h"


std::vector<std::string> &split_helper(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}


std::vector<std::string> Utils::split(const std::string &s, char delim) {
    std::vector<std::string> elems;
    split_helper(s, delim, elems);
    return elems;
}


int Utils::rand_int(int min, int max) {
    return min + (std::rand() % (int) (max - min + 1));
}
