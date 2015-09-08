#include "ga.h"
#include <float.h>

namespace ga
{
    double GeneticAlgorithm::getFitness(int i)
    {
        double income =
            chromosome[i][0] * 3000 +
            chromosome[i][1] * 3100 +
            chromosome[i][2] * 5200 +
            chromosome[i][3] * 2500;

        double plat_kg =
            chromosome[i][0] * 0.2f +
            chromosome[i][1] * 0.3f +
            chromosome[i][2] * 0.8f +
            chromosome[i][3] * 0.1f;
        double iron_kg =
            chromosome[i][0] * 0.7f +
            chromosome[i][1] * 0.2f +
            chromosome[i][2] * 0.1f +
            chromosome[i][3] * 0.5f;
        double copper_kg =
            chromosome[i][0] * 0.1f +
            chromosome[i][1] * 0.5f +
            chromosome[i][2] * 0.1f +
            chromosome[i][3] * 0.4f;

        double elec_kwh =
            chromosome[i][0] * 25 +
            chromosome[i][1] * 23 +
            chromosome[i][2] * 35 +
            chromosome[i][3] * 20;

        double elec_expense = exp(0.01f*elec_kwh);

        double copper_expense = 0;
        if (copper_kg <= 8)
            copper_expense = copper_kg*800;
        else
            copper_expense = copper_kg*800*0.9;

        int plat_kg_floor = (int)floor(plat_kg);
        double iron_expense = 0;
        if (plat_kg_floor < iron_kg) //if we have fewer plat kgs then find excess else 0
            iron_expense = iron_kg * 300 - plat_kg_floor*300;

        double plat_expense = plat_kg*(1200 + 10* plat_kg_floor);

        double total_expense = elec_expense + iron_expense + copper_expense + plat_expense;

        return income - total_expense;            
    }

    void GeneticAlgorithm::init()
    {
        for (int i = 0; i < chromosome.size(); i++) {
            for (int j = 0; j < chromosome[0].size(); j++) {                
                int kg= (int)floor(dist(mt) * (51));
                chromosome[i][j] = kg;
            }
        }
    }

    vector<int> GeneticAlgorithm::selectForTournament()
    {
        vector<int> selection;
        int select_size = (int)floor(chromosome.size() * tournament_percent);

        for (int i = 0; i < select_size; i++) {
            selection.push_back((int)floor(dist(mt) * (51)));            
        }        
    }

    int GeneticAlgorithm::selectTournament()
    {
        vector<int> tourn = selectForTournament();
        int maxfitpos = 0;
        double maxfit = -DBL_MAX;
        for (int i = 0; i < tourn.size(); i++) {
            double fitness = getFitness(tourn[i]);
            if (fitness > maxfit)
            {
                maxfit = fitness;
                maxfitpos = i;
            }
        }
        return maxfitpos;
    }

    void GeneticAlgorithm::crossOverMutate(int p1, int p2,
                                           vector<double>& child1,
                                           vector<double>& child2)
    {
        for (int i = 0; i < chromosome[0].size(); i++)
        {
            double crossover = (dist(mt));
            double mutate1 = (dist(mt));
            double mutate2 = (dist(mt));
            double mutation1 = mutate1 > mutate_chance? ndist(mt) : 0;
            double mutation2 = mutate2 > mutate_chance? ndist(mt) : 0;            
            if (crossover > 0.5)
            {
                child1.push_back(chromosome[p1][i] + mutation1);
                child2.push_back(chromosome[p2][i] + mutation2);
            }
            else
            {
                child1.push_back(chromosome[p2][i] + mutation1);
                child2.push_back(chromosome[p1][i] + mutation2);
            }
        }

                
    }

    void GeneticAlgorithm::runFor(int i)
    {
        

    }

    GeneticAlgorithm::GeneticAlgorithm()
    {

    }
}
