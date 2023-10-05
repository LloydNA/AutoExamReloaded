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
  void fitness(std::vector<Individual>&);
  void mutation(Individual&); // Swap mutation
  Individual crossover(Individual&, Individual&); // 1 Point crossover
  Individual &binaryTournament();
  void survivorSelection(std::vector<Individual>&);
  void calculateSolutionFitness(Individual&);
};


//Genome (candidate solution) -> vector<int> -> a vector of size n where n is the number of careers, each value is in range of [0, m) where m represents the amount
//of days in the calendar exams.

//Consider day 0, as monday of the first week, day 5 as saturday of first week, day 6 as monday of second week, and lastly day 11 as saturday of second week

//Consider every scheduled exam with a score of 10 - exams_on_same_day_per_career - 2(if a day before an easier exam took place) - 2(if a day after a harder exam takes place)
//This fitness rule it's meant to keep the least amount of shared days for exams, and to avoid an increasing difficulty curve