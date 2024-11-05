#ifndef ANNEALING_H
#define ANNEALING_H
#include "City.h"
#include <vector>
using namespace std;
void SimulatedAnnealing(vector<City> &city, vector<int> &best, double init_temp, double cool_rate, int max_iter);
#endif