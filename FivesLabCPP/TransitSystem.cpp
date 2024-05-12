//#include <sstream>
//#include "TransitSystem.h" // Подключение заголовочного файла TransitSystem.h, содержащего объявление класса
//#include <unordered_set>
//
//using namespace std;
//
//TransitSystem::TransitSystem() {} // Реализация конструктора класса TransitSystem
//
//void TransitSystem::executeCommands() {
//    string command;
//    while (true) {
//        cout << ">>> ";
//        getline(cin, command);
//        if (command == "EXIT") break;
//
//        vector<string> commandParts;
//        string part;
//        istringstream iss(command);
//        while (iss >> part) {
//            commandParts.push_back(part);
//        }
//
//        if (commandParts.empty()) { // Проверка на отсутствие ввода
//            cout << "No command entered.\n";
//            continue;
//        }
//
//        CommandType type;
//        if (commandParts[0] == "CREATE_TRL") type = CommandType::CREATE_TRL;
//        else if (commandParts[0] == "TRL_IN_STOP") type = CommandType::TRL_IN_STOP;
//        else if (commandParts[0] == "STOPS_IN_TRL") type = CommandType::STOPS_IN_TRL;
//        else if (commandParts[0] == "TRLS") type = CommandType::TRLS;
//        else if (commandParts[0] == "HELP") type = CommandType::HELP;
//        else {
//            cout << "Invalid command\n";
//            continue;
//        }
//
//        switch (type) {
//        case CommandType::CREATE_TRL:
//            if (commandParts.size() < 3) { // Проверка на количество аргументов
//                cout << "Invalid command format. Usage: CREATE_TRL trl stop1 stop2 ...\n";
//                continue;
//            }
//            createTrolleybus(commandParts);
//            break;
//        case CommandType::TRL_IN_STOP:
//            if (commandParts.size() != 2) {
//                cout << "Invalid command format. Usage: TRL_IN_STOP stop\n";
//                continue;
//            }
//            trolleybusesInStop(commandParts);
//            break;
//        case CommandType::STOPS_IN_TRL:
//            if (commandParts.size() != 2) {
//                cout << "Invalid command format. Usage: STOPS_IN_TRL trl\n";
//                continue;
//            }
//            stopsInTrolleybus(commandParts);
//            break;
//        case CommandType::TRLS:
//            displayTrolleybuses();
//            break;
//        case CommandType::HELP:
//            displayHelp();
//            break;
//        }
//    }
//}
//
//void TransitSystem::createTrolleybus(const vector<string>& command) {
//    string trl = command[1];
//    vector<string> stops(command.begin() + 2, command.end());
//
//    // Проверка наличия троллейбуса с таким именем
//    if (trlStops.find(trl) != trlStops.end()) {
//        cout << "Trolleybus with the same name already exists.\n";
//        return;
//    }
//
//    // Проверка на количество остановок
//    if (stops.size() < 2) {
//        cout << "Trolleybus must have at least two stops.\n";
//        return;
//    }
//
//    // Проверка на уникальность остановок в маршруте троллейбуса
//    unordered_set<string> uniqueStops;
//    for (const auto& stop : stops) {
//        if (uniqueStops.count(stop) > 0) {
//            cout << "Duplicate stop " << stop << " in trolleybus route.\n";
//            return;
//        }
//        uniqueStops.insert(stop);
//    }
//
//    // Проверка на неположительный номер троллейбуса
//    try {
//        int trlNumber = stoi(trl);
//        if (trlNumber <= 0) {
//            cout << "Trolleybus number must be a positive integer.\n";
//            return;
//        }
//    }
//    catch (const invalid_argument& e) {
//        cout << "Invalid trolleybus number.\n";
//        return;
//    }
//    catch (const out_of_range& e) {
//        cout << "Trolleybus number is out of range.\n";
//        return;
//    }
//
//    // Проверка на повторение пути другого троллейбуса
//    for (const auto& existingTrl : trlStops) {
//        const auto& existingStops = existingTrl.second;
//        if (existingStops.size() == stops.size()) {
//            bool sameRoute = true;
//            for (size_t i = 0; i < stops.size(); ++i) {
//                if (existingStops[i] != stops[i]) {
//                    sameRoute = false;
//                    break;
//                }
//            }
//            if (sameRoute) {
//                cout << "Trolleybus with the same route already exists.\n";
//                return;
//            }
//        }
//    }
//
//    // Добавление троллейбуса и его маршрута
//    trlStops[trl] = stops;
//    for (const auto& stop : stops) {
//        stopTrls[stop].push_back(trl);
//    }
//}
//
//void TransitSystem::trolleybusesInStop(const vector<string>& command) { // Реализация функции вывода троллейбусов на остановке
//    string stop = command[1]; // Получение имени остановки из введенной команды
//    if (stopTrls.find(stop) == stopTrls.end()) { // Проверка наличия остановки в списке
//        cout << "Stops is absent\n"; // Вывод сообщения об отсутствии остановки
//        return;
//    }
//
//    if (stopTrls[stop].empty()) { // Проверка наличия троллейбусов на остановке
//        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбусов
//        return;
//    }
//
//    for (const auto& trl : stopTrls[stop]) { // Цикл по каждому троллейбусу на остановке
//        cout << trl << " "; // Вывод имени троллейбуса
//    }
//    cout << endl;
//}
//
//void TransitSystem::stopsInTrolleybus(const vector<string>& command) { // Реализация функции вывода остановок для троллейбуса
//    string trl = command[1]; // Получение имени троллейбуса из введенной команды
//    if (trlStops.find(trl) == trlStops.end()) { // Проверка наличия троллейбуса в списке
//        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбуса
//        return;
//    }
//
//    if (trlStops[trl].empty()) { // Проверка наличия остановок для троллейбуса
//        cout << "Stops is absent\n"; // Вывод сообщения об отсутствии остановок
//        return;
//    }
//
//    for (const auto& stop : trlStops[trl]) { // Цикл по каждой остановке для троллейбуса
//        cout << "Stop " << stop << ": "; // Вывод имени остановки
//        for (const auto& trlPassing : stopTrls[stop]) { // Цикл по каждому троллейбусу на остановке
//            if (trlPassing != trl) { // Если это не тот же троллейбус, что исследуется
//                cout << trlPassing << " "; // Вывод имени проходящего троллейбуса
//            }
//        }
//        cout << endl;
//    }
//}
//
//void TransitSystem::displayTrolleybuses() { // Реализация функции отображения всех троллейбусов
//    if (trlStops.empty()) { // Проверка наличия троллейбусов в системе
//        cout << "Trams is absent\n"; // Вывод сообщения об отсутствии троллейбусов
//        return;
//    }
//    for (const auto& trl : trlStops) { // Цикл по каждому троллейбусу в системе
//        cout << "TRL " << trl.first << ": "; // Вывод имени троллейбуса
//        for (const auto& stop : trl.second) { // Цикл по каждой остановке для данного троллейбуса
//            cout << stop << " "; // Вывод имени остановки
//        }
//        cout << endl;
//    }
//}
//
//void TransitSystem::displayHelp() { // Реализация функции отображения справки
//    cout << "Доступные команды:\n"
//        << "CREATE_TRL trl stop1 stop2 ... - Создать троллейбус с именем trl, проходящий через остановки stop1, stop2, ...\n"
//        << "TRL_IN_STOP stop - Вывод всех троллейбусов, которые проходят через конкретную остановку\n"
//        << "STOPS_IN_TRL trl - Вывод всех остановок, которые проезжает троллейбус с именем trl.Для каждой остановки прописать,\nкакие троллейбусы идут через эту остановку(не включая trl)\n"
//        << "TRLS - Отобразить все троллейбусы с указанием остановок\n"
//        << "HELP - Отобразить это справочное сообщение\n"
//        << "EXIT - Выйти из программы\n";
//}