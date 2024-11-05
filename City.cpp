#include "City.h"
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>


/**
 * @brief Calculates the Euclidean distance between two cities.
 * 
 * Given two City objects representing coordinates on a 2D plane, this function
 * computes the Euclidean distance between them.
 * 
 * @param a The first City object.
 * @param b The second City object.
 * @return The Euclidean distance between city `a` and city `b`.
 */
double Distance_between_two_cities(const City &a, const City &b)
{
    /**/
    return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}


/**
 * @brief Computes the total distance for a given TSP tour.
 * 
 * This function calculates the total distance of a specific tour, defined as 
 * an ordered sequence of city indices. It sums up the distances between each 
 * consecutive pair of cities, returning to the starting city at the end.
 * 
 * @param cities A vector of City objects representing the cities and their coordinates.
 * @param tour A vector of integers representing the sequence of city indices in the tour.
 * @return The total distance of the tour, measured as the sum of Euclidean distances 
 *         between consecutive cities in the sequence.
 * 
 * @details 
 * The function iterates through the sequence of cities given by `tour`, summing the 
 * distances between each city and the next. The final city in `tour` connects back 
 * to the first city, making it a complete cycle.
 */

double Total_Distance(const std::vector<City> &cities, const std::vector<int> &tour)
{
    double tot = 0.0;
    for (int i = 0; i < tour.size(); i++)
    {
        int curr = tour[i];
        int next = tour[(i + 1) % tour.size()];
        tot += Distance_between_two_cities(cities[curr], cities[next]);
    }
    return tot;
}


/**
 * @brief Loads city coordinates from a TSP data file.
 * 
 * Reads city coordinates from a file in a specific format, where each city 
 * is represented by an index and its (x, y) coordinates. This function reads 
 * the data and stores each city's coordinates in the `cities` vector.
 * 
 * @param filename The name of the file containing TSP data in `.tsp` format.
 * @param cities A reference to a vector of City objects to be populated with the 
 *               coordinates of each city from the file.
 * 
 * @details 
 * This function opens the specified file, finds the "NODE_COORD_SECTION" section 
 * where coordinates are listed, and reads each city's index and coordinates 
 * until it encounters "EOF". Each city's coordinates are then stored in the `cities` vector.
 * 
 * Example of expected file format:
 * ```
 * NODE_COORD_SECTION
 * 1 10.0 20.0
 * 2 15.5 25.1
 * ...
 * EOF
 * ```
 * 
 * If the file cannot be opened, the function outputs an error message and exits.
 */
void load_Cities(const std::string &filename, std::vector<City> &cities)
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cerr << "Error opening file!" << std::endl;
        exit(1);
    }
    std::string line;
    while (getline(file, line))
    {
        if (line == "NODE_COORD_SECTION")
            break;
    }
    while (getline(file, line))
    {
        if (line == "EOF")
            break;
        std::stringstream ss(line);
        int index;
        double x, y;
        ss >> index >> x >> y;
        cities.push_back({x, y});
    }
    file.close();
}
