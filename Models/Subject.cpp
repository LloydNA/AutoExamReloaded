#include <utility>
#include <vector>
#include <string>
#include "./Career.cpp"

#pragma once

struct Subject{
  std::string name;
  float difficulty;
  bool isHumanities;
  
  std::vector<unsigned int> scheduledDays;
  std::vector<Career> assignedCareers;

  std::vector<unsigned int> rowIndexes;
  
  Subject(std::string name, float difficulty, std::vector<unsigned int> scheduledDays, std::vector<Career> assignedCareers, bool isHumanities): assignedCareers(std::move(assignedCareers)){
    this->name = name;
    this->difficulty = difficulty;
    this->scheduledDays = scheduledDays;
    this->isHumanities = isHumanities;
  }
};