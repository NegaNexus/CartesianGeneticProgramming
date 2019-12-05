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

            // Print population
            // for (const vector<int> &v : population) {
            //     for (int x : v) {
            //         cout << x << " ";
            //     }
            //     cout << endl;
            // }
        }

        vector<bool> identify(vector<int> individual) {
            vector<int> unsplit = vector<int>(individual.begin(), individual.end()-numOutputs);
            vector<int> outputGenes = vector<int>(individual.begin()+(arity+1)*length*width, individual.end());
            
            int n = arity+1;
            int size = (unsplit.size()-1)/n+1;
            
            vector<int> nodes[size];

            for (int i = 0; i < size; ++i) {
                auto start = next(unsplit.cbegin(), i*n);
                auto end = next(unsplit.cbegin(), i*n + n);

                nodes[i].resize(n);

                copy(start, end, nodes[i].begin());
            }

            // Print split
            // for (int i = 0; i < size; ++i) {
            //     for (int j = 0; j < nodes[i].size(); ++j)
            //         cout << nodes[i][j] << " ";
            //     cout << endl;
            // }

            vector<bool> toEvaluate;
            for (int i = 0; i < size; ++i) {
                toEvaluate.push_back(false);
            }

            for (int p = 0; p < numOutputs; ++p) {
                if (outputGenes[p] >= numInputs) {
                    toEvaluate[outputGenes[p]-numInputs] = true;
                }
            }

            for (int p = size; p >= 0; --p) {
                if (toEvaluate[p]) {
                    if (nodes[p][1] >= numInputs) {
                        toEvaluate[nodes[p][1]-numInputs] = true;
                    }
                    if (nodes[p][2] >= numInputs) { 
                        toEvaluate[nodes[p][2]-numInputs] = true;
                    }
                }
            }

            return toEvaluate;
        }
};

int main() {
    CartesianGP model;
    auto toEvaluate = model.identify(model.population[1]);

    for (auto x : toEvaluate) {
        cout << x << " ";
    }
    
    return 0;
}
