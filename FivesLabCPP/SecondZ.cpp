//#include <iostream>
//#include <queue>
//#include <vector>
//#include <algorithm>
//#include <string>
//#include <windows.h>
//
//using namespace std;
//
//// Функция для распределения очереди посетителей на окна
//static void distributeQueue(int numWindows, queue<pair<int, string>>& visitors) {
//    // Создаем вектор окон, где каждое окно представлено парой <продолжительность обслуживания, список талонов>
//    vector<pair<int, vector<string>>> windows(numWindows);
//
//    // Сортируем окна по возрастанию продолжительности обслуживания
//    sort(windows.begin(), windows.end());
//
//    // Пока есть посетители в очереди
//    while (!visitors.empty()) {
//        // Извлекаем следующего посетителя из очереди
//        auto currentVisitor = visitors.front();
//        visitors.pop();
//
//        // Ищем окно с наименьшей очередью
//        auto minWindow = min_element(windows.begin(), windows.end());
//
//        // Добавляем посетителя к выбранному окну
//        minWindow->second.push_back(currentVisitor.second);
//
//        // Увеличиваем продолжительность обслуживания окна на продолжительность посещения посетителя
//        minWindow->first += currentVisitor.first;
//    }
//
//    // Выводим распределение посетителей на окна
//    for (int i = 0; i < numWindows; ++i) {
//        cout << "Окно " << i + 1 << " (" << windows[i].first << " минут): ";
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
//    int numWindows; // Переменная для хранения количества окон
//    cout << "Введите кол-во окон: ";
//    while (!(cin >> numWindows) || numWindows <= 0) { // Проверка на корректность ввода количества окон
//        cout << "Некорректный ввод. Пожалуйста, введите положительное целое число: ";
//    }
//
//    queue<pair<int, string>> visitors; // Очередь посетителей, представленных парой <продолжительность посещения, талон>
//
//    string command; // Переменная для хранения команды пользователя
//    cout << "Введите команды (ENQUEUE <продолжительность посещения>, DISTRIBUTE для завершения):" << endl;
//    while (true) { // Бесконечный цикл для обработки команд
//        cout << ">>> ";
//        cin >> command; // Ввод команды с клавиатуры
//        if (command == "ENQUEUE") { // Если команда ENQUEUE
//            int duration;
//            if (!(cin >> duration) || duration <= 0) { // Проверка на корректность ввода продолжительности посещения
//                cout << "Некорректная продолжительность посещения. Пожалуйста, введите положительное целое число: ";
//                continue;
//            }
//            static int tokenCounter = 1;
//            string token = "T" + to_string(tokenCounter++); // Генерация уникального талона
//            visitors.push({ duration, token }); // Добавление посетителя в очередь
//            cout << token << endl; // Вывод номера талона
//        }
//        else if (command == "DISTRIBUTE") { // Если команда DISTRIBUTE
//            distributeQueue(numWindows, visitors); // Вызов функции для распределения посетителей по окнам
//            break; // Завершение цикла
//        }
//        else { // Если команда не распознана
//            cout << "Некорректный синтаксис" << endl; // Вывод сообщения об ошибке
//        }
//    }
//
//    return 0;
//}