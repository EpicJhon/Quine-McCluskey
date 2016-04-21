#ifndef QUINE_H
#define QUINE_H

#include "includes.h"

/**
 * Minimizing a boolean function using the Quine-McCluskey algorithm
 */
class QuineMcCluskey {
private:

    /**
     * Determines whether or not to display the minimization process
     */
    bool verbose;

    /**
     * It determines whether the minimization process already has been made of the function
     */
    bool minimized = false;
    /**
     * It represents the number of variables of the function
     */
    int nunVars;
    /**
     * It contains all the minterms of the function
     */
    std::set<int> minterm;
    /**
     * It contains the table of adjacencies
     * (index minterm adjacency)
     */
    std::map<int, std::vector<std::pair<std::vector<int>, std::string>>> IMA;

    /**
     * It represents a row in a table of prime implicants
     */
    struct primeRow {
        std::vector<int> primes;
        std::string bin;
        int weight;
    };

    /**
     * Table of prime implicants
     */
    std::vector<primeRow> p_i, p_i_min;
    /**
     * sets of auxiliary minterms (internal)
     */
    std::set<int> min_p_i, normal_p_i;

    /**
     * Creates an adjacency
     * @param num_vars
     * @param a
     * @param b
     * @param old
     * @return 
     */
    std::string createAdjacency(int num_vars, int a, int b, std::string old = "");

    /**
     * Determines whether it is possible to create an adjacency
     * @param a
     * @param b
     * @return 
     */
    bool checkAdjacency(std::string a, std::string b);

    /**
     * Returns the cost of an adjacency
     * @param adjacency
     * @return 
     */
    int getWeight(std::string adjacency);

    /**
     * Prints adjacencies groups
     * @param i_m_a
     */
    void printGroups(std::map<int, std::vector<std::pair < std::vector<int>, std::string>>> i_m_a);

    /**
     * Prints a table of prime implicants
     * @param prime_table
     * @param columns
     */
    void printPrimeTable(std::vector<primeRow> prime_table, std::set<int> columns);

public:

    void addMinterm(int minterm) {
        this->minterm.insert(minterm);
    }

    void setNunVars(int nunVars) {
        this->nunVars = nunVars;
    }

    void setVerbose(bool verbose) {
        this->verbose = verbose;
    }

    /**
     * Prints the resulting minimized function
     */
    void printSOP();
    /**
     * minimizes the function
     */
    void minimize();
};

#endif /* QUINE_H */

