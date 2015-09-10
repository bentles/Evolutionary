#include "ga.h"

namespace ga
{
    std::random_device GeneticAlgorithm::rd;
    std::mt19937 GeneticAlgorithm::mt(GeneticAlgorithm::rd());
    
    double GeneticAlgorithm::getFitness(int i) {
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

        double elec_expense = exp(0.01*elec_kwh);

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

    vector<int> GeneticAlgorithm::selectForTournament() {
        vector<int> selection;
        std::uniform_real_distribution<double> dist(0.0,1.0);
        int select_size = (int)floor(chromosome.size() * tournament_percent);

        for (int i = 0; i < select_size; i++) {
            selection.push_back((int)floor(dist(mt) * (pop_size)));            
        }

        return selection;
    }

    int GeneticAlgorithm::selectTournament() {
        vector<int> tourn = selectForTournament();
        int maxfitpos = 0;
        double maxfit = -DBL_MAX;
        for (int i = 0; i < tourn.size(); i++) {
            double fitness = getFitness(tourn[i]);
            // std::cout << tourn[i] << ": " << fitness << std::endl ;
            if (fitness > maxfit)
            {
                //std::cout << "BIGGER" << std::endl;
                maxfit = fitness;
                maxfitpos = tourn[i];
            }
        }
        //std::cout << "PARENT:" << maxfitpos << std::endl;
        return maxfitpos;
    }

    void GeneticAlgorithm::crossOverMutate(int p1, int p2,
                                           vector<double>& child1,
                                           vector<double>& child2) {
        std::uniform_real_distribution<double> dist(0.0,1.0);
        std::normal_distribution<double> ndist(0.0,stddev);
        for (int i = 0; i < chromosome[0].size(); i++)  {
            double crossover = dist(mt);
            double mutate1 = dist(mt);
            double mutate2 = dist(mt);
            double mutation1 = mutate1 < mutate_chance? ndist(mt) : 0;
            double mutation2 = mutate2 < mutate_chance? ndist(mt) : 0;
            double mutated1 = chromosome[p1][i] + mutation1 < 0 ? 0 :
                chromosome[p1][i] + mutation1;
            double mutated2 = chromosome[p2][i] + mutation2 < 0 ? 0 :
                chromosome[p2][i] + mutation2;   
            
            if (crossover > 0.5) {              
                child1.push_back(mutated1);
                child2.push_back(mutated2);
            }
            else {
                child1.push_back(mutated2);
                child2.push_back(mutated1);
            }
        }                
    }

    void GeneticAlgorithm::runFor(int iterations) {
        for (int i = 0; i < iterations; i++) {
            //printPopulation();
            vector<vector<double> > children;
            while (children.size() < chromosome.size()) {            
                vector<double> child1;
                vector<double> child2;
                int parent1 = selectTournament();
                int parent2 = selectTournament();
                //std::cout <<"----------------------PARENTS CHOSEN---------------------:" << std::endl;
                //std::cout << parent1 << ":" << parent2 << std::endl;
                crossOverMutate(parent1, parent2, child1, child2);
                children.push_back(child1);
                children.push_back(child2);
            }
            int pos = getMaxFitPos();
            double fit = getFitness(pos); 
            if (fit > best_fitness)
                newBest(pos, fit);

            if (verbose && (i % 1000) == 0 ) {
                std::cout << "Iteration: " << i << std::endl;
                std::cout << "Fitness: " << fit << std::endl;
                std::cout << "Alloys: " ;
                std::cout << "\t1: " << chromosome[pos][0] << ",";
                std::cout << "\t2: " << chromosome[pos][1] << ",";
                std::cout << "\t3: " << chromosome[pos][2] << ",";
                std::cout << "\t4: " << chromosome[pos][3] << std::endl; 
            }
            //gg old gen
            chromosome = children;
        }

        std::cout << "Fitness: " << best_fitness << std::endl;
        std::cout << "Alloys: " ;
        std::cout << "\t1: " << best_chromo[0] << ",";
        std::cout << "\t2: " << best_chromo[1] << ",";
        std::cout << "\t3: " << best_chromo[2] << ",";
        std::cout << "\t4: " << best_chromo[3] << std::endl; 
    }

    int GeneticAlgorithm::getMaxFitPos() {
        double maxfit = -DBL_MAX;
        int fitpos = 0;
        for (int i = 0; i < chromosome.size(); i++) {
            double fitness = getFitness(i);
            if (fitness > maxfit)
            {
                maxfit = fitness;
                fitpos = i;
            }
        }
        return fitpos;
    }

    GeneticAlgorithm::GeneticAlgorithm(
        int pop_size,
        double stddev,
        double tourn_percent,
        double mutate_chance) :
        pop_size(pop_size),
        stddev(stddev),
        verbose(false),
        tournament_percent(tourn_percent),
        mutate_chance(mutate_chance), best_fitness(-DBL_MAX) {
        std::uniform_real_distribution<double> dist(0.0,1.0);
        for (int i = 0; i < pop_size; i++) {
            vector<double> cur;
            for (int j = 0; j < 4; j++) {                
                int kg= (int)floor(dist(mt) * (51));
                cur.push_back(kg);
            }
            chromosome.push_back(cur);
        }
    }

    GeneticAlgorithm GeneticAlgorithm::Verbose(bool isverbose) {
        verbose = isverbose;
        return *this;
    }

    void GeneticAlgorithm::newBest(int i, double fitness)
    {
        best_fitness = fitness;
        best_chromo = chromosome[i];

        std::cout << "NEW RECORD!" << std::endl;
        std::cout << "Fitness: " << std::setprecision(15) << best_fitness << std::endl;
        std::cout << "Alloys: " << std::setprecision(5) ;
        std::cout << "\t1: " << best_chromo[0] << ",";
        std::cout << "\t2: " << best_chromo[1] << ",";
        std::cout << "\t3: " << best_chromo[2] << ",";
        std::cout << "\t4: " << best_chromo[3] << std::endl; 
        
    }
    void GeneticAlgorithm::printPopulation()
    {
        for (int i = 0; i < chromosome.size(); i++) {
            std::cout << i << ":\t";
            for (int j = 0; j < chromosome[i].size(); j++) {
                std::cout << chromosome[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }
}

    int main() {
        using namespace ga;
        
        GeneticAlgorithm ga(
            200, //pop_size
            0.3,//std_dev
            0.1, //percent of population chosen per tournament
            0.2); //mutation chance
        ga.Verbose(false);
        ga.runFor(10000000);        
        return 0;
       }
