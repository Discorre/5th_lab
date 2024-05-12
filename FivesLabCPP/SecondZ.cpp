//#include <iostream>
//#include <queue>
//#include <vector>
//#include <algorithm>
//#include <string>
//#include <windows.h>
//
//using namespace std;
//
//// ������� ��� ������������� ������� ����������� �� ����
//static void distributeQueue(int numWindows, queue<pair<int, string>>& visitors) {
//    // ������� ������ ����, ��� ������ ���� ������������ ����� <����������������� ������������, ������ �������>
//    vector<pair<int, vector<string>>> windows(numWindows);
//
//    // ��������� ���� �� ����������� ����������������� ������������
//    sort(windows.begin(), windows.end());
//
//    // ���� ���� ���������� � �������
//    while (!visitors.empty()) {
//        // ��������� ���������� ���������� �� �������
//        auto currentVisitor = visitors.front();
//        visitors.pop();
//
//        // ���� ���� � ���������� ��������
//        auto minWindow = min_element(windows.begin(), windows.end());
//
//        // ��������� ���������� � ���������� ����
//        minWindow->second.push_back(currentVisitor.second);
//
//        // ����������� ����������������� ������������ ���� �� ����������������� ��������� ����������
//        minWindow->first += currentVisitor.first;
//    }
//
//    // ������� ������������� ����������� �� ����
//    for (int i = 0; i < numWindows; ++i) {
//        cout << "���� " << i + 1 << " (" << windows[i].first << " �����): ";
//        for (const auto& token : windows[i].second) {
//            cout << token << ", ";
//        }
//        cout << endl;
//    }
//}
//
//int main() {
//    setlocale(LC_ALL, "ru");
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
//
//    int numWindows; // ���������� ��� �������� ���������� ����
//    cout << "������� ���-�� ����: ";
//    while (!(cin >> numWindows) || numWindows <= 0) { // �������� �� ������������ ����� ���������� ����
//        cout << "������������ ����. ����������, ������� ������������� ����� �����: ";
//    }
//
//    queue<pair<int, string>> visitors; // ������� �����������, �������������� ����� <����������������� ���������, �����>
//
//    string command; // ���������� ��� �������� ������� ������������
//    cout << "������� ������� (ENQUEUE <����������������� ���������>, DISTRIBUTE ��� ����������):" << endl;
//    while (true) { // ����������� ���� ��� ��������� ������
//        cout << ">>> ";
//        cin >> command; // ���� ������� � ����������
//        if (command == "ENQUEUE") { // ���� ������� ENQUEUE
//            int duration;
//            if (!(cin >> duration) || duration <= 0) { // �������� �� ������������ ����� ����������������� ���������
//                cout << "������������ ����������������� ���������. ����������, ������� ������������� ����� �����: ";
//                continue;
//            }
//            static int tokenCounter = 1;
//            string token = "T" + to_string(tokenCounter++); // ��������� ����������� ������
//            visitors.push({ duration, token }); // ���������� ���������� � �������
//            cout << token << endl; // ����� ������ ������
//        }
//        else if (command == "DISTRIBUTE") { // ���� ������� DISTRIBUTE
//            distributeQueue(numWindows, visitors); // ����� ������� ��� ������������� ����������� �� �����
//            break; // ���������� �����
//        }
//        else { // ���� ������� �� ����������
//            cout << "������������ ���������" << endl; // ����� ��������� �� ������
//        }
//    }
//
//    return 0;
//}