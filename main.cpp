#include <fstream>
#include <iostream>

#include "FastA.h"
#include "storage.h"
#include "utils.h"
#include "analyzer.h"
#include "cluster.h"


int main(int argc, char **argv) {
    std::vector<Gene> genes;

    /*
     * Parse data
     */
	std::ifstream fin("data/dicty_primary_cds.fasta");
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
    Kluster clus(6);
    clus.init(genes);
    std::vector< std::vector<Gene> > res = clus.run();
    Analyzer::cluster_stats(res);

	return 0;
}
