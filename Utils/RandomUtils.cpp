#import "RandomUtils.hpp"

RandomUtils* RandomUtils::getInstance(){
	if(instance == nullptr)
		instance = new RandomUtils();
	
	return instance;
}

int RandomUtils::uniformRandInt(int begin, int end) {
	std::uniform_int_distribution<int> distribution(begin, end);
	
	return distribution(generator);
}