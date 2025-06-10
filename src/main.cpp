#include <bits/stdc++.h>
#include "./Engine/huerstics.cpp"
#include "./Engine/generator.cpp"

using namespace std;

const int BOARD_DIMENSION = 5;
const int MAX_GENERATION = 10000;
const int POPULATION_SIZE = 10;
const int NUMBER_QUEENS = 5;

// returns the ratio by which count attacks was decreased in the 2 populations
float calculate_success(int** oldPopulation, int** newPopulation, int populationSize, int dimensionSize){
    int countAttacksOld = 0;
    int countAttacksNew = 0;
    for(int i = 0 ; i < populationSize ; ++i){
        countAttacksOld += calculate_count_attacks(oldPopulation[i], dimensionSize);
        countAttacksNew += calculate_count_attacks(newPopulation[i], dimensionSize);
    }
    return 1 - float(countAttacksOld) / float(countAttacksNew);
}

int run(){
    cout << "---------------------------------------\n";
    cout << "intializing dimensions with " << BOARD_DIMENSION 
    << " and population size " << POPULATION_SIZE << ", queen to be placed " << NUMBER_QUEENS << "\npreping the population\n";
    cout << "---------------------------------------\n";


    int** population = Generator::generate_random_population(POPULATION_SIZE, BOARD_DIMENSION);
    int n = MAX_GENERATION;

    while(n--){
        cout << "---------------------------------------\n";
        cout << "Current generation: " << MAX_GENERATION - n << "\n";

        float* fitness = calculate_fitness_for_population(population, POPULATION_SIZE, BOARD_DIMENSION);
        int** newPopulation = roulette_wheel_selection(population, fitness, POPULATION_SIZE, BOARD_DIMENSION);
        int** crossOver = random_cross_over(newPopulation, POPULATION_SIZE, BOARD_DIMENSION);
        int** mutatedPopulation = mutation(crossOver, POPULATION_SIZE, BOARD_DIMENSION, 0.1);

        float successRate = calculate_success(population, mutatedPopulation, POPULATION_SIZE, BOARD_DIMENSION);
        cout << "Success rate in new poopulation (" << successRate * 100 << "%)\n";

        population = mutatedPopulation;
        cout << "---------------------------------------\n";
    }

    for(int i = 0 ; i < POPULATION_SIZE ; ++i){
        for(int j = 0 ; j < BOARD_DIMENSION ; ++j){
            cout << population[i][j] << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

int main(){
    srand(time(NULL));
    return run();
}
