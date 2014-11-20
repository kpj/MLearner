#include <vector>
#include <iostream>

#include <cmath>
#include <cstdlib>
#include <ctime>

#include "data.h"
#include "utils.h"
#include "storage.h"


template <class T>
class Kluster {
public:
    Kluster(int k);

    void init(std::vector<T>);
    std::vector< std::vector<T> > run();

    std::map<std::string, double> (*get_cluster_mean)(std::vector<T>);
    int (*get_clostest_cluster_index)(T, std::vector< std::map<std::string, double> >);
private:
    int k;
    std::vector< std::vector<T> > clusters;
    std::vector<T> originals;

    std::vector< std::vector<T> > generate_clusters();
};


/*
 * Function Implementations
 */

template <class T>
Kluster<T>::Kluster(int k) {
    this->k = k;

    std::srand(std::time(NULL));
}

template <class T>
std::vector< std::vector<T> > Kluster<T>::generate_clusters() {
    std::vector< std::vector<T> > tmp;

    for(std::size_t i = 0 ; i < k ; i++) {
        tmp.push_back(std::vector<T>());
    }

    return tmp;
}

template <class T>
void Kluster<T>::init(std::vector<T> elements) {
    originals = elements;

    // create empty clusters
    clusters = generate_clusters();

    // fill 'em
    for(std::size_t i = 0 ; i < elements.size() ; i++) {
        int ind = Utils::rand_int(0, k-1);
        clusters[ind].push_back(elements[i]);
    }
}

template <class T>
std::vector< std::vector<T> > Kluster<T>::run() {
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

        // generate new sets and put elements in there
        std::vector< std::vector<T> > tmp = generate_clusters();
        for(std::size_t i = 0 ; i < originals.size() ; i++) {
            T element = originals[i];
            int ind = get_clostest_cluster_index(element, means);;

            tmp[ind].push_back(element);
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
