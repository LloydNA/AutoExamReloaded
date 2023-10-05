#include <vector>
#include <string>
#include "./Career.cpp"

struct Subject{
  std::string name;
  float difficulty;
  bool isHumanities;
  
  std::vector<unsigned int> scheduledDays;
  std::vector<Career> &assignedCareers;
  
  Subject(std::string name, float difficulty, std::vector<unsigned int> scheduledDays, std::vector<Career> &assignedCareers, bool isHumanities){
    this->name = name;
    this->difficulty = difficulty;
    this->scheduledDays = scheduledDays;
    this->assignedCareers = assignedCareers;
    this->isHumanities = isHumanities;
  }
};