/* 
 * File:   quine.cpp
 * Author: h4x0r
 * 
 * Created on 20 de abril de 2016, 06:28 PM
 */

#include "quine.h"

using namespace std;

string QuineMcCluskey::createAdjacency(int num_vars, int a, int b, string old) {
    string s_a = Utility::padTo(Utility::binary(a), num_vars);
    string diference = Utility::padTo(Utility::binary(abs(a - b)), num_vars);

    if (old.empty())
        return s_a.replace(diference.find('1'), 1, "-");
    else
        return old.replace(diference.find('1'), 1, "-");
}

bool QuineMcCluskey::checkAdjacency(string a, string b) {

    std::replace(a.begin(), a.end(), '0', '.');
    std::replace(a.begin(), a.end(), '1', '.');

    std::replace(b.begin(), b.end(), '0', '.');
    std::replace(b.begin(), b.end(), '1', '.');

    return a == b;
}

int QuineMcCluskey::getWeight(string adjacency) {
    adjacency.erase(std::remove(adjacency.begin(), adjacency.end(), '-'), adjacency.end());
    return adjacency.length();
}

void QuineMcCluskey::printGroups(map<int, vector<pair < vector<int>, string>>> i_m_a) {
    for (auto &kv : i_m_a) {
        cout << "index: " << kv.first << endl;
        // pairs
        for (auto &kv_pair : kv.second) {

            cout << "\tMin: " << endl << "\t\t";

            for (auto minterm : kv_pair.first) {
                cout << minterm << "-";
            }

            cout << "; " << kv_pair.second << endl;
        }
    }
}

void QuineMcCluskey::printPrimeTable(vector<primeRow> prime_table, set<int> columns) {

    cout << "\t";
    for (int min : columns)
        cout << min << "\t";
    cout << endl;

    int index, prev_index;

    for (auto &row : prime_table) {
        cout << row.bin << "\t";
        index = 0;
        prev_index = 0;
        for (int min : row.primes) {
            prev_index = index;

            if (columns.find(min) == columns.end())
                continue;

            index = std::distance(columns.begin(), columns.find(min));
            for (int i = 0; i < index - prev_index; i++)
                cout << "\t";
            cout << "X";
        }

        cout << endl;
    }

}

void QuineMcCluskey::printSOP() {
    if (!minimized) {
        cout << "No hay una funcion a mostrar aun";
        return;
    }

    /*
     * print essential formula 
     */
    bool printed;
    int j = 0;

    for (auto &kv : p_i) {
        printed = false;
        cout << (j > 0 ? " || " : "");
        for (int i = 0; i < kv.bin.size(); i++) {

            if (kv.bin[i] == '-')
                continue;

            cout << (printed ? " && " : "");

            if (kv.bin[i] == '0')
                cout << '!';

            cout << (char) ('a' + i);

            printed = true;

        }
        j++;
    }

    // if all minterm is covered by essential primes
    if (min_p_i.size() == 0) {
        return;
    }

    /*
     * print non-essential formula 
     */
    for (auto &kv : p_i_min) {
        printed = false;
        cout << " || ";
        for (int i = 0; i < kv.bin.size(); i++) {

            if (kv.bin[i] == '-')
                continue;

            cout << (printed ? " && " : "");

            if (kv.bin[i] == '0')
                cout << '!';

            cout << (char) ('a' + i);

            printed = true;

        }
    }

}

