//#include <sstream>
//#include "TransitSystem.h" // ����������� ������������� ����� TransitSystem.h, ����������� ���������� ������
//#include <unordered_set>
//
//using namespace std;
//
//TransitSystem::TransitSystem() {} // ���������� ������������ ������ TransitSystem
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
//        if (commandParts.empty()) { // �������� �� ���������� �����
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
//            if (commandParts.size() < 3) { // �������� �� ���������� ����������
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
//    // �������� ������� ����������� � ����� ������
//    if (trlStops.find(trl) != trlStops.end()) {
//        cout << "Trolleybus with the same name already exists.\n";
//        return;
//    }
//
//    // �������� �� ���������� ���������
//    if (stops.size() < 2) {
//        cout << "Trolleybus must have at least two stops.\n";
//        return;
//    }
//
//    // �������� �� ������������ ��������� � �������� �����������
//    unordered_set<string> uniqueStops;
//    for (const auto& stop : stops) {
//        if (uniqueStops.count(stop) > 0) {
//            cout << "Duplicate stop " << stop << " in trolleybus route.\n";
//            return;
//        }
//        uniqueStops.insert(stop);
//    }
//
//    // �������� �� ��������������� ����� �����������
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
//    // �������� �� ���������� ���� ������� �����������
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
//    // ���������� ����������� � ��� ��������
//    trlStops[trl] = stops;
//    for (const auto& stop : stops) {
//        stopTrls[stop].push_back(trl);
//    }
//}
//
//void TransitSystem::trolleybusesInStop(const vector<string>& command) { // ���������� ������� ������ ������������ �� ���������
//    string stop = command[1]; // ��������� ����� ��������� �� ��������� �������
//    if (stopTrls.find(stop) == stopTrls.end()) { // �������� ������� ��������� � ������
//        cout << "Stops is absent\n"; // ����� ��������� �� ���������� ���������
//        return;
//    }
//
//    if (stopTrls[stop].empty()) { // �������� ������� ������������ �� ���������
//        cout << "Trams is absent\n"; // ����� ��������� �� ���������� ������������
//        return;
//    }
//
//    for (const auto& trl : stopTrls[stop]) { // ���� �� ������� ����������� �� ���������
//        cout << trl << " "; // ����� ����� �����������
//    }
//    cout << endl;
//}
//
//void TransitSystem::stopsInTrolleybus(const vector<string>& command) { // ���������� ������� ������ ��������� ��� �����������
//    string trl = command[1]; // ��������� ����� ����������� �� ��������� �������
//    if (trlStops.find(trl) == trlStops.end()) { // �������� ������� ����������� � ������
//        cout << "Trams is absent\n"; // ����� ��������� �� ���������� �����������
//        return;
//    }
//
//    if (trlStops[trl].empty()) { // �������� ������� ��������� ��� �����������
//        cout << "Stops is absent\n"; // ����� ��������� �� ���������� ���������
//        return;
//    }
//
//    for (const auto& stop : trlStops[trl]) { // ���� �� ������ ��������� ��� �����������
//        cout << "Stop " << stop << ": "; // ����� ����� ���������
//        for (const auto& trlPassing : stopTrls[stop]) { // ���� �� ������� ����������� �� ���������
//            if (trlPassing != trl) { // ���� ��� �� ��� �� ����������, ��� �����������
//                cout << trlPassing << " "; // ����� ����� ����������� �����������
//            }
//        }
//        cout << endl;
//    }
//}
//
//void TransitSystem::displayTrolleybuses() { // ���������� ������� ����������� ���� ������������
//    if (trlStops.empty()) { // �������� ������� ������������ � �������
//        cout << "Trams is absent\n"; // ����� ��������� �� ���������� ������������
//        return;
//    }
//    for (const auto& trl : trlStops) { // ���� �� ������� ����������� � �������
//        cout << "TRL " << trl.first << ": "; // ����� ����� �����������
//        for (const auto& stop : trl.second) { // ���� �� ������ ��������� ��� ������� �����������
//            cout << stop << " "; // ����� ����� ���������
//        }
//        cout << endl;
//    }
//}
//
//void TransitSystem::displayHelp() { // ���������� ������� ����������� �������
//    cout << "��������� �������:\n"
//        << "CREATE_TRL trl stop1 stop2 ... - ������� ���������� � ������ trl, ���������� ����� ��������� stop1, stop2, ...\n"
//        << "TRL_IN_STOP stop - ����� ���� ������������, ������� �������� ����� ���������� ���������\n"
//        << "STOPS_IN_TRL trl - ����� ���� ���������, ������� ��������� ���������� � ������ trl.��� ������ ��������� ���������,\n����� ����������� ���� ����� ��� ���������(�� ������� trl)\n"
//        << "TRLS - ���������� ��� ����������� � ��������� ���������\n"
//        << "HELP - ���������� ��� ���������� ���������\n"
//        << "EXIT - ����� �� ���������\n";
//}