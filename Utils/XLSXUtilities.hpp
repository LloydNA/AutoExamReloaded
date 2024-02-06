#include <OpenXLSX.hpp>

#include "../Models/Career.cpp"
#include "../Models/Subject.cpp"

using namespace OpenXLSX;

class XLSXUtilities {
public:
    XLSXUtilities(std::string, std::string, unsigned int, unsigned int);
    std::vector<Career> readCareers();
    std::vector<Subject> readSubjects();

    void test();

private:
    XLDocument document;
    XLWorksheet databaseSheet;

    std::unordered_map<std::string, Career> careersMap;
    std::unordered_map<char, std::string> column2careersMap;
    std::unordered_map<std::string, Subject> subjectsMap;

    unsigned int initialRowIndex;
    unsigned int finalRowIndex;

    char initialCareersColumn = 'E';
    char finalCareersColumn = 'K';

    char classNumberColumn = 'O';

    char initialDaysColumn = 'P';
    char finalDaysColumn = 'U';

    char academyColumn = 'O';
};