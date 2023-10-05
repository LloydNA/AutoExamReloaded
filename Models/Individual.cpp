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
	
	bool operator<(const Individual& a){
		return this->fitnessScore < a.fitnessScore;
	}
	
	bool operator>(const Individual& a){
		return this->fitnessScore > a.fitnessScore;
	}
	
	bool operator==(const Individual& a){
		return this->fitnessScore == a.fitnessScore;
	}
};