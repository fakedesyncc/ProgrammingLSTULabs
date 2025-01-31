/* лаб 4 прога 2 сем */
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

struct Train {
    std::string destination;
    int trainNumber;
    std::string departureTime;
};

std::vector<Train> createTrainContainer() {
    std::vector<Train> trainContainer;
    int numTrains;
    std::cout << "Введите количество поездов: ";
    std::cin >> numTrains;
    std::cin.ignore();

    for (int i = 0; i < numTrains; i++) {
        Train newTrain;
        std::cout << "Введите пункт назначения поезда: ";
        std::getline(std::cin, newTrain.destination);
        std::cout << "Введите номер поезда: ";
        std::cin >> newTrain.trainNumber;
        std::cin.ignore();
        std::cout << "Введите время отправления (формат: ЧЧ:ММ): ";
        std::getline(std::cin, newTrain.departureTime);
        trainContainer.push_back(newTrain);
    }
    return trainContainer;
}

void sortByDestination(std::vector<Train>& trainContainer) {
    std::sort(trainContainer.begin(), trainContainer.end(), [](const Train& t1, const Train& t2) {
        return t1.destination < t2.destination;
    });
}

void printTrainsAfterTime(const std::vector<Train>& trainContainer, const std::string& time) {
    std::cout << "Поезда, отправляющиеся после " << time << ":\n";
    for (const auto& train : trainContainer) {
        if (train.departureTime > time) {
            std::cout << "Номер поезда: " << train.trainNumber << ", Пункт назначения: " << train.destination << "\n";
        }
    }
}

int main() {
    std::vector<Train> trainContainer = createTrainContainer();
    sortByDestination(trainContainer);

    std::string desiredDepartureTime;
    std::cout << "Введите время (формат: ЧЧ:ММ): ";
    std::getline(std::cin, desiredDepartureTime);

    printTrainsAfterTime(trainContainer, desiredDepartureTime);

    return 0;
}
