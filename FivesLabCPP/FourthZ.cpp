#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

vector<int> expulsion_list; // Вектор для хранения статуса студентов (0 - нормальный, 1 - подозрительный, -1 - бессмертный)

static void addStudents(int number) {
    if (number > 0) { // Проверка, что количество новых студентов положительно
        cout << "Welcome " << number << " clever students!" << endl; // Вывод приветствия для новых студентов
        for (int i = 0; i < number; ++i) {
            expulsion_list.push_back(0); // Добавление новых студентов в конец списка с начальным статусом "нормальный"
        }
    }
    else {
        cout << "Incorrect" << endl; // Если количество новых студентов не положительно, вывод сообщения об ошибке
    }
}

static void markSuspicious(int number_student) {
    if (number_student >= 1 && number_student <= expulsion_list.size()) { // Проверка, что номер студента находится в допустимых пределах
        cout << "The suspected student " << number_student << endl; // Вывод сообщения о подозрительном студенте
        expulsion_list[number_student - 1] = 1; // Пометка студента как подозрительного в списке
    }
    else {
        cout << "Incorrect" << endl; // Если номер студента недопустимый, вывод сообщения об ошибке
    }
}

static void markImmortal(int number_student) {
    if (number_student >= 1 && number_student <= expulsion_list.size()) { // Проверка, что номер студента находится в допустимых пределах
        cout << "Student " << number_student << " is immortal!" << endl; // Вывод сообщения о "бессмертном" студенте
        expulsion_list[number_student - 1] = -1; // Пометка студента как "бессмертного" в списке
    }
    else {
        cout << "Incorrect" << endl; // Если номер студента недопустимый, вывод сообщения об ошибке
    }
}

static void printExpulsionList() {
    vector<int> temp_list; // Временный вектор для хранения индексов подозрительных студентов
    for (int i = 0; i < expulsion_list.size(); ++i) {
        if (expulsion_list[i] == 1) { // Если студент подозрительный
            temp_list.push_back(i + 1); // Добавляем его индекс во временный вектор
        }
    }
    cout << "List of students for expulsion:"; // Вывод заголовка списка
    for (int i = 0; i < temp_list.size(); ++i) {
        cout << " Student " << temp_list[i]; // Вывод индексов подозрительных студентов
        if (i != temp_list.size() - 1) {
            cout << ","; // Добавление запятой после каждого индекса, кроме последнего
        }
    }
    cout << endl;
}

static void printExpulsionCount() {
    int count = 0; // Переменная для подсчета количества подозрительных студентов
    for (int i = 0; i < expulsion_list.size(); ++i) {
        if (expulsion_list[i] == 1) { // Если студент подозрительный
            count++; // Увеличиваем счетчик на 1
        }
    }
    cout << "List of students for expulsion consists of " << count << " students" << endl; // Вывод количества подозрительных студентов
}

static void printHelp() { // Вывод заголовка списка команд
    cout << "Доступные команды:" << endl;
    cout << "NEW_STUDENTS [number]: Добавить в конец очереди студентов в количестве number" << endl;
    cout << "SUSPICIOUS [number_student]: Студент с порядковым номером number_student является крайне подозрительным\nи входит в топ - лист на отчисление" << endl;
    cout << "IMMORTAL [number_student]: Студент с порядковым номером number_student является неприкасаемым\nи из топ - листа на отчисление уходит. Такого студента никто и ничто не может отчислить" << endl;
    cout << "TOP-LIST: Вывод отсортированного списка студентов, входящих в топ - лист на отчисление" << endl;
    cout << "SCOUNT: Вывод количества студентов, входящих в топ - лист на отчисление" << endl;
    cout << "HELP: Отобразить это справочное сообщение" << endl;
    cout << "EXIT: Выйти из программы" << endl;
}

int main() {
    setlocale(LC_ALL, "ru"); // Установка локали для корректного вывода на кириллице
    SetConsoleCP(1251); // Установка кодовой страницы консоли для ввода на кириллице
    SetConsoleOutputCP(1251); // Установка кодовой страницы консоли для вывода на кириллице

    printHelp();

    int n;
    cout << ">>> ";
    cin >> n; // Ввод начального количества студентов
    expulsion_list.resize(n); // Изменение размера вектора expulsion_list до значения n

    string command;
    int number_student;

    while (true) { // Цикл обработки команд, продолжается до получения команды "EXIT"
        cout << ">>> ";
        cin >> command;
        if (command == "NEW_STUDENTS") {
            cin >> number_student;
            addStudents(number_student);
        }
        else if (command == "SUSPICIOUS") {
            cin >> number_student;
            markSuspicious(number_student);
        }
        else if (command == "IMMORTAL") {
            cin >> number_student;
            markImmortal(number_student);
        }
        else if (command == "TOP-LIST") {
            printExpulsionList();
        }
        else if (command == "SCOUNT") {
            printExpulsionCount();
        }
        else if (command == "HELP") {
            printHelp();
        }
        else if (command == "EXIT") {
            cout << "Exiting the program..." << endl;
            break; // Выход из цикла
        }
        else {
            cout << "Incorrect" << endl; // Вывод сообщения об ошибке при некорректной команде
        }
    }

    return 0;
}
