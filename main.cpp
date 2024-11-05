#include<iostream>
#include<vector>
#include<ctime>
#include "City.h"
#include "Annealing.h"

using namespace std;

int main(){
    srand(time(0));
    vector<City> c;
    // You can check this using other tsp file 
    // for dataset you check https://www.math.uwaterloo.ca/tsp/vlsi/index.html
    string file = "Dataset/xqg237.tsp";
    load_Cities(file, c);
    vector<int> best;
    double init_temp = 10000 , cool_rate = 0.999;
    int max_iter = 10000;

    SimulatedAnnealing(c,best,init_temp,cool_rate,max_iter);
}