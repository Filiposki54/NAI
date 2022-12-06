#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std::chrono;

//Used for generating random numbers
std::random_device rd;
std::mt19937 mt_generator(rd());

auto coords_generator(double r1, double r2) {
    std::uniform_real_distribution<> coords(r1, r2);
    return std::pair<double, double>(coords(mt_generator), coords(mt_generator));
}

auto brute_force = [](auto f, auto domain, int iterations, double r1, double r2) {
    auto current_p = domain(r1, r2);
    auto best_point = current_p;

    for (int i = 0; i < iterations; ++i) {
        if (f(current_p) < f(best_point)) {
            best_point = current_p;
        }
        current_p = domain(r1, r2);
    }

    return best_point;
};

int main() {

    auto Himmelblaus_f = [](std::pair<double, double> pair) {
        return  pow((pow(pair.first,2) + pair.second - 11),2) +
                pow((pair.first + pow(pair.second,2) -7),2);
    };

    auto Booth_f = [](std::pair<double, double> pair) {
        return  pow(pair.first + (2*pair.second)- 7,2) +
                pow((2*pair.first) + pair.second -5,2);
    };

    auto ThreeHumpCamel_f = [](std::pair<double, double> pair) {
        return  (2*pow(pair.first,2)) -
                (1.05*pow(pair.first,4)) +
                (pow(pair.first,6)/6) +
                (pair.first * pair.second) + pow(pair.second,2);
    };
    std::cout << "Results for Himmelblaus:\n";
    for(int i = 0; i < 20; i++){
        auto start = high_resolution_clock::now();
        auto Himmelblaus = brute_force(Himmelblaus_f, coords_generator, 1000000, -5, 5);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << " x = " << Himmelblaus.first
                  << " y = " << Himmelblaus.second
                  << " result: " << Himmelblaus_f(Himmelblaus)
                  << std::endl;
        std::cout << " duration: " << duration.count() << std::endl;
    }
    std::cout << "Results for Both:\n";
    for(int i = 0; i < 20; i++){
        auto start = high_resolution_clock::now();
        auto Booth = brute_force(Booth_f, coords_generator, 1000000, -10, 10);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << " x = " << Booth.first
                  << " y = " << Booth.second
                  << " result: " << Booth_f(Booth)
                  << std::endl;
        std::cout << "| duration: " << duration.count() << std::endl;
    }
    std::cout << "Results for ThreeHumpCamel:\n";
    for(int i = 0; i < 20; i++){
        auto start = high_resolution_clock::now();
        auto ThreeHumpCamel = brute_force(ThreeHumpCamel_f, coords_generator, 1000000, -5, 5);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);
        std::cout << " x = " << ThreeHumpCamel.first
                  << " y = " << ThreeHumpCamel.second
                  << " result: " << ThreeHumpCamel_f(ThreeHumpCamel)
                  << std::endl;
        std::cout << "| duration: " << duration.count() << std::endl;
    }
    return 0;
}
