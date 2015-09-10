#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <math.h>
#include <random>
#include <float.h>
#include <iostream>
#include <iomanip>

using std::vector;

namespace ga
{
    class GeneticAlgorithm
    {
    private:
        static std::random_device rd;
        static std::mt19937 mt; //(rd());
        vector<double> best_chromo;
        double best_fitness;
        int pop_size;
        double stddev;
        bool verbose;
        double tournament_percent; //percent of population in each tournament
        double mutate_chance;
        vector<vector<double> > chromosome;
        double getFitness(int i);
        void crossOverMutate(int parent1, int parent2,
                                       vector<double>& child1, vector<double>& child2);
        vector<int> selectForTournament();
        int selectTournament();
        void crossOverMutate();
        void printPopulation();
        int getMaxFitPos();
        void newBest(int i, double fitness);
    public:
        void runFor(int i);
        GeneticAlgorithm Verbose(bool isverbose);

        GeneticAlgorithm(
            int pop_size,
            double stddev,
            double tourn_percent,
            double mutate_chance);

    };
}

#endif /* GENETIC_ALGORITHM */
