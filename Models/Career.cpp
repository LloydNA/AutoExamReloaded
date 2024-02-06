#include <vector>
#include <string>

#pragma once

struct Career{
  std::string name;

  std::vector<unsigned int> examsPerDay;

  Career(std::string name){
    this->name = name;
    this->examsPerDay = std::vector<unsigned int>();
  }
};