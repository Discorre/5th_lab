#ifndef TRANSITSYSTEM_H // Проверка на то, что заголовочный файл еще не был включен
#define TRANSITSYSTEM_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Перечисление для типов команд
enum class CommandType {
    CREATE_TRL,     // Создать троллейбус
    TRL_IN_STOP,    // Вывести троллейбусы на остановке
    STOPS_IN_TRL,   // Вывести остановки для троллейбуса
    TRLS,           // Вывести все троллейбусы
    HELP            // Вывести справку
};

class TransitSystem {
public:
    TransitSystem(); // Конструктор класса

    void executeCommands(); // Метод для выполнения команд

private:
    // Хранение соответствия троллейбусов и остановок, и наоборот
    unordered_map<string, vector<string>> trlStops;
    unordered_map<string, vector<string>> stopTrls;

    // Приватные методы для обработки каждой команды
    void createTrolleybus(const vector<string>& command);
    void trolleybusesInStop(const vector<string>& command);
    void stopsInTrolleybus(const vector<string>& command);
    void displayTrolleybuses();
    void displayHelp();
};

#endif // Завершение условного включения
