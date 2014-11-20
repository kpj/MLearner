#include <iostream>

#include "FastA.h"


enum FAStages {
    SEARCH_BLOCK,
    READ_ID,
    READ_INFO,
    CHECK_COMMENT,
    READ_COMMENT,
    READ_SEQUENCE,
    SEQUENCE_OVER
} faParserStage = SEARCH_BLOCK;

FAErrors faErrorCode = FA_NO_ERROR;


FAErrors lastFAError() {
    return faErrorCode;
}

std::ostream& writeEntry(std::ostream& os, const fasta& entry) {
    os << ">" << entry.id << " " << entry.info << std::endl;

    for(size_t i = 0 ; i < entry.comments.size() ; i++) {
        os << ";" << entry.comments[i] << std::endl;
    }

    os << entry.sequence << std::endl;

    return os;
}

std::istream& getEntry(std::istream& is, fasta& entry) {
    if(is.eof()) {
        return is;
    }

    // reset state
    faErrorCode = FA_NO_ERROR;
    faParserStage = SEARCH_BLOCK;

    // tmp variables
    std::string buffer;
    char cur = is.get();

    while(is.good()) {
        switch(faParserStage) {
            case SEARCH_BLOCK:
                if(cur != '>' && cur != ';') {
                    faErrorCode = FA_ERROR_NO_BLOCK_FOUND;
                    break;
                }

                faParserStage = READ_ID;
                break;
            case READ_ID:
                if(cur == ' ') {
                    entry.id = buffer;
                    buffer.clear();

                    faParserStage = READ_INFO;
                    break;
                }

                buffer += cur;
                break;
            case READ_INFO:
                if(cur == '\n') {
                    entry.info = buffer;
                    buffer.clear();

                    faParserStage = CHECK_COMMENT;
                    break;
                }

                buffer += cur;
                break;
            case CHECK_COMMENT:
                if(cur == ';') {
                    faParserStage = READ_COMMENT;
                } else {
                    is.unget();
                    faParserStage = READ_SEQUENCE;
                }
                break;
            case READ_COMMENT:
                if(cur == '\n') {
                    entry.comments.push_back(buffer);
                    buffer.clear();

                    faParserStage = CHECK_COMMENT;
                    break;
                }

                buffer += cur;
                break;
            case READ_SEQUENCE:
                if(!(std::isalpha(cur) || cur == '.' || cur == '-' || std::isspace(cur))) {
                    entry.sequence = buffer;
                    buffer.clear();

                    faParserStage = SEQUENCE_OVER;
                } else {
                    if(!std::isspace(cur)) {
                        buffer += cur;
                    }
                }

                break;
            case SEQUENCE_OVER:
                std::cout
                    << "Well, this (still) is awkward..."
                    << std::endl
                ;

                break;
        }

        if(faErrorCode != FA_NO_ERROR) {
            is.setstate(std::ios_base::failbit);
            return is;
        }

        if(faParserStage == SEQUENCE_OVER) {
            if(!is.eof()) {
                is.unget();
            }
            break;
        }

        // proceed to next character
        cur = is.get();
    }

    if(!buffer.empty()) {
        // assume that sequence of last entry wasn't processed. Let's do it!
        entry.sequence = buffer;
    }

    return is;
}
