#include <OpenXLSX.hpp>

#include "../Models/Career.cpp"
#include "../Models/Subject.cpp"

using namespace OpenXLSX;

class XLSXUtilities {
public:
    XLSXUtilities(std::string);


private:
    XLDocument document;
};