#include <iostream>
#include <utility>
#include <vector>
#include <random>

using namespace std;

auto booth = [](pair<double, double> pair) {

    return pow(pair.first + (2 * pair.second) - 7,2)+
           pow((2 * pair.first) + pair.second -5,2);
};

random_device rd;
mt19937 mt_generator(rd());

vector<vector<int>> generateGenoType(int size) {
    vector<vector<int>> genotype;
    vector<int> chromosomes;

    for (int i = 0; i < size; ++i) {
        chromosomes.clear();

        for (int j = 0; j < size ; ++j) {
            uniform_int_distribution<int> uni(0, 1);
            chromosomes.push_back(uni(mt_generator));
        }

        genotype.push_back(chromosomes);
    }

    return genotype;
}

pair<double, double> decodePhenotype(vector<int> chromosomes) {
    double x, y = 0.0;

    for (int i = 0; i < chromosomes.size() / 2; i++) {
        x = x * 2 + chromosomes[i];
    }

    for (int i = (int) chromosomes.size() / 2; i < chromosomes.size(); i++) {
        y = y * 2 + chromosomes[i];
    }

    x = x / pow(2.0, (chromosomes.size() / 2 - 4)) - 8;
    y = y / pow(2.0, (chromosomes.size() / 2 - 4)) - 8;

    return {x, y};
}

double fitness(vector<int> chromosomes) {
    return 1.0 / (1.0 + abs(booth(decodePhenotype(move(chromosomes)))));
}

int main() {
    for (auto &element: generateGenoType(100 + (20490 % 10) * 2)) {
        auto decoded = decodePhenotype(element);
        cout << "X: " << decoded.first << "\nY: " << decoded.second << "\nMaksymalizacja: " << fitness(element) <<"\n"<< endl;
    }

    return 0;
}