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

void initPopulation();
vector<int> evaluate(vector<int> individual);
int fitness(vector<int> individual);
void mutate(vector<int> individual);

int main() {
    int numInputs;
    int numOutputs;
    int width;
    int length;
    int arity;
    
    int numSamples;


    cin >> numInputs;
    cin >> numOutputs;
    cin >> width;
    cin >> length;
    cin >> arity;

    cin >> numSamples;

    int inputs[numSamples][numInputs];
    int outputs[numSamples][numOutputs];

    for (int i = 0; i < numSamples; ++i) {
        for (int j = 0; j < numInputs; ++j) {
            cin >> inputs[i][j]; 
        }
        for (int j = 0; j < numOutputs; ++j) {
            cin >> outputs[i][j];
        }
    }

    return 0;
}
