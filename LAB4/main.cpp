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

vector<int> binaryToGray(vector<int> binary) {
    vector<int> gray;
    gray.push_back(binary[0]);
    for (int i = 1; i < binary.size(); i++) {
        gray.push_back(binary[i - 1] xor binary[i]);
    }
    return gray;
}

vector<vector<int>> generateGenoType(int size) {
    vector<vector<int>> genotype;
    vector<int> chromosomes;

    for (int i = 0; i < size; ++i) {
        chromosomes.clear();

        for (int j = 0; j < size ; ++j) {
            uniform_int_distribution<int> uni(0, 1);
            chromosomes.push_back(uni(mt_generator));
        }

        genotype.push_back(binaryToGray(chromosomes));
    }

    return genotype;
}

pair<double, double> decodePhenotype(vector<int> gray) {
    double x, y = 0.0;
    vector<int> binary;
    binary.push_back(gray[0]);
    for (int i = 1; i < gray.size(); i++) {
        binary.push_back(gray[i] xor binary[i-1]);
    }
    for (int i = 0; i < binary.size() / 2; i++) {
        x = x * 2 + binary[i];
    }

    for (int i = (int) binary.size() / 2; i < binary.size(); i++) {
        y = y * 2 + binary[i];
    }

    x = x / pow(2.0, (binary.size() / 2 - 4)) - 8;
    y = y / pow(2.0, (binary.size() / 2 - 4)) - 8;

    return {x, y};
}

double fitness(vector<int> gray) {
    return 1.0 / (1.0 + abs(booth(decodePhenotype(move(gray)))));
}

int main() {
    for (auto &element: generateGenoType(100 + (20490 % 10) * 2)) {
        auto decoded = decodePhenotype(element);
        cout << "X: " << decoded.first << "\nY: " << decoded.second << "\nMaksymalizacja: " << fitness(element) <<"\n"<< endl;
    }

    return 0;
}