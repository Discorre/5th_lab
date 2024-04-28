#include <sstream>
#include "TransitSystem.h" // ����������� ������������� ����� TransitSystem.h, ����������� ���������� ������

using namespace std;

TransitSystem::TransitSystem() {} // ���������� ������������ ������ TransitSystem

void TransitSystem::executeCommands() { // ���������� ������� ���������� ������
    string command; // ���������� ���������� ��� �������� ��������� �������
    while (true) { // ����������� ���� ��� ����� ������
        cout << ">>> "; // ����� ����������� ��� ����� �������
        getline(cin, command); // ��������� ������ ������� �� ������������
        if (command == "EXIT") break; // ���� ������� ������� "EXIT", ��������� ����

        vector<string> commandParts; // �������� ������� ��� �������� ������ �������
        string part; // ���������� ��� �������� ������ ����� �������
        istringstream iss(command); // �������� ������� stringstream ��� ������� ������ �������
        while (iss >> part) { // ���� ��� ������� ������ ������� �� ��������� �����
            commandParts.push_back(part); // ���������� ������ ����� ������� � ������
        }

        CommandType type; // ���������� ���������� ��� �������� ���� �������
        // ����������� ���� ������� �� ������ ������ ����� ������
        if (commandParts[0] == "CREATE_TRL") type = CommandType::CREATE_TRL;
        else if (commandParts[0] == "TRL_IN_STOP") type = CommandType::TRL_IN_STOP;
        else if (commandParts[0] == "STOPS_IN_TRL") type = CommandType::STOPS_IN_TRL;
        else if (commandParts[0] == "TRLS") type = CommandType::TRLS;
        else if (commandParts[0] == "HELP") type = CommandType::HELP;
        else { // ���� ��� ������� �� ���������, ������� ��������� �� ������ � ���������� ����
            cout << "Invalid command\n";
            continue;
        }

        switch (type) { // ���������� ��������������� ������� � ����������� �� ����
        case CommandType::CREATE_TRL:
            createTrolleybus(commandParts); // ����� ������� �������� �����������
            break;
        case CommandType::TRL_IN_STOP:
            trolleybusesInStop(commandParts); // ����� ������� ������ ������������ �� ���������
            break;
        case CommandType::STOPS_IN_TRL:
            stopsInTrolleybus(commandParts); // ����� ������� ������ ��������� ��� �����������
            break;
        case CommandType::TRLS:
            displayTrolleybuses(); // ����� ������� ����������� ���� ������������
            break;
        case CommandType::HELP:
            displayHelp(); // ����� ������� ����������� �������
            break;
        }
    }
}

void TransitSystem::createTrolleybus(const vector<string>& command) { // ���������� ������� �������� �����������
    string trl = command[1]; // ��������� ����� ����������� �� ��������� �������
    vector<string> stops(command.begin() + 2, command.end()); // ��������� ������ ��������� �� ��������� �������

    trlStops[trl] = stops; // ���������� ������ ��������� ��� ������� �����������
    for (const auto& stop : stops) { // ���� �� ������ ���������
        stopTrls[stop].push_back(trl); // ���������� ������� ����������� � ������ ���������� ����� ���������
    }
}

void TransitSystem::trolleybusesInStop(const vector<string>& command) { // ���������� ������� ������ ������������ �� ���������
    string stop = command[1]; // ��������� ����� ��������� �� ��������� �������
    if (stopTrls.find(stop) == stopTrls.end()) { // �������� ������� ��������� � ������
        cout << "Stops is absent\n"; // ����� ��������� �� ���������� ���������
        return;
    }

    if (stopTrls[stop].empty()) { // �������� ������� ������������ �� ���������
        cout << "Trams is absent\n"; // ����� ��������� �� ���������� ������������
        return;
    }

    for (const auto& trl : stopTrls[stop]) { // ���� �� ������� ����������� �� ���������
        cout << trl << " "; // ����� ����� �����������
    }
    cout << endl;
}

void TransitSystem::stopsInTrolleybus(const vector<string>& command) { // ���������� ������� ������ ��������� ��� �����������
    string trl = command[1]; // ��������� ����� ����������� �� ��������� �������
    if (trlStops.find(trl) == trlStops.end()) { // �������� ������� ����������� � ������
        cout << "Trams is absent\n"; // ����� ��������� �� ���������� �����������
        return;
    }

    if (trlStops[trl].empty()) { // �������� ������� ��������� ��� �����������
        cout << "Stops is absent\n"; // ����� ��������� �� ���������� ���������
        return;
    }

    for (const auto& stop : trlStops[trl]) { // ���� �� ������ ��������� ��� �����������
        cout << "Stop " << stop << ": "; // ����� ����� ���������
        for (const auto& trlPassing : stopTrls[stop]) { // ���� �� ������� ����������� �� ���������
            if (trlPassing != trl) { // ���� ��� �� ��� �� ����������, ��� �����������
                cout << trlPassing << " "; // ����� ����� ����������� �����������
            }
        }
        cout << endl;
    }
}

void TransitSystem::displayTrolleybuses() { // ���������� ������� ����������� ���� ������������
    if (trlStops.empty()) { // �������� ������� ������������ � �������
        cout << "Trams is absent\n"; // ����� ��������� �� ���������� ������������
        return;
    }
    for (const auto& trl : trlStops) { // ���� �� ������� ����������� � �������
        cout << "TRL " << trl.first << ": "; // ����� ����� �����������
        for (const auto& stop : trl.second) { // ���� �� ������ ��������� ��� ������� �����������
            cout << stop << " "; // ����� ����� ���������
        }
        cout << endl;
    }
}

void TransitSystem::displayHelp() { // ���������� ������� ����������� �������
    cout << "��������� �������:\n"
        << "CREATE_TRL trl stop1 stop2 ... - ������� ���������� � ������ trl, ���������� ����� ��������� stop1, stop2, ...\n"
        << "TRL_IN_STOP stop - ����� ���� ������������, ������� �������� ����� ���������� ���������\n"
        << "STOPS_IN_TRL trl - ����� ���� ���������, ������� ��������� ���������� � ������ trl.��� ������ ��������� ���������,\n����� ����������� ���� ����� ��� ���������(�� ������� trl)\n"
        << "TRLS - ���������� ��� ����������� � ��������� ���������\n"
        << "HELP - ���������� ��� ���������� ���������\n"
        << "EXIT - ����� �� ���������\n";
}