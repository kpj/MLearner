#ifndef STORAGE_H_HH
#define STORAGE_H_HH

#include <string>
#include <map>


typedef struct gene {
    std::string name;
    std::string chromosome;
    std::map<std::string, double> codon_freqs;
} Gene;

#endif
