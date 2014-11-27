#ifndef STORAGE_H_HH
#define STORAGE_H_HH

#include <string>
#include <map>


typedef struct gene {
    std::string name;
    std::string chromosome;
    std::string sequence;
    int cluster;
    std::map<std::string, double> codon_freqs;
} Gene;

static std::ofstream& operator<<(std::ofstream &out, Gene &g) {
    out << g.name << " " << g.chromosome << " " << g.sequence << " " << g.cluster;
    return out;
}

static std::istream& operator>>(std::istream &in, Gene &g) {
    in >> g.name >> g.chromosome >> g.sequence >> g.cluster;
    return in;
}

#endif
