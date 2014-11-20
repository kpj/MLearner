#ifndef UTILS_H_HH
#define UTILS_H_HH

#include <vector>
#include <string>


class Utils {
public:
    static std::vector<std::string> split(const std::string &str, char deli);
    static int rand_int(int min, int max);
};

#endif
