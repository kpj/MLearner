#include <iostream>
#include <sstream>
#include <fstream>

#include "analyzer.h"


void Analyzer::save(std::string fname, std::map<std::string, double> freqs) {
    std::ofstream fout(fname.c_str());

    fout << "Codon,Frequency" << std::endl;
    for(std::map<std::string, double>::const_iterator it = freqs.begin() ; it != freqs.end() ; it++) {
        fout << it->first << "," << it->second << std::endl;
    }

    fout.close();
}

std::map<std::string, double> Analyzer::compute_frequencies(std::string sequence, bool reading_frame) {
    std::map<std::string, double> freqs;
    int step = (reading_frame)?3:1;

    int triplet_num = 0;
    for(std::size_t i = 0 ; i < sequence.size()-2 ; i+=step) {
        std::stringstream ss;
        ss << sequence[i] << sequence[i+1] << sequence[i+2];
        std::string triplet = ss.str();

        freqs[triplet]++;
        triplet_num++;
    }

    for(std::map<std::string, double>::const_iterator it = freqs.begin() ; it != freqs.end() ; it++) {
        freqs[it->first] /= triplet_num;
    }

    return freqs;
}

void Analyzer::cluster_stats(std::vector< std::vector<Gene> > clusters) {
    for(std::size_t i = 0 ; i < clusters.size() ; i++) {
        std::cout << "Cluster #" << i << std::endl;
        double nums[8] = {0, 0, 0, 0, 0, 0, 0, 0}; // chrom. 1-6, NA, misc

        std::vector<Gene> clus = clusters[i];
        for(std::size_t j = 0 ; j < clus.size() ; j++) {
            std::string id = clus[j].chromosome;
            if(id == "NA") {
                nums[6]++;
            } else if(id == "M" || id == "BF") {
                nums[7]++;
            } else {
                int ind = std::stoi(id);
                nums[ind-1]++;
            }
        }
        for(std::size_t j = 0 ; j < 8 ; j++) {
            nums[j] /= clus.size();

            if(j < 6) {
                std::cout << "> Chromosome #" << (j+1);
            } else if(j == 6) {
                std::cout << "> NA";
            } else {
                std::cout << "> misc";
            }
            std::cout  << ": " << nums[j] << std::endl;
        }
        std::cout << std::endl;
    }
}