void QuineMcCluskey::minimize() {

    minimized = true;

    int index;
    string bin_number;
    vector<int>::iterator it;

    // iteration 0
    for (int number : minterm) {
        bin_number = Utility::padTo(Utility::binary(number), nunVars);
        index = Utility::countSubstring(bin_number, "1");

        IMA[index].push_back({
            {number}, bin_number
        });
    }

    int a, b, iteration = 1;
    string adjacency, s_a, s_b;
    vector<int> adjacency_group;
    bool exists;
    // new table
    map<int, vector<pair < vector<int>, string>>> newIMA;
    // lock groups
    vector<string> lock;

    // iterations
    while (true) {

        // iterate index
        for (int i = 0; i < IMA.size() - 1; i++) {

            // iterate pairs of current index
            for (int j = 0; j < IMA[i].size(); j++) {

                // iterate pairs of upper index
                for (int k = 0; k < IMA[i + 1].size(); k++) {

                    a = IMA[i][j].first.front();
                    b = IMA[i + 1][k].first.front();
                    s_a = IMA[i][j].second;
                    s_b = IMA[i + 1][k].second;

                    if (b > a and Utility::isPowerOfTwo(b - a) and checkAdjacency(s_a, s_b)) {

                        // lock minterm
                        if (!Utility::exists(lock, s_a))
                            lock.push_back(s_a);
                        if (!Utility::exists(lock, s_b))
                            lock.push_back(s_b);

                        // create adjacency
                        adjacency = createAdjacency(nunVars, a, b, s_a);

                        // scheck that does not exist before
                        exists = false;
                        for (auto &kv : newIMA[i]) {
                            exists = (adjacency == kv.second);
                            if (exists)
                                break;
                        }

                        // add only if no there
                        if (!exists) {
                            adjacency_group.clear();

                            for (auto number : IMA[i][j].first)
                                adjacency_group.push_back(number);

                            for (auto number : IMA[i + 1][k].first)
                                adjacency_group.push_back(number);

                            newIMA[i].push_back({adjacency_group, adjacency});
                        }

                    }

                }

            }
        }

        /*
         * end of iterations
         */
        if (lock.size() == 0) {
            // clear stuff
            newIMA.clear();
            if (verbose)
                cout << "===== End of iterations! =====" << endl;
            break;
        }

        /*
         * remove all locked minterm, and add unlock minterm to next iteration
         */
        for (auto str : lock)
            for (auto &kv : IMA)
                for (auto it = kv.second.cbegin(); it != kv.second.cend();) {
                    if (str == it->second) {
                        kv.second.erase(it++);
                        if (kv.second.size() == 0)
                            IMA.erase(kv.first);
                        break;
                    } else {
                        ++it;
                    }
                }

        for (auto kv : IMA)
            for (auto kv_pair : kv.second)
                newIMA[kv.first].push_back({kv_pair.first, kv_pair.second});


        /*
         * Prepare all to next iteration
         */
        IMA.clear();
        IMA = newIMA;

        newIMA.clear();
        lock.clear();

        // show current iteration
        if (verbose) {
            cout << "===== Iteration: " << iteration << " =====" << endl;
            printGroups(IMA);
        }

        iteration++;
    }

    for (auto &kv : IMA)
        for (auto &kv_pair : kv.second)
            p_i.push_back({kv_pair.first, kv_pair.second, getWeight(kv_pair.second)});

    /*
     * Get reduced prime implicants table
     */
    min_p_i = minterm;
    normal_p_i = minterm;
    bool prime;
    for (auto &kv : p_i) {

        for (auto &n : kv.primes) {
            prime = true;

            for (auto &kv2 : p_i) {

                // if same then ignore
                if (kv.bin == kv2.bin)
                    continue;

                // non-essential
                if (Utility::exists(kv2.primes, n)) {
                    prime = false;
                    break;
                }

            }

            if (prime)
                break;
        }

        if (!prime) {
            p_i_min.push_back({kv});
        } else {
            for (auto &prime : kv.primes)
                min_p_i.erase(prime);
        }
    }


    if (verbose) {
        cout << "===== Tabla de implicantes =====" << endl;
        printPrimeTable(p_i, minterm);
    }

    // remove all non-essential primes in p_i
    for (auto &kv : p_i_min)
        for (auto it = p_i.cbegin(); it != p_i.cend();) {
            if (kv.bin == it->bin) {
                p_i.erase(it++);
                break;
            } else {
                ++it;
            }
        }

    // if all minterm is covered by essential primes
    if (min_p_i.size() == 0)
        return;

    if (verbose) {
        cout << "===== Tabla de implicantes reducida =====" << endl;
        printPrimeTable(p_i_min, min_p_i);
    }

    // remove all covered minterm from primes table
    for (int prime : min_p_i)
        normal_p_i.erase(prime);

    // remove all covered minterm from recuded primes table
    for (auto &row : p_i_min)
        for (int prime : normal_p_i)
            Utility::removeAll(row.primes, prime);

    // remove all non-essential primes in p_i
    bool to_remove;
    for (auto it = p_i_min.begin(); it != p_i_min.end();) {

        to_remove = false;
        for (auto row2 : p_i_min) {
            // ignore me
            if (it->bin == row2.bin) {
                continue;
            }

            // equivalence
            if (it->primes == row2.primes and it->weight >= row2.weight) {
                to_remove = true;
                break;
            }

            // dominance
            if (row2.primes.size() > it->primes.size()) {
                if (Utility::contains(row2.primes, it->primes)) {
                    to_remove = true;
                    break;
                }
            }
        }

        if (to_remove) {
            it = p_i_min.erase(it);
        } else {
            ++it;
        }
    }

    if (verbose) {
        cout << "===== Tabla de implicantes reducida FINAL =====" << endl;
        printPrimeTable(p_i_min, min_p_i);
    }
}