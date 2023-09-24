#include <vector>
#include <string>

struct Subject{
  std::string name;
  unsigned int id;
  float difficulty;
  
  std::vector<unsigned int> scheduledDays;
  std::vector<unsigned int> assignedCareersIds;
  
  Subject(std::string name, float difficulty, std::vector<unsigned int> scheduledDays, std::vector<unsigned int> assignedCareersIds){
    this->name = name;
    this->difficulty = difficulty;
    this->scheduledDays = scheduledDays;
    this->assignedCareersIds = assignedCareersIds;
  }
};

//TODO: Id manager to avoid repeated ids