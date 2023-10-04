#include <vector>
#include <string>

struct Career{
  std::string name;

  std::vector<unsigned int> examsPerDay;

  Career(std::string name, std::vector<unsigned int> examsPerDay){
    this->name = name;
    this->examsPerDay = examsPerDay;
  }
};