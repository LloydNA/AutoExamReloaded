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