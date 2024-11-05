#ifndef CITY_H
#define CITY_H

#include <vector>
#include <string>

struct City {
    double x, y;
};

double Distance_between_two_cities(const City &a, const City &b);
double Total_Distance(const std::vector<City> &cities, const std::vector<int> &tour);
void load_Cities(const std::string &filename, std::vector<City> &cities);

#endif
