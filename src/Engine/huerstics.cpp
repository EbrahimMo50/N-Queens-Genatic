#include <bits/stdc++.h>
using namespace std;
/*
returns the huerstic value for a state in a population

time complexity O(size)
*/
int calculate_count_attacks(int state[], int size){
    int countAttacks = 0;
    int checkRowAttacks[size] = {0};

    // check row attacks
    for(int i = 0; i < size ; ++ i){
        if(state[i] == -1)
            continue;
        countAttacks += checkRowAttacks[state[i]];
        checkRowAttacks[state[i]] += 1;
    }

    // check for diagonal attacks

    int checkDiagonalAttacks[size*2 - 1] = {0};
    for(int i = 0; i < size ; ++ i){
        if(state[i] == -1)
            continue;
        countAttacks += checkDiagonalAttacks[(state [i] - i) + (size - 1)];
        checkDiagonalAttacks[(state [i] - i) + (size - 1)] += 1;
    }
    
    for(int i = 0 ; i < size*2 - 1 ; ++i)
        checkDiagonalAttacks[i] = 0;

    for(int i = 0; i < size ; ++ i){
        if(state[i] == -1)
            continue;
        countAttacks += checkDiagonalAttacks[state[i] + i];
        checkDiagonalAttacks[state[i] + i] += 1;
    }
    
    return countAttacks;
}

// returns the fitness percentage of each state in array mapped the indexes to the population indexes
//
// time complexity O(populationSize*dimnesionSize)
float* calculate_fitness_for_population(int** population, int populationSize, int dimnesionSize){
    int sumAttacks = 0;
    float* fitness = new float[populationSize];

    for(int i = 0; i < populationSize; ++i){
        // maximum possible attacks minus real count attacks 
        int countAttacks = 2 * dimnesionSize - calculate_count_attacks(population[i], dimnesionSize);
        sumAttacks += countAttacks;
        fitness[i] = countAttacks;
    }

    for(int i = 0; i < populationSize; ++i){
        fitness[i] = float(fitness[i])/float(sumAttacks)*100;
    }

    return fitness;
}

// selects a new population from the fitness data provided
//
// time complexity O(populationSize^2)
int** roulette_wheel_selection(int** population, float* fitness, int populationSize, int dimensionSize){
    int** result = new int*[populationSize];
    float* cumulation = new float[populationSize];

    cumulation[0] = (float)fitness[0];
    for(int i = 1 ; populationSize > i ; ++i){
        cumulation[i] = cumulation[i-1] + (float)fitness[i];
    }

    for (int i = 0; i < populationSize; ++i) {
        result[i] = new int[dimensionSize];
        int selector = rand() % 100;
        for (int j = 0; j < populationSize; ++j) {
            if (cumulation[j] >= selector) {
                memcpy(result[i], population[j], dimensionSize * sizeof(int));
                break;
            }
        }
    }

    return result;
}

// randomly selects index and merges 2 parents from the population
//
// time complexity O(populationSize * dimensionSize)
int** random_cross_over(int** population, int populationSize, int dimensionSize){
    int** newPopulation = new int*[populationSize];

    for(int i = 0 ; i < populationSize ; ++i){
        newPopulation[i] = new int[dimensionSize];
        int pivot = 1 + rand() % (dimensionSize-3);

        for(int j = 0 ; j < dimensionSize ; ++j){
            if(pivot > j){
                newPopulation[i][j] = population[i][j];
            }
            else{
                if(i == populationSize - 1)
                    newPopulation[i][j] = population[0][j];
                else
                    newPopulation[i][j] = population[i+1][j];
            }
        }
    }

    return newPopulation;
}

// evalutes all the possible combination with sliding windows algorithm on the chromosomes
// not priotrized to be implemented since it could result in local minimum solution and will 
// cause by generations the population to be alike
//
// time complexity O(populationSize^2 * dimensionSize)
int** sliding_window_cross_over(){
    throw runtime_error("not implemented");
}

// randomly swaps two queen positions from each state in the population
//
// time complexity O(populationSize)
int** mutation(int** population, int populationSize, int dimensionSize, float mutationSuccessRate){
    int** newPopulation = new int*[populationSize];
    for(int i = 0 ; i < populationSize ; ++i){
        newPopulation[i] = new int[dimensionSize];
        memcpy(newPopulation[i], population[i], dimensionSize * sizeof(int));

        float randomRatio = float(rand() % 1000) / 1000;

        if(mutationSuccessRate < randomRatio)
            continue;

        int selectorA = rand() % dimensionSize;
        int selectorB = rand() % dimensionSize;

        swap(newPopulation[i][selectorA], newPopulation[i][selectorB]);

        population[i][rand()%dimensionSize] = rand()%dimensionSize;
    }

    return newPopulation;
}