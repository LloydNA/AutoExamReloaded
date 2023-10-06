#include <iostream>
#include <vector>
#include <algorithm>

#include "./GeneticScheduler.hpp"

#include "../Utils/RandomUtils.hpp"

GeneticAlgorithm::GeneticAlgorithm(unsigned int populationSize, unsigned int initialDay, unsigned int finalDay,
                                   unsigned int crossoverProbability, unsigned int mutationProbability, std::vector<Career> &careers,
                                   std::vector<Subject> &subjects): careers(careers), subjects(subjects){
  this->populationSize = populationSize;
  this->initialDay = initialDay;
  this->finalDay = finalDay;
  
  this->crossoverProbability = crossoverProbability;
  this->mutationProbability = mutationProbability;
}

void GeneticAlgorithm::genesis(){
  unsigned int sz = subjects.size();
  
  for(unsigned int i = 0; i < populationSize; i++){
    Individual currentIndividual(sz, careers);
    for(unsigned int j = 0; j < sz; j++){
      if(subjects[j].isHumanities)
        for(int k = 0; k < subjects[j].scheduledDays.size(); k++)
            if(subjects[j].scheduledDays[k] >= initialDay && subjects[j].scheduledDays[k] <= finalDay){
                currentIndividual.individual[j] = subjects[j].scheduledDays[k]; //Assuming that scheduled days are sorted
                break;
            }

      else{
        int randomIndex = rand() % subjects[j].scheduledDays.size();
        while(subjects[j].scheduledDays[randomIndex] < initialDay || subjects[j].scheduledDays[randomIndex] > finalDay)
            randomIndex = rand() % subjects[j].scheduledDays.size();
        currentIndividual.individual[j] = subjects[j].scheduledDays[randomIndex];
      }
    }

    population.emplace_back(currentIndividual);
  }
    
}

void GeneticAlgorithm::fitness(std::vector<Individual> &population){
  for(Individual &a:population)
    calculateSolutionFitness(a);
}

void GeneticAlgorithm::calculateSolutionFitness(Individual &solution){
  for(int i=0; i<solution.individualsAmount; i++){
    solution.fitnessScore = 5.0;
    unsigned int proposedDay = solution.individual[i];
    
    for(Career &a: subjects[i].assignedCareers){ //exams_on_same_day criteria
      solution.fitnessScore -= solution.careers[a.name][proposedDay];
      solution.careers[a.name][proposedDay]++;
    }
    
  }
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

  int randomFlipIndex = rand() % subjects[randomIndex1].scheduledDays.size();

  while(subjects[randomIndex1].scheduledDays[randomFlipIndex] < initialDay || subjects[randomIndex1].scheduledDays[randomFlipIndex] > finalDay)
      randomFlipIndex = rand() % subjects[randomIndex1].scheduledDays.size();

  individual.individual[randomIndex1] = subjects[randomIndex1].scheduledDays[randomFlipIndex]; // also change day to ensure better diversity
}

Individual GeneticAlgorithm::crossover(Individual &parent1, Individual &parent2){
  unsigned int sz = subjects.size();
  
  int randomIndex1 = rand() % (sz - 1) + 1;
  
  std::vector<int> fusedIndividual;
  
  fusedIndividual.insert(fusedIndividual.end(), parent1.individual.begin(), parent1.individual.begin() + randomIndex1); //[)
  fusedIndividual.insert(fusedIndividual.end(), parent2.individual.begin() + randomIndex1, parent2.individual.end()); 
  
  Individual newIndividual(fusedIndividual, careers);
  
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

void GeneticAlgorithm::survivorSelection(std::vector<Individual> &newPopulation){
  population.insert(population.end(), newPopulation.begin(), newPopulation.end());
  
  std::sort(population.begin(), population.end()); //Sorted from worst to better
  std::reverse(population.begin(), population.end()); //Sorted from better to worst

  while(population.size() > populationSize)
      population.pop_back(); //Discard worst elements
}

std::vector<Individual> GeneticAlgorithm::perform(unsigned int maxGenerations){
  genesis();
  fitness(population);
  
  while(maxGenerations--){
    std::vector<Individual> newPopulation;
    for(int i = 0; i < populationSize; i++){
      if((rand() % 100) <= crossoverProbability){
        Individual &parent1 = binaryTournament();
        Individual &parent2 = binaryTournament();
        
        newPopulation.emplace_back(crossover(parent1, parent2));
      }else
        newPopulation.emplace_back(binaryTournament());
      
      if((rand() % 100) <= mutationProbability)
        mutation(newPopulation.back());
    }

      survivorSelection(newPopulation);
  }
  
  return population;
}
