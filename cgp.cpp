#include "rand.h"

#include <iostream>
#include <cmath>
#include <string.h>
#include <vector> 
#include <map>
#include <deque>
#include <algorithm>
#include <numeric> 
#include <iomanip>

using namespace std;


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
                            upper = numInputs+j;
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

        int fitness(vector<int> individual) {
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

            map<int, bool> outputs; 

            auto toEvaluate = identify(individual);
            
            int fit = 0;

            for (int i = 0; i < numSamples; ++i) {
                for (int p = 0; p < numInputs; ++p) { 
                    outputs[p] = data[i][p];
                }

                for (int p = 0; p < size; ++p) {
                    if (toEvaluate[p]) {
                        bool in1 = outputs[nodes[p][1]];
                        bool in2 = outputs[nodes[p][2]];
                        if (nodes[p][0] == 0) {
                            outputs[p+numInputs] = (in1 && in2);
                        }
                        else if (nodes[p][0] == 1) {
                            outputs[p+numInputs] = (in1 || in2);
                        }
                        else if (nodes[p][0] == 2) {
                            outputs[p+numInputs] = (in1 != in2);
                        }
                        else if (nodes[p][0] == 3) {
                            outputs[p+numInputs] = (!in1);
                        }
                    }
                }

                bool output[numOutputs];

                int k = 0;
                for (auto gene : outputGenes) {
                    output[k] = outputs[gene];
                    ++k;
                }

                k = 0;
                bool trueOutput[numOutputs]; 
                for (int j = numInputs; j < numInputs+numOutputs; ++j) {
                    trueOutput[k] = data[i][j];
                    ++k;
                }

                for (int j = 0; j < numOutputs; ++j) {
                    cout << trueOutput[j] << ' '; 
                }
                cout << endl;
                cout << endl;

                for (int j = 0; j < numOutputs; ++j) {
                    cout << output[j] << ' '; 
                }
                cout << endl;
                cout << "---" << endl;

                bool flag = true;
                for (int  j = 0; j < numOutputs; ++j) {
                    if (trueOutput[j] != output[j]) {
                        flag = false;
                    }
                }

                if (flag) {
                    fit++;
                }
            }

            return fit;
        }

        void mutate(vector<int> individual) {
            int upper = numInputs;

            vector<int> range;
            for (unsigned int i = 0; i < individual.size(); ++i) {
                range.push_back(i);
            }
            
            int num = 0.2*individual.size();
            int choices[num];
            for (int i = 0; i < num; ++i) {
                int index = randMod(range.size());
                choices[i] = individual[range[index]];
                range.erase(range.begin()+index);
            }

            for (auto choice : choices) {
                if (choice <= (width*length*(arity+1))) {
                    if (choice % width == 0) {
                        upper = numInputs+(choice/(arity+1));
                    }

                    if (choice % (arity+1) == 0) {
                        individual[choice] = randMod(4); 
                    }
                    else {
                        individual[choice] = randMod(upper);
                    }
                }
                else {
                    individual[choice] = randMod(numInputs+width*length);
                }
            }

        }
};

int main() {
    CartesianGP model;
    auto toEvaluate = model.identify(model.population[0]);
    // cout << model.fitness(model.population[0]) << endl;

    for (auto x : model.population[0]) {
        cout << x << " ";
    }
    cout << endl;

    // auto mutated = model.population[0];
    // model.mutate(mutated);

    // for (auto x : mutated) {
    //     cout << x << " ";
    // }

    for (auto x : toEvaluate) {
        cout << x << " ";
    }
    
    return 0;
}
