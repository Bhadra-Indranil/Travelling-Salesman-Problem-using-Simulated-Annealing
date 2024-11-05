#include "Annealing.h"
#include "City.h"
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iostream>
#include <random>

using namespace std;


/**
 * @brief Solves the Traveling Salesman Problem (TSP) using the Simulated Annealing algorithm.
 * 
 * This function takes a set of cities and applies the simulated annealing metaheuristic 
 * to approximate an optimal tour with minimal total travel cost. The simulated annealing 
 * algorithm probabilistically accepts new solutions based on a cooling schedule, aiming 
 * to avoid local optima and approach a global minimum.
 * 
 * @param city A reference to a vector of City objects representing the cities to be visited, 
 *             where each City contains its coordinates (x, y).
 * @param best A reference to a vector of integers that will store the optimal sequence 
 *             of cities (in terms of their indices) after completing the algorithm.
 * @param init_temp Initial temperature for the simulated annealing algorithm. Higher temperatures 
 *                  allow for greater flexibility in accepting costlier moves at the beginning.
 * @param cool_rate Cooling rate used to decrease the temperature progressively in each iteration. 
 *                  A rate close to 1.0 (e.g., 0.999) provides a slower cooling, aiding in exploration.
 * @param max_iter Maximum number of iterations to run the simulated annealing algorithm.
 * 
 * @details 
 * Steps of the Algorithm:
 * 1. Initializes a random tour (current solution) of all cities.
 * 2. Calculates the total distance (cost) for the initial random tour and stores it as the current best.
 * 3. Iterates up to `max_iter`, each time generating a new neighboring solution by swapping two city positions:
 *    - A new tour is created by swapping the positions of two randomly selected cities.
 *    - If the new tour has a lower cost, it is accepted as the current best.
 *    - If the new tour is worse, it may still be accepted with a probability that decreases with temperature.
 * 4. Updates the temperature after each iteration according to the cooling rate.
 * 
 * Final Output:
 * - Outputs the achieved minimum cost and the sequence of cities in the optimal tour.
 * - Prints the "Final cost" and "Solution [sequence of cities]" as the list of city indices in visiting order.
 * 
 * Example Output:
 * ```
 * Final cost: [calculated_cost]
 * Solution [seq of cities]: 0 4 1 3 2 ...
 * ```
 */
void SimulatedAnnealing(vector<City> &city, vector<int> &best, double init_temp, double cool_rate, int max_iter)
{
    

    int no_of_cities = city.size();
    vector<int> curr(no_of_cities);

    for (int i = 0; i < no_of_cities; ++i)
    {
        curr[i] = i;
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(curr.begin(), curr.end(), gen);

    best = curr;

    double best_cost = Total_Distance(city, best);
    double temp = init_temp;

    for (int i = 0; i < max_iter; ++i)
    {
        int city_1 = rand() % no_of_cities;
        int city_2 = (city_1 + 1 + rand() % (no_of_cities - 1)) % no_of_cities;

        swap(curr[city_1], curr[city_2]);
        double curr_cost = Total_Distance(city, curr);
        double p = exp((best_cost - curr_cost) / temp);

        if (curr_cost < best_cost || p > (double)rand() / RAND_MAX + 1.0)
        {
            best = curr;
            best_cost = curr_cost;
        }
        else
        {
            swap(curr[city_1], curr[city_2]);
        }

        temp *= cool_rate;
    }

    cout << "Final cost: " << best_cost << endl;
    cout << "Solution [seq of cities]: ";
    for (int c : best)
    {
        cout << c << " ";
    }
    cout << endl;
}

