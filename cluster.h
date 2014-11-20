#include <vector>

#include "storage.h"


class Kluster {
public:
    Kluster(int k);

    void init(std::vector<Gene> genes);
    std::vector< std::vector<Gene> > run();
private:
    int k;
    std::vector< std::vector<Gene> > clusters;
    std::vector<Gene> originals;

    std::vector< std::vector<Gene> > generate_clusters();

    std::map<std::string, double> get_cluster_mean(std::vector<Gene> cluster);
    int get_clostest_cluster_index(Gene gene, std::vector< std::map<std::string, double> > means);
};
