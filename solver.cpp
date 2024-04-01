#include "parcer.cpp"
#include <algorithm>

using namespace std;

class Solver; 

class individ{
    friend class Solver;
    vector<long> gene;
    long fitness;
public:
    bool operator< (const individ& ind) const{
        return (fitness < ind.fitness);
    };
     bool operator> (const individ& ind) const{
        return (fitness > ind.fitness);
    };
};

class Solver: public Parcer{
    vector<individ> population;
    
    long fitness_func(vector<long> gene){
        long res = 0, w = 0, i;
        for (i=0; i<N; i++) w += gene[i]*weight[i];
        if (w <= backpack_weight) for (i=0; i<N; i++) res += gene[i]*value[i];
        return res;
    }
    
    void crossing(long a1, long a2){
        long n = N/2, i;
        individ g1, g2;
        vector<long> gene1 = population[a1].gene, gene2 = population[a2].gene;
        for (i=0; i<n; i++){
            g1.gene.push_back(gene1[i]);
            g2.gene.push_back(gene2[i]);
        }
        for (i=n; i<N; i++){
            g1.gene.push_back(gene2[i]);
            g2.gene.push_back(gene1[i]);
        }
        long r = rand()%101, ind, d;
        //mutation
        if (r <= 5){
            ind = rand()%N, d = rand()%2;
            if (d==0) g1.gene[ind] = (g1.gene[ind]+1)%2;
            else g2.gene[ind] = (g2.gene[ind]+1)%2;
        }
        g1.fitness = fitness_func(g1.gene);
        g2.fitness = fitness_func(g2.gene);
        population.push_back(g1);
        population.push_back(g2);
    }
public:
    Solver(ifstream &f_in, long amount=2000): Parcer(f_in){
        long i,j,a,p,w=0;
        //create population
        for (i=0; i<amount; i++) {
            individ g;
            g.fitness = 0;
            for (j=0; j<N; j++) {
                a = rand()%100;
                if (a < 25) g.gene.push_back(1);
                else g.gene.push_back(0);
            }
            g.fitness = fitness_func(g.gene);
            population.push_back(g);
        }
        for (i=0; i<amount; i++){
            long a1 = rand()%amount, a2 = rand()%amount;
            while (a1==a2) a2 = rand()%amount;
            crossing(a1, a2);
            sort(population.begin(),population.end(),greater<individ>());
            population.pop_back();
            population.pop_back();
        }
        for (i=0; i<N; i++) w += population[0].gene[i]*weight[i];
        cout << population[0].fitness << " " << backpack_weight - w << endl;
        for (i=0; i<N; i++) cout << population[0].gene[i] << " ";
    }
};