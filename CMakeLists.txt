cmake_minimum_required(VERSION 3.25)
project(AutoExamReloaded)

set(CMAKE_CXX_STANDARD 17)

include_directories(Algorithms)
include_directories(Models)
include_directories(Utils)
include_directories(XLSX)

add_subdirectory(OpenXLSX)

add_executable(AutoExamReloaded
        Algorithms/EvolutionaryScheduler.cpp
        Algorithms/EvolutionaryScheduler.hpp
        Algorithms/GeneticScheduler.cpp
        Algorithms/GeneticScheduler.hpp
        Models/Career.cpp
        Models/Individual.cpp
        Models/Subject.cpp
        Utils/RandomUtils.cpp
        Utils/RandomUtils.hpp
        main.cpp Utils/XLSXUtilities.hpp Utils/XLSXUtilities.cpp Utils/PerformanceMeasurer.hpp Utils/PerformanceMeasurer.cpp)

target_link_libraries(AutoExamReloaded OpenXLSX::OpenXLSX)