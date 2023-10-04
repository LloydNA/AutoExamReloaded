#include <vector>
#include "../Models/Career.cpp"
#include "../Models/Subject.cpp"
#include "../Models/Individual.cpp"

class GeneticAlgorithm {
public:
  std::pair<std::vector<Individual>, float> perform(unsigned int maxGenerations);
private:
  unsigned int populationSize;
  unsigned int initialDay;
  unsigned int finalDay;
  
  std::vector<Career> &careers;
  std::vector<Subject> &subjects;
  
  std::vector<Individual> population;
  
  std::pair<Individual&, float> elite;
  
  void genesis();
  void fitness();
  void mutation(Individual &individual); // Swap mutation
  Individual crossover(Individual &parent1, Individual &parent2); // 1 Point crossover
  Individual &binaryTournament(Individual &parent1, Individual &parent2);
  void survivorSelection();
  float calculateSolutionFitness(Individual &solution);
};


//Genome (candidate solution) -> vector<int> -> a vector of size n where n is the number of careers, each value is in range of [0, m) where m represents the amount
//of days in the calendar exams.

//GenomeModifier -> vector<int> -> a vector of same size as Genome, however, each value in this vector will be the sigma which will determine the center of a
//Gausssian distribution to select a random number as scheduled day for the corresponding day, if the selected random number is not in a scheduled day for that subject,
//It will be changed to the nearest scheduled day for that subject

//Consider day 0, as monday of the first week, day 5 as saturday of first week, day 6 as monday of second week, and lastly day 11 as saturday of second week

//This algorithm will be similar to Sin prediction one, we will have a constant modifier (gamma) for each sigma, and each sigma will be the origin for a gaussian distribution
//To select scheduled day.
//Maybe an evolutionary algorithm is not the most efficient approach for a scheduling, but it's worth trying =)