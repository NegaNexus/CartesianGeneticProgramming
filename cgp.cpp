#include "rand.h"

#include <iostream>
#include <cmath>
#include <string.h>
#include <vector> 
#include <deque>
#include <algorithm>
#include <numeric> 
#include <iomanip>

using namespace std;

int fitness(vector<int> individual);
void mutate(vector<int> individual);

class CartesianGP {
    private:
        int numInputs;
        int numOutputs;
        int width;
        int length;
        int arity;
        int numSamples;

        int** data;

    public:
        vector<vector<int>> population;

        CartesianGP() {
            initRand();

            cin >> numInputs;
            cin >> numOutputs;
            cin >> width;
            cin >> length;
            cin >> arity;
            cin >> numSamples;

            data = new int*[numSamples];

            for (int i = 0; i < numSamples; ++i) {
                data[i] = new int[numInputs+numOutputs];
                for (int j = 0; j < numInputs+numOutputs; ++j) {
                    cin >> data[i][j];
                }
            }

            for (int i = 0; i < 4; ++i) {
                vector<int> individual; 
                for (int j = 0; j < (width*length); ++j) {
                    individual.push_back(randMod(4));
                    for (int k = 0; k < arity; ++k) {
                        int upper;
                        if (i % width == 0) {
                            upper = numInputs+i;
                        }
                        individual.push_back(randMod(upper));
                    }
                }
                for (int j = 0; j < numOutputs; ++j) {
                    individual.push_back(randMod(numInputs+width*length));
                }

                population.push_back(individual);
            }

            for (const vector<int> &v : population) {
                for (int x : v) {
                    cout << x << " ";
                }
                cout << endl;
            }
        }

        void identify(vector<int> individual) {
            vector<int> unsplit = vector<int>(individual.begin(), individual.end()-numOutputs);
            vector<int> outputGenes = vector<int>(individual.begin()+numOutputs, individual.end());

            int n = arity+1;
            int size = (unsplit.size()-1)/n+1;
            
            vector<int> nodes[size];

            for (int i = 0; i < size; ++i) {
                auto start = next(unsplit.cbegin(), i*n);
                auto end = next(unsplit.cbegin(), i*n + n);

                nodes[i].resize(n);

                copy(start, end, nodes[i].begin());
            }

            for (int i = 0; i < size; ++i) {
                for (int j = 0; j < nodes[i].size(); ++j)
                    cout << nodes[i][j] << " ";
                cout << endl;
            }

            // bool to_evaluate[len];

            // for (int p = 0; p < numOutputs; ++p) {
            //     if (outputGenes[p] >= numInputs) {
            //         to_evaluate[outputGenes[p]-numInputs] = true;
            //     }
            //     else {
            //         to_evaluate[outputGenes[p]-numInputs] = false;
            //     }
            // }

            // for (int p = len; p >= 0; ++p) {
            //     if (to_evaluate[p]) {
            //     }
            // }

        }

};

int main() {
    CartesianGP model;
    model.identify(model.population[0]);

    return 0;
}
