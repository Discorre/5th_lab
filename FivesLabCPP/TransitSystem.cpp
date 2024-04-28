#include <sstream>
#include "TransitSystem.h" // Подключение заголовочного файла TransitSystem.h, содержащего объявление класса

using namespace std;

TransitSystem::TransitSystem() {} // Реализация конструктора класса TransitSystem

void TransitSystem::executeCommands() { // Реализация функции выполнения команд
    string command; // Объявление переменной для хранения введенной команды
    while (true) { // Бесконечный цикл для ввода команд
        cout << ">>> "; // Вывод приглашения для ввода команды
        getline(cin, command); // Получение строки команды от пользователя
        if (command == "EXIT") break; // Если введена команда "EXIT", завершить цикл

        vector<string> commandParts; // Создание вектора для хранения частей команды
        string part; // Переменная для хранения каждой части команды
        istringstream iss(command); // Создание объекта stringstream для разбора строки команды
        while (iss >> part) { // Цикл для разбора строки команды на отдельные части
            commandParts.push_back(part); // Добавление каждой части команды в вектор
        }

        CommandType type; // Объявление переменной для хранения типа команды
        // Определение типа команды на основе первой части строки
        if (commandParts[0] == "CREATE_TRL") type = CommandType::CREATE_TRL;
        else if (commandParts[0] == "TRL_IN_STOP") type = CommandType::TRL_IN_STOP;
        else if (commandParts[0] == "STOPS_IN_TRL") type = CommandType::STOPS_IN_TRL;
        else if (commandParts[0] == "TRLS") type = CommandType::TRLS;
        else if (commandParts[0] == "HELP") type = CommandType::HELP;
        else { // Если тип команды не распознан, вывести сообщение об ошибке и продолжить цикл
            cout << "Invalid command\n";
            continue;
        }

        switch (type) { // Выполнение соответствующей команды в зависимости от типа
        case CommandType::CREATE_TRL:
            createTrolleybus(commandParts); // Вызов функции создания троллейбуса
            break;
        case CommandType::TRL_IN_STOP:
            trolleybusesInStop(commandParts); // Вызов функции вывода троллейбусов на остановке
            break;
        case CommandType::STOPS_IN_TRL:
            stopsInTrolleybus(commandParts); // Вызов функции вывода остановок для троллейбуса
            break;
        case CommandType::TRLS:
            displayTrolleybuses(); // Вызов функции отображения всех троллейбусов
            break;
        case CommandType::HELP:
            displayHelp(); // Вызов функции отображения справки
            break;
        }
    }
}

void TransitSystem::createTrolleybus(const vector<string>& command) { // Реализация функции создания троллейбуса
    string trl = command[1]; // Получение имени троллейбуса из введенной команды
    vector<string> stops(command.begin() + 2, command.end()); // Получение списка остановок из введенной команды

    trlStops[trl] = stops; // Сохранение списка остановок для данного троллейбуса
    for (const auto& stop : stops) { // Цикл по каждой остановке
        stopTrls[stop].push_back(trl); // Добавление данного троллейбуса в список проходящих через остановку
    }
}

void TransitSystem::trolleybusesInStop(const vector<string>& command) { // Реализация функции вывода троллейбусов на остановке
    string stop = command[1]; // Получение имени остановки из введенной команды
    if (stopTrls.find(stop) == stopTrls.end()) { // Проверка наличия остановки в списке
        cout << "Stops is absent\n"; // Вывод сообщения об отсутствии остановки
        return;
    }

    if (stopTrls[stop].empty()) { // Проверка наличия троллейбусов на остановке
        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбусов
        return;
    }

    for (const auto& trl : stopTrls[stop]) { // Цикл по каждому троллейбусу на остановке
        cout << trl << " "; // Вывод имени троллейбуса
    }
    cout << endl;
}

void TransitSystem::stopsInTrolleybus(const vector<string>& command) { // Реализация функции вывода остановок для троллейбуса
    string trl = command[1]; // Получение имени троллейбуса из введенной команды
    if (trlStops.find(trl) == trlStops.end()) { // Проверка наличия троллейбуса в списке
        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбуса
        return;
    }

    if (trlStops[trl].empty()) { // Проверка наличия остановок для троллейбуса
        cout << "Stops is absent\n"; // Вывод сообщения об отсутствии остановок
        return;
    }

    for (const auto& stop : trlStops[trl]) { // Цикл по каждой остановке для троллейбуса
        cout << "Stop " << stop << ": "; // Вывод имени остановки
        for (const auto& trlPassing : stopTrls[stop]) { // Цикл по каждому троллейбусу на остановке
            if (trlPassing != trl) { // Если это не тот же троллейбус, что исследуется
                cout << trlPassing << " "; // Вывод имени проходящего троллейбуса
            }
        }
        cout << endl;
    }
}

void TransitSystem::displayTrolleybuses() { // Реализация функции отображения всех троллейбусов
    if (trlStops.empty()) { // Проверка наличия троллейбусов в системе
        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбусов
        return;
    }
    for (const auto& trl : trlStops) { // Цикл по каждому троллейбусу в системе
        cout << "TRL " << trl.first << ": "; // Вывод имени троллейбуса
        for (const auto& stop : trl.second) { // Цикл по каждой остановке для данного троллейбуса
            cout << stop << " "; // Вывод имени остановки
        }
        cout << endl;
    }
}

void TransitSystem::displayHelp() { // Реализация функции отображения справки
    cout << "Доступные команды:\n"
        << "CREATE_TRL trl stop1 stop2 ... - Создать троллейбус с именем trl, проходящий через остановки stop1, stop2, ...\n"
        << "TRL_IN_STOP stop - Вывод всех троллейбусов, которые проходят через конкретную остановку\n"
        << "STOPS_IN_TRL trl - Вывод всех остановок, которые проезжает троллейбус с именем trl.Для каждой остановки прописать,\nкакие троллейбусы идут через эту остановку(не включая trl)\n"
        << "TRLS - Отобразить все троллейбусы с указанием остановок\n"
        << "HELP - Отобразить это справочное сообщение\n"
        << "EXIT - Выйти из программы\n";
}