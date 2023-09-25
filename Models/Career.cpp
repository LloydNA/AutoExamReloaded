#include <vector>
#include <string>

struct Career{
  std::string name;
  unsigned int id;
  

  std::vector<unsigned int> examsPerDay;

  Career(std::string name, std::vector<unsigned int> examsPerDay){
    this->name = name;
    this->examsPerDay = examsPerDay;
  }
};

//TODO: Id manager to avoid repeated ids