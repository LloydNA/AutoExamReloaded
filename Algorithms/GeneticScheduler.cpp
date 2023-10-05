#include <iostream>
#include <vector>

#include "./GeneticScheduler.hpp"

#include "../Utils/RandomUtils.hpp"

GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize, unsigned int initialDay, unsigned int finalDay, std::vector<Career> &careers, std::vector<Subject> &subjects){
  this->populationSize = populationSize;
  this->initialDay = initialDay;
  this->finalDay = finalDay;
  
  this->careers = careers;
  this->subjects = subjects;
  
  this->elite = {nullptr, 0.0};
}

void GeneticAlgorithm::genesis(){
  unsigned int sz = subjects.size();
  population = std::vector<Individual>(populationSize);
  
  for(unsigned int i = 0; i < populationSize; i++){
    Individual currentIndividual(sz);
    for(unsigned int j = 0; j < sz; j++){
      if(subjects[j].isHumanities)
        currentIndividual.individual[j] = subjects[j].scheduledDays[0]; //Assuming that scheduled days are sorted
      else{
        int randomIndex = rand() % subjects[j].scheduledDays.size();
        currentIndividual.individual[j] = subjects[j].scheduledDays[randomIndex];
      }
    }
  }
    
}

void GeneticAlgorithm::fitness(){
  
}

void GeneticAlgorithm::mutation(Individual &individual){
  unsigned int sz = subjects.size();
  
  int randomIndex1 = rand() % sz;
  int randomIndex2 = rand() % sz;
  
  while(subjects[randomIndex1].isHumanities) // Ensure that we are not touching humanities
    randomIndex1 = rand() % sz;
  
  while(randomIndex1 == randomIndex2 || subjects[randomIndex2].isHumanities)
    randomIndex2 = rand() % sz;
  
  std::swap(individual.individual[randomIndex1], individual.individual[randomIndex2]);
}

Individual GeneticAlgorithm::crossover(Individual &parent1, Individual &parent2){
  unsigned int sz = subjects.size();
  
  int randomIndex1 = rand() % (sz - 1) + 1;
  
  std::vector<int> fusedIndividual;
  
  fusedIndividual.insert(fusedIndividual.end(), parent1.individual.begin(), parent1.individual.begin() + randomIndex1); //[)
  fusedIndividual.insert(fusedIndividual.end(), parent2.individual.begin() + randomIndex1, parent2.individual.end()); 
  
  Individual newIndividual(fusedIndividual);
  
  return newIndividual;
}

Individual &GeneticAlgorithm::binaryTournament(){
  int randomIndex1 = rand() % populationSize;
  int randomIndex2 = rand() % populationSize;
  
  while(randomIndex1 == randomIndex2)
    randomIndex2 = rand() % populationSize;
  
  Individual &parent1 = population[randomIndex1];
  Individual &parent2 = population[randomIndex2];
  
  return parent1 > parent2 ? parent1 : parent2;
}
