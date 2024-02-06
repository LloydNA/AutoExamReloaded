#include <XLSXUtilities.hpp>

XLSXUtilities::XLSXUtilities(std::string url, std::string sheetName, unsigned int initialRowIndex, unsigned int finalRowIndex){
    document.open(url);
    databaseSheet = document.workbook().worksheet(sheetName);

    this->initialRowIndex = initialRowIndex;
    this->finalRowIndex = finalRowIndex;

    column2careersMap['E'] = "II";
    column2careersMap['F'] = "IM";
    column2careersMap['G'] = "IID";
    column2careersMap['H'] = "IIA";
    column2careersMap['I'] = "ITE";
    column2careersMap['J'] = "ICA";
    column2careersMap['K'] = "IBE";
}

std::vector<Career> XLSXUtilities::readCareers(){
    std::vector<Career> careers = {Career("II2"), Career("II7"),
                                   Career("II6"), Career("II1"),
                                   Career("II5"), Career("II3"),
                                   Career("II4"), Career("II8"),
                                   Career("IM2"), Career("IM7"),
                                   Career("IM1"), Career("IM3"),
                                   Career("IM6"), Career("IM4"),
                                   Career("IM5"), Career("IM8"),
                                   Career("IID7"), Career("IID1"),
                                   Career("IID5"), Career("IID3"),
                                   Career("IID4"), Career("IID8"),
                                   Career("IID2"), Career("IID6"),
                                   Career("IIA2"), Career("IIA7"),
                                   Career("IIA1"), Career("IIA3"),
                                   Career("IIA8"), Career("IIA5"),
                                   Career("IIA4"), Career("IIA6"),
                                   Career("ITE2"), Career("ITE7"),
                                   Career("ITE1"), Career("ITE4"),
                                   Career("ITE3"), Career("ITE6"),
                                   Career("ITE8"), Career("ITE5"),
                                   Career("ICA9"), Career("ICA1"),
                                   Career("ICA7"), Career("ICA3"),
                                   Career("ICA4"), Career("ICA5"),
                                   Career("ICA2"), Career("ICA6"),
                                   Career("ICA8"), Career("ICA10"),
                                   Career("IBE2"), Career("IBE5"),
                                   Career("IBE1"), Career("IBE3"),
                                   Career("IBE4"), Career("IBE8"),
                                   Career("IBE7"), Career("IBE6")};

    for(Career &a:careers)
        careersMap.insert({a.name, a});

    return careers;
}

std::vector<Subject> XLSXUtilities::readSubjects(){
    for(int row = initialRowIndex; row <= finalRowIndex; row++){
        std::string classNumberCellType = databaseSheet.cell(std::string(1, classNumberColumn) + std::to_string(row)).value().typeAsString();
        std::string classNumber = classNumberCellType == "integer" ? std::to_string(databaseSheet.cell(std::string(1, classNumberColumn) + std::to_string(row)).value().get<int>()) : databaseSheet.cell(std::string(1, classNumberColumn) + std::to_string(row)).value().get<std::string>();

        if(subjectsMap.find(classNumber) == subjectsMap.end()){
            std::vector<unsigned int> scheduledDays;

            for(char day = initialDaysColumn; day <= finalDaysColumn; day++){
                std::string currentCellValue = databaseSheet.cell(std::string(1, day) + std::to_string(row)).value().get<std::string>();

                if(!currentCellValue.empty()){
                    unsigned int currentDayAsInt = (unsigned int)(day - initialDaysColumn);
                    scheduledDays.emplace_back(currentDayAsInt);
                    scheduledDays.emplace_back(currentDayAsInt + 6);
                }

            }

            std::sort(scheduledDays.begin(), scheduledDays.end());

            std::vector<Career> assignedCareers;

            for(char career = initialCareersColumn; career <= finalCareersColumn; career++){
                std::string currentCellType = databaseSheet.cell("A" + std::string(1, career) + std::to_string(row)).value().typeAsString();
                std::string currentCellValue = currentCellType == "integer" ? std::to_string(databaseSheet.cell("A" + std::string(1, career) + std::to_string(row)).value().get<int>()) : "";

                if(!currentCellValue.empty()) {
                    std::string currentCareerName = column2careersMap[career];
                    currentCareerName += currentCellValue;

                    assignedCareers.emplace_back(careersMap.at(currentCareerName));
                }
            }

            std::string academyCell = databaseSheet.cell("A" + std::string(1, academyColumn) + std::to_string(row)).value().get<std::string>();

            bool isHumanities = academyCell == "HUM";

            Subject newSubject(classNumber, 1.0f, scheduledDays, assignedCareers, isHumanities);

            newSubject.rowIndexes.emplace_back(row);

            subjectsMap.insert({classNumber, newSubject});
        }else{
            subjectsMap.at(classNumber).rowIndexes.emplace_back(row);

            for(char day = initialDaysColumn; day <= finalDaysColumn; day++){
                std::string currentCellValue = databaseSheet.cell(std::string(1, day) + std::to_string(row)).value().get<std::string>();

                if(!currentCellValue.empty()){
                    unsigned int currentDayAsInt = (unsigned int)(day - initialDaysColumn);
                    subjectsMap.at(classNumber).scheduledDays.emplace_back(currentDayAsInt);
                    subjectsMap.at(classNumber).scheduledDays.emplace_back(currentDayAsInt + 6);
                }

            }

            std::sort(subjectsMap.at(classNumber).scheduledDays.begin(), subjectsMap.at(classNumber).scheduledDays.end());
        }

    }

    std::vector<Subject> subjects;

    for(auto current:subjectsMap)
        subjects.emplace_back(current.second);

    return subjects;
}

void XLSXUtilities::test(){
    //std::cout << databaseSheet.cell("B2").value().get<std::string>();
    std::cout << databaseSheet.cell("AJ3").value().typeAsString();
}