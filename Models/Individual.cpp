#include <vector>

struct Individual{
	int individualsAmount;
	std::vector<int> individual;
	float fitnessScore;
	
	Individual(int individualsAmount){
		individual = std::vector<int>(individualsAmount * 2, 0);
	}
}