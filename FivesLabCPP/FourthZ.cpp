//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <Windows.h>
//#include <random>
//#include <sstream>
//
//using namespace std;
//
//vector<int> expulsion_list; // ������ ��� �������� ������� ��������� (0 - ����������, 1 - ��������������, -1 - �����������)
//
//static void addStudents(int number) {
//    if (number > 0) { // ��������, ��� ���������� ����� ��������� ������������
//        cout << "Welcome " << number << " clever students!" << endl; // ����� ����������� ��� ����� ���������
//        for (int i = 0; i < number; ++i) {
//            expulsion_list.push_back(0); // ���������� ����� ��������� � ����� ������ � ��������� �������� "����������"
//        }
//    }
//    else {
//        cout << "Incorrect" << endl; // ���� ���������� ����� ��������� �� ������������, ����� ��������� �� ������
//    }
//}
//
//static void markSuspicious(int number_student) {
//    if (number_student >= 1 && number_student <= expulsion_list.size()) { // ��������, ��� ����� �������� ��������� � ���������� ��������
//        cout << "The suspected student " << number_student << endl; // ����� ��������� � �������������� ��������
//        expulsion_list[number_student - 1] = 1; // ������� �������� ��� ��������������� � ������
//    }
//    else {
//        cout << "Incorrect" << endl; // ���� ����� �������� ������������, ����� ��������� �� ������
//    }
//}
//
//static void markImmortal(int number_student) {
//    if (number_student >= 1 && number_student <= expulsion_list.size()) { // ��������, ��� ����� �������� ��������� � ���������� ��������
//        cout << "Student " << number_student << " is immortal!" << endl; // ����� ��������� � "�����������" ��������
//        expulsion_list[number_student - 1] = -1; // ������� �������� ��� "������������" � ������
//    }
//    else {
//        cout << "Incorrect" << endl; // ���� ����� �������� ������������, ����� ��������� �� ������
//    }
//}
//
//static void printExpulsionList() {
//    vector<int> temp_list; // ��������� ������ ��� �������� �������� �������������� ���������
//    for (int i = 0; i < expulsion_list.size(); ++i) {
//        if (expulsion_list[i] == 1) { // ���� ������� ��������������
//            temp_list.push_back(i + 1); // ��������� ��� ������ �� ��������� ������
//        }
//    }
//    cout << "List of students for expulsion:"; // ����� ��������� ������
//    for (int i = 0; i < temp_list.size(); ++i) {
//        cout << " Student " << temp_list[i]; // ����� �������� �������������� ���������
//        if (i != temp_list.size() - 1) {
//            cout << ","; // ���������� ������� ����� ������� �������, ����� ����������
//        }
//    }
//    cout << endl;
//}
//
//static void printExpulsionCount() {
//    int count = 0; // ���������� ��� �������� ���������� �������������� ���������
//    for (int i = 0; i < expulsion_list.size(); ++i) {
//        if (expulsion_list[i] == 1) { // ���� ������� ��������������
//            count++; // ����������� ������� �� 1
//        }
//    }
//    cout << "List of students for expulsion consists of " << count << " students" << endl; // ����� ���������� �������������� ���������
//}
//
//static void printHelp() { // ����� ��������� ������ ������
//    cout << "��������� �������:" << endl;
//    cout << "NEW_STUDENTS [number]: �������� � ����� ������� ��������� � ���������� number" << endl;
//    cout << "SUSPICIOUS [number_student]: ������� � ���������� ������� number_student �������� ������ ��������������\n� ������ � ��� - ���� �� ����������" << endl;
//    cout << "IMMORTAL [number_student]: ������� � ���������� ������� number_student �������� �������������\n� �� ��� - ����� �� ���������� ������. ������ �������� ����� � ����� �� ����� ���������" << endl;
//    cout << "TOP-LIST: ����� ���������������� ������ ���������, �������� � ��� - ���� �� ����������" << endl;
//    cout << "SCOUNT: ����� ���������� ���������, �������� � ��� - ���� �� ����������" << endl;
//    cout << "HELP: ���������� ��� ���������� ���������" << endl;
//    cout << "EXIT: ����� �� ���������" << endl;
//}
//
//int main() {
//    setlocale(LC_ALL, "ru"); // ��������� ������ ��� ����������� ������ �� ���������
//    SetConsoleCP(1251); // ��������� ������� �������� ������� ��� ����� �� ���������
//    SetConsoleOutputCP(1251); // ��������� ������� �������� ������� ��� ������ �� ���������
//
//    printHelp();
//
//    int i = 0;{};
//    
//    while (true) {
//        int n;
//        cout << ">>> ";
//        cin >> n; // ���� ���������� ���������� ���������
//        if (n < 1) {
//            cout << "Incorrect student number" << endl; // ����� ��������� �� ������ ��� ������������ ������ ��������
//        }
//        else {
//            expulsion_list.resize(n); // ��������� ������� ������� expulsion_list �� �������� n
//            break;
//        }
//    }
//
//    string command;
//    int number_student;
//
//    while (true) { // ���� ��������� ������, ������������ �� ��������� ������� "EXIT"
//        cout << ">>> ";
//        cin >> command;
//        if (command == "NEW_STUDENTS") {
//            cin >> number_student;
//            if (number_student < 1 || number_student > expulsion_list.size()) {
//                cout << "Incorrect student number" << endl; // ����� ��������� �� ������ ��� ������������ ������ ��������
//                continue; // ����������� ����� ��� ���������� ��������� ��������
//            }
//
//            addStudents(number_student);
//        }
//        else if (command == "SUSPICIOUS") {
//            cin >> number_student;
//            /*unsigned long long int rd;
//            mt19937_64 gen(rd);
//            uniform_int_distribution<> dis(1, n);
//            for (int i = 0; i < 10; i++) {
//                number_student = dis(gen);
//                markSuspicious(number_student);
//            }*/
//            /*number_student = dis(gen);*/
//            markSuspicious(number_student);
//        }
//        else if (command == "IMMORTAL") {
//            cin >> number_student;
//            markImmortal(number_student);
//        }
//        else if (command == "TOP-LIST") {
//            printExpulsionList();
//        }
//        else if (command == "SCOUNT") {
//            printExpulsionCount();
//        }
//        else if (command == "HELP") {
//            printHelp();
//        }
//        else if (command == "EXIT") {
//            cout << "Exiting the program..." << endl;
//            break; // ����� �� �����
//        }
//        else {
//            if (i < 100) {
//                i++;
//                cout << "Incorrect" << endl; // ����� ��������� �� ������ ��� ������������ �������
//            }
//            else {
//                break;
//            }
//        }
//    }
//    return 0;
//}
//    
