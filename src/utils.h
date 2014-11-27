#ifndef UTILS_H_HH
#define UTILS_H_HH

#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>


class Utils {
public:
    static std::vector<std::string> split(const std::string &str, char deli);
    static int rand_int(int min, int max);

    template <class T>
    static void saveClusters(std::string, std::vector< std::vector<T> >);
    template <class T>
    static std::vector<T> readClusters(std::string);
    template <class T>
    static std::vector< std::vector<T> > parseClusters(std::vector<T>);
};


template <class T>
void Utils::saveClusters(std::string fname, std::vector< std::vector<T> > clusters) {
    std::vector<T> all;

    // store cluster information
    for(std::size_t i = 0 ; i < clusters.size() ; i++) {
        std::vector<T> clus = clusters[i];

        for(std::size_t j = 0 ; j < clus.size() ; j++) {
            T e = clus[j];
            e.cluster = i;
            all.push_back(e);
        }
    }

    // save
    std::replace(fname.begin(), fname.end(), '/', '_');

    std::stringstream ss;
    ss << fname << ".dat";
    std::ofstream fout(ss.str());

    for(std::size_t i = 0 ; i < all.size() ; i++) {
        fout << all[i] << std::endl;
    }

    fout.close();
}

template <class T>
std::vector<T> Utils::readClusters(std::string fname) {
    std::vector<T> all;
    std::ifstream fin(fname);

    T e;
    while(fin >> e) {
        all.push_back(e);
    }

    fin.close();
    return all;
}

template <class T>
std::vector< std::vector<T> > Utils::parseClusters(std::vector<T> eles) {
    std::vector< std::vector<T> > clusters;

    // get cluster k
    int k = -1;
    for(std::size_t i = 0 ; i < eles.size() ; i++) {
        T e = eles[i];
        if(e.cluster > k) k = e.cluster; // does every element have cluster property?
    }
    k++;

    for(std::size_t i = 0 ; i < k ; i++) {
        std::vector<T> clus;
        clusters.push_back(clus);
    }

    // generate clusters
    for(std::size_t i = 0 ; i < eles.size() ; i++) {
        T e = eles[i];
        clusters[e.cluster].push_back(e);
    }

    return clusters;
}

#endif
