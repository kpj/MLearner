#include <iostream>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "data.h"
#include "utils.h"

#include "cluster.h"


Kluster::Kluster(int k) {
    this->k = k;

    std::srand(std::time(NULL));
}

std::vector< std::vector<Gene> > Kluster::generate_clusters() {
    std::vector< std::vector<Gene> > tmp;

    for(std::size_t i = 0 ; i < k ; i++) {
        tmp.push_back(std::vector<Gene>());
    }

    return tmp;
}

void Kluster::init(std::vector<Gene> genes) {
    originals = genes;

    // create empty clusters
    clusters = generate_clusters();

    // fill 'em
    for(std::size_t i = 0 ; i < genes.size() ; i++) {
        int ind = Utils::rand_int(0, k-1);
        clusters[ind].push_back(genes[i]);
    }
}

std::vector< std::vector<Gene> > Kluster::run() {
    std::vector<int> old_sizes;
    for(std::size_t i = 0 ; i < k ; i++) {
        old_sizes.push_back(-1);
    }

    int runs = 0;
    while(true) {
        // info
        for(std::size_t i = 0 ; i < k ; i++) {
            std::cout << "Elements in cluster #" << i << ": " << clusters[i].size() << std::endl;
        }
        std::cout << std::endl;

        // compute current cluster means
        std::vector< std::map<std::string, double> > means;
        for(std::size_t i = 0 ; i < k ; i++) {
            means.push_back(get_cluster_mean(clusters[i]));
        }

        // generate new sets and put genes in there
        std::vector< std::vector<Gene> > tmp = generate_clusters();
        for(std::size_t i = 0 ; i < originals.size() ; i++) {
            Gene gene = originals[i];
            int ind = get_clostest_cluster_index(gene, means);;

            tmp[ind].push_back(gene);
        }

        // check if we should stop
        std::vector<int> new_sizes; // tmp workaround
        for(std::size_t i = 0 ; i < k ; i++) {
            new_sizes.push_back(clusters[i].size());
        }

        if(old_sizes == new_sizes) {
           break;
        } else {
            clusters = tmp;
            old_sizes = new_sizes;
            
            // remove empty entries and update k
            // ...
        }

        runs++;
    }

    return clusters;
}



int Kluster::get_clostest_cluster_index(Gene gene, std::vector< std::map<std::string, double> > means) {
    int closest = 0;
    double old_dist = 1000000000;

    for(std::size_t i = 0 ; i < k ; i++) {
        double dist = 0;

        std::vector<double> res;
        for(std::size_t j = 0 ; j < all_codons.size() ; j++) {
            std::string key = all_codons[j];
            res.push_back(std::abs(means[i][key] - gene.codon_freqs[key]));
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

std::map<std::string, double> Kluster::get_cluster_mean(std::vector<Gene> cluster) {
    /*
     * Return mean of cluster
     */
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

