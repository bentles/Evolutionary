#ifndef GENETIC_ALGORITHM_H
#define GENETIC_ALGORITHM_H

#include <vector>
#include <math.h>
#include <random>

using std::vector;

namespace ga
{
    class GeneticAlgorithm
    {
    private:
        std::random_device rd;
        std::mt19937 mt; //(rd());
        std::uniform_real_distribution<double> dist;//(start, end)
        std::normal_real_distribtion<double> ndist;//(mean, stddev)
        bool verbose;
        double tournament_percent; //percent of population in each tournament
        int num_tournaments;
        double mutate_chance;
        vector<vector<double> > chromosome;
        double getFitness(int i);
        void init();
        void crossOverMutate(int parent1, int parent2,
                                       vector<double>& child1, vector<double>& child2);
        vector<int> selectForTournament();
        int selectTournament();
        void crossOverMutate();
    public:
        void runFor(int i);
        GeneticAlgorithm();

    };
}

#endif /* GENETIC_ALGORITHM */
