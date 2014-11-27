#ifndef ANALYZER_H_HH
#define ANALYZER_H_HH

#include <string>
#include <vector>
#include <map>

#include "storage.h"


class Analyzer {
public:
    static std::map<std::string, double> compute_frequencies(std::string sequence, bool reading_frame);
    static void save(std::string fname, std::map<std::string, double> freqs);

    static void cluster_stats(std::vector< std::vector<Gene> > clusters);

    static std::vector<double> codonFreqs(std::string codon, std::vector< std::vector<Gene> > clusters);
};

#endif
