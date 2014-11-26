#ifndef UTILS_H_HH
#define UTILS_H_HH

#include <vector>
#include <string>
#include <sstream>


class Utils {
public:
    static std::vector<std::string> split(const std::string &str, char deli);
    static int rand_int(int min, int max);

    template <class T>
    static void saveClusters(std::string, std::vector< std::vector<T> >);
};


template <class T>
void Utils::saveClusters(std::string prefix, std::vector< std::vector<T> > clusters) {
    for(std::size_t i = 0 ; i < clusters.size() ; i++) {
        std::vector<T> clus = clusters[i];
        std::stringstream ss;
        ss << prefix << i << ".dat";
        std::ofstream out(ss.str());

        for(std::size_t j = 0 ; j < clus.size() ; j++) {
            out << clus[j] << std::endl;
        }
    }
}

#endif
