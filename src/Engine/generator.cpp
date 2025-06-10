#include <bits/stdc++.h>
using namespace std;

class Generator{
    public:
    // generates random seed for the program to start up with an overload
    // to have less queens than width by setting a value to the countQueens
    static int** generate_random_population(int populationSize, int boardDimension){
        return generate_random_population_implemntation(populationSize, boardDimension);
    }

    // seeds the population with -1 randomaly imetating the behaviour of no queen in the column
    static int** generate_random_population(int populationSize, int boardDimension, int countQueens){

        if(countQueens > boardDimension)
            throw out_of_range("queen's count can not be larger than board dimension");
        
        int** population = generate_random_population_implemntation(populationSize, boardDimension);

        for(int i = 0 ; populationSize > i ; ++i){
            for(int j = 0 ; boardDimension - countQueens > j ; ++j){
                int random = rand() % boardDimension;
                if(population[i][random] == -1)
                    j--;
                population[i][random] = -1;
            }
        }
        return population;
    }

    private:
    static int** generate_random_population_implemntation(int populationSize, int boardDimension){
        int** population = new int*[populationSize];

        for(int i = 0 ; populationSize > i ; ++i){
            population[i] = new int[boardDimension];

            for(int j = 0 ; boardDimension > j ; ++j){
                population[i][j] = rand() % boardDimension;
            }
        }
        return population;
    }
};