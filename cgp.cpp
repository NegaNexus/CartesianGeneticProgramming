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

vector<int> evaluate(vector<int> individual);
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

    public:
        vector<vector<int>> population;
        int** inputs;
        int** outputs;

        CartesianGP() {
            initRand();

            cin >> numInputs;
            cin >> numOutputs;
            cin >> width;
            cin >> length;
            cin >> arity;

            cin >> numSamples;

            inputs = new int*[numSamples];
            int data[numSamples][numInputs+numOutputs];

            for (int i = 0; i < numSamples; ++i) {
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
};

int main() {
    CartesianGP();

    return 0;
}
