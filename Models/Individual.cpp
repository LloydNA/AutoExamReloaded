#include <vector>
#include <unordered_map>
#include "./Career.cpp"

struct Individual{
	int individualsAmount;
	std::vector<int> individual;
	float fitnessScore;
	
	std::unordered_map<std::string, std::vector<unsigned int>> careers;
	
	Individual(int individualsAmount, std::vector<Career> &careersList){
		individual = std::vector<int>(individualsAmount, 0);
		this->individualsAmount = individualsAmount;
		fitnessScore = 0.0;
		
		for(Career &a: careersList)
			careers[a.name] = std::vector<unsigned int>(12, 0);
	}
	
	Individual(std::vector<int> individual, std::vector<Career> &careersList){
		individualsAmount = individual.size();
		this->individual = individual;
		fitnessScore = 0.0;
		
		for(Career &a: careersList)
			careers[a.name] = std::vector<unsigned int>(12, 0);
	}
	
	bool operator<(const Individual& a) const{
		return this->fitnessScore < a.fitnessScore;
	}
	
	bool operator>(const Individual& a) const{
		return this->fitnessScore > a.fitnessScore;
	}
	
	bool operator==(const Individual& a) const{
		return this->fitnessScore == a.fitnessScore;
	}
};