#include <iostream>
#include <XLSXUtilities.hpp>
#include <GeneticScheduler.hpp>

std::string number2day(int);

int main(){
  XLSXUtilities utilities("/Users/lloydna/Desktop/UP/7°Semestre.nosync/AutoExamReloaded/XLSX/Horarios1242.xlsm", "Base de datos", 3, 217);

  //utilities.test();
  std::vector<Career> careers = utilities.readCareers();
  std::vector<Subject> subjects = utilities.readSubjects();

  //for(Subject &a:subjects)
    //  std::cout << a.name;

  //for(Career &a: careers)
    //  std::cout << a.name;

  GeneticAlgorithm algorithm(30, 0, 10, 70, 30, careers, subjects);

  auto result = algorithm.perform(10000);

  std::cout << "\nBest fitness:" << result[0].fitnessScore << "\n\n";

  std::vector<std::string> calendar(223);

  for(int i = 0; i < subjects.size(); i++)
      for(unsigned int &a:subjects[i].rowIndexes)
          calendar[a - 3] = number2day(result[0].individual[i]);

  for(std::string &a:calendar)
      std::cout << a << '\n';

  //falta contemplar numeros de clases repetidos para repetir la fehca de examen ahi tambien
}

std::string number2day(int numberedDay){
    std::string converted = "";
    switch(numberedDay){
        case 0:
            converted = "1Lu";
            break;
        case 1:
            converted = "1Ma";
            break;
        case 2:
            converted = "1Mi";
            break;
        case 3:
            converted = "1Ju";
            break;
        case 4:
            converted = "1Vi";
            break;
        case 5:
            converted = "1Sa";
            break;
        case 6:
            converted = "2Lu";
            break;
        case 7:
            converted = "2Ma";
            break;
        case 8:
            converted = "2Mi";
            break;
        case 9:
            converted = "2Ju";
            break;
        case 10:
            converted = "2Vi";
            break;
        case 11:
            converted = "2Sa";
            break;
        default:
            converted = "ERROR";
    }

    return converted;
}