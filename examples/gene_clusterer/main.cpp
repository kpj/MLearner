#include <fstream>
#include <iostream>

#include "../../src/cluster.h"
#include "../../src/utils.h"

#include "FastA.h"
#include "data.h"
#include "storage.h"
#include "analyzer.h"


std::map<std::string, double> get_cluster_mean(std::vector<Gene> cluster) {
    std::map<std::string, double> mean;

    for(std::size_t i = 0 ; i < cluster.size() ; i++) {
        Gene g = cluster[i];

        for(std::map<std::string, double>::const_iterator it = g.codon_freqs.begin() ; it != g.codon_freqs.end() ; it++) {
            mean[it->first] += it->second;
        }
    }

    for(std::map<std::string, double>::const_iterator it = mean.begin() ; it != mean.end() ; it++) {
        mean[it->first] /= cluster.size();
    }

    return mean;
}

int get_clostest_cluster_index(Gene element, std::vector< std::map<std::string, double> > means) {
    int closest = 0;
    double old_dist = 1000000000;

    for(std::size_t i = 0 ; i < means.size() ; i++) {
        double dist = 0;

        std::vector<double> res;
        for(std::size_t j = 0 ; j < all_codons.size() ; j++) {
            std::string key = all_codons[j];
            res.push_back(std::abs(means[i][key] - element.codon_freqs[key]));
        }

        for(std::size_t j = 0 ; j < res.size() ; j++) {
            dist += res[j];
        }
        //dist /= res.size();

        if(dist < old_dist) {
            closest = i;
            old_dist = dist;
        }
    }

    return closest;
}

int main(int argc, char **argv) {
    std::vector<Gene> genes;

    /*
     * Parse data
     */
	std::ifstream fin("data/simple.fasta");
	fasta ele;

    while(!fin.eof()) {
        Gene cur;
	    getEntry(fin, ele);
        std::vector<std::string> parts = Utils::split(ele.info, ' ');

        cur.name = ele.id;
        cur.codon_freqs = Analyzer::compute_frequencies(ele.sequence, true);
        cur.chromosome = (parts.size() >= 7)?parts[6]:"NA"; // get chromosome

        genes.push_back(cur);
    }
    fin.close();

    std::cout << "Read " << genes.size() << " genes" << std::endl;

    /*
     * Some k-means clustering
     */
    Kluster<Gene> clus(6);

    clus.get_cluster_mean = &get_cluster_mean;
    clus.get_clostest_cluster_index = &get_clostest_cluster_index;

    clus.init(genes);
    std::vector< std::vector<Gene> > res = clus.run();
    //Analyzer::cluster_stats(res);

    /*
     * Save results
     */
    Utils::saveClusters<Gene>("cluster_", res);

	return 0;
}
