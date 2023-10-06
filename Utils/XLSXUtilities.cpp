#include <XLSXUtilities.hpp>

XLSXUtilities::XLSXUtilities(std::string url){
    document.create(url);
}