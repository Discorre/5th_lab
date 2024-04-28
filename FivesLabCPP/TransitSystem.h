#ifndef TRANSITSYSTEM_H // �������� �� ��, ��� ������������ ���� ��� �� ��� �������
#define TRANSITSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// ������������ ��� ����� ������
enum class CommandType {
    CREATE_TRL,     // ������� ����������
    TRL_IN_STOP,    // ������� ����������� �� ���������
    STOPS_IN_TRL,   // ������� ��������� ��� �����������
    TRLS,           // ������� ��� �����������
    HELP            // ������� �������
};

class TransitSystem {
public:
    TransitSystem(); // ����������� ������

    void executeCommands(); // ����� ��� ���������� ������

private:
    // �������� ������������ ������������ � ���������, � ��������
    unordered_map<string, vector<string>> trlStops;
    unordered_map<string, vector<string>> stopTrls;

    // ��������� ������ ��� ��������� ������ �������
    void createTrolleybus(const vector<string>& command);
    void trolleybusesInStop(const vector<string>& command);
    void stopsInTrolleybus(const vector<string>& command);
    void displayTrolleybuses();
    void displayHelp();
};

#endif // ���������� ��������� ���������
