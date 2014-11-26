#ifndef FASTA_H_HH
#define FASTA_H_HH

#include <string>
#include <vector>


struct fasta {
    std::string id;
    std::string info;
    std::vector<std::string> comments;
    std::string sequence;
};

enum FAErrors {
    FA_NO_ERROR,
    FA_ERROR_NO_BLOCK_FOUND
};

FAErrors lastFAError();
std::istream& getEntry(std::istream&, fasta&);
std::ostream& writeEntry(std::ostream&, const fasta&);

#endif
