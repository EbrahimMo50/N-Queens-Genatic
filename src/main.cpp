#include <bits/stdc++.h>
#include "./Engine/huerstics.cpp"
#include "./Engine/generator.cpp"

using namespace std;

const int BOARD_DIMENSION = 5;
const int MAX_GENERATION = 1000;
const int POPULATION_SIZE = 1000;
const int NUMBER_QUEENS = 5;        //only effective when used in (queens < board dim) state

pair<int*,int> bestState = make_pair(new int[BOARD_DIMENSION], numeric_limits<int>::max());

// returns the ratio by which count attacks was decreased in the 2 populations
float calculate_success(int** oldPopulation, int** newPopulation, int populationSize, int dimensionSize){
    int countAttacksOld = 0;
    int countAttacksNew = 0;
    for(int i = 0 ; i < populationSize ; ++i){
        int attacksNew = calculate_count_attacks(newPopulation[i], dimensionSize);
        countAttacksOld += calculate_count_attacks(oldPopulation[i], dimensionSize);
        countAttacksNew += attacksNew;
        if(attacksNew < bestState.second){
            for(int j = 0 ; j < BOARD_DIMENSION ; ++j){
                bestState.first[j] = newPopulation[i][j];
            }
            bestState.second = attacksNew;
        }
    }
    return 1 - float(countAttacksOld) / float(countAttacksNew);
}

void free_2D_array(int** array, int size) {
    if (array == nullptr) return;

    for (int i = 0; i < size; ++i)
        delete[] array[i];
    delete[] array;
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
        int** mutatedPopulation = mutation(crossOver, POPULATION_SIZE, BOARD_DIMENSION, 0.01);

        float successRate = calculate_success(population, mutatedPopulation, POPULATION_SIZE, BOARD_DIMENSION);
        cout << "Success rate in new poopulation (" << successRate * 100 << "%)\n";

        cout << "---------------------------------------\n";

        // Free old memory (HAS GREAT IMPACT ON PERFORMACE TIME)

        // free_2D_array(population, POPULATION_SIZE);
        // free_2D_array(newPopulation, POPULATION_SIZE);
        // free_2D_array(crossOver, POPULATION_SIZE);

        population = mutatedPopulation;
        delete[] fitness;
    }

    for(int i = 0 ; i < POPULATION_SIZE ; ++i){
        for(int j = 0 ; j < BOARD_DIMENSION ; ++j){
            cout << population[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "---------------------------------------\n";

    cout << "best found state is: ";
    for(int i = 0 ; i < BOARD_DIMENSION ; ++i){
            cout << bestState.first[i] << " ";
    }
    cout << "\nwith count attacks " << bestState.second << "\n";

    cout << "---------------------------------------\n";
    return 0;
}

int main(){
    srand(time(NULL));
    return run();
}
