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

vector<vector<int>> crossover(vector<int> parent1, vector<int> parent2) {
    vector<vector<int>> children;
    int crossoverPoint = mt_generator() % parent1.size();
    vector<int> child1(parent1.begin(), parent1.begin() + crossoverPoint);
    child1.insert(child1.end(), parent2.begin() + crossoverPoint, parent2.end());
    vector<int> child2(parent2.begin(), parent2.begin() + crossoverPoint);
    child2.insert(child2.end(), parent1.begin() + crossoverPoint, parent1.end());
    children.push_back(child1);
    children.push_back(child2);
    return children;
}

vector<int> mutate(vector<int> chromosome, double mutationProb) {
    for (int &gene : chromosome) {
        double rnd = static_cast<double>(mt_generator()) / mt_generator.max();
        if (rnd < mutationProb) {
            gene = gene xor 1;
        }
    }
    return chromosome;
}

vector<int> rouletteSelection(vector<vector<int>> population) {
    vector<double> probabilities(population.size());
    double sumFitness = 0;
    for (const auto &chromosome : population) {
        sumFitness += fitness(chromosome);
    }
    for (int i = 0; i < population.size(); i++) {
        probabilities[i] = fitness(population[i]) / sumFitness;
    }
    for (int i = 1; i < probabilities.size(); i++) {
        probabilities[i] += probabilities[i - 1];
    }

    double rnd = static_cast<double>(mt_generator()) / mt_generator.max();
    int selectedIndex = 0;
    while (rnd > probabilities[selectedIndex]) {
        selectedIndex++;
    }
    return population[selectedIndex];
}

int main() {
    int populationSize = 10;
    double crossoverProb = 0.8;
    double mutationProb = 0.01;
    int numGenerations = 2;

    vector<vector<int>> population = generateGenoType(populationSize);

    for (int generation = 0; generation < numGenerations; generation++) {
        vector<vector<int>> newPopulation;

        while (newPopulation.size() < population.size()) {
            vector<int> parent1 = rouletteSelection(population);
            vector<int> parent2 = rouletteSelection(population);
            double rnd = static_cast<double>(mt_generator()) / mt_generator.max();
            if (rnd < crossoverProb) {
                auto children = crossover(parent1, parent2);
                newPopulation.push_back(mutate(children[0], mutationProb));
                newPopulation.push_back(mutate(children[1], mutationProb));
            } else {
                newPopulation.push_back(parent1);
                newPopulation.push_back(parent2);
            }
        }
        population = move(newPopulation);

        for (auto &element: population) {
            auto decoded = decodePhenotype(element);
            cout << "X: " << decoded.first << "\nY: " << decoded.second << "\nMaksymalizacja: " << fitness(element) <<"\n"<< endl;
        }
    }
    return 0;
}