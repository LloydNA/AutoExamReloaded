#include <vector>

struct Individual{
	int individualsAmount;
	std::vector<int> individual;
	float fitnessScore;
	
	Individual(int individualsAmount){
		individual = std::vector<int>(individualsAmount, 0);
		this->individualsAmount = individualsAmount;
	}
	
	Individual(std::vector<int> individual){
		individualsAmount = individual.size();
		this->individual = individual;
	}
};