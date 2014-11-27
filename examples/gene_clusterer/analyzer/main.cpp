#include <iostream>
#include <sstream>
#include <vector>

#include "../../../src/cluster.h"
#include "../../../src/utils.h"

#include "../storage.h"
#include "../analyzer.h"


int main(int argc, char **argv) {
    std::vector<Gene> genes;

    /*
    * Parse cmd-line args
    */
    if(argc != 2) {
      std::cout << "Usage: " << argv[0] << " <cluster file>" << std::endl;
      return 1;
    }
    std::string fname = argv[1];

    /*
     * Read data
     */
    genes = Utils::readClusters<Gene>(fname);
    std::cout << "Read " << genes.size() << " genes" << std::endl;

    std::vector<Gene> tmp;
    for(auto iter : genes) {
        iter.codon_freqs = Analyzer::compute_frequencies(iter.sequence, true);
        tmp.push_back(iter);
    }
    genes = tmp;

    // make some nice format
    std::vector< std::vector<Gene> > clusters = Utils::parseClusters(genes);

    /*
    * Further analyses
    */
    //Analyzer::cluster_stats(clusters);

    std::stringstream ss;
    ss << "codons_" << fname;
    Analyzer::codonFreqs(ss.str(), clusters);
}
