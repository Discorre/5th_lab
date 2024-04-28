import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

// Класс, представляющий ячейку склада
class Cell {
    String address; // Адрес ячейки
    Map<String, Integer> products; // Карта товаров и их количества в ячейке

    // Конструктор для создания новой ячейки
    public Cell(String addr) {
        address = addr;
        products = new HashMap<>(); // Инициализация карты товаров
    }

    // Метод для добавления товара в ячейку
    public void addProduct(String productName, int quantity) {
        products.put(productName, products.getOrDefault(productName, 0) + quantity); // Добавление товара в карту
        System.out.println("Добавлено " + quantity + " единиц товара " + productName + " в ячейку " + address + ".");
    }

    // Метод для удаления товара из ячейки
    public void removeProduct(String productName, int quantity) {
        if (products.containsKey(productName)) { // Проверка наличия товара в ячейке
            int currentQuantity = products.get(productName);
            if (currentQuantity >= quantity) { // Проверка достаточного количества товара для удаления
                products.put(productName, currentQuantity - quantity); // Удаление товара из карты
                if (products.get(productName) == 0) { // Если количество товара стало нулевым, удаляем его из карты
                    products.remove(productName);
                }
                System.out.println("Убрано " + quantity + " единиц товара " + productName + " из ячейки " + address + ".");
            } else {
                System.out.println("Невозможно убрать " + quantity + " единиц товара " + productName + " из ячейки " + address + ".");
            }
        } else {
            System.out.println("Невозможно убрать " + quantity + " единиц товара " + productName + " из ячейки " + address + ".");
        }
    }

    // Метод для вывода содержимого ячейки
    public void showContents() {
        if (!products.isEmpty()) { // Проверка наличия товаров в ячейке
            System.out.println("Содержимое ячейки " + address + ":");
            for (Map.Entry<String, Integer> entry : products.entrySet()) {
                System.out.println("- " + entry.getKey() + ": " + entry.getValue() + " шт.");
            }
        }
    }
}

// Класс, представляющий склад
class Warehouse {
    int zones; // Количество зон на складе
    int shelvesPerZone; // Количество полок в каждой зоне
    int sectionsPerShelf; // Количество секций на каждой полке
    int shelvesCapacity; // Вместимость каждой полки
    int totalCapacity; // Общая вместимость склада
    Map<String, Cell> cells; // Карта ячеек склада

    // Конструктор для создания нового склада с заданными параметрами
    public Warehouse(int z, int spz, int sps, int sc) {
        zones = z;
        shelvesPerZone = spz;
        sectionsPerShelf = sps;
        shelvesCapacity = sc;
        totalCapacity = zones * shelvesPerZone * sectionsPerShelf * shelvesCapacity; // Вычисление общей вместимости
        cells = new HashMap<>(); // Инициализация карты ячеек

        // Создание ячеек для каждой комбинации зоны, полки, секции и позиции на полке
        for (int zone = 1; zone <= zones; ++zone) {
            for (int shelf = 1; shelf <= shelvesPerZone; ++shelf) {
                for (int section = 1; section <= sectionsPerShelf; ++section) {
                    for (int shelfPosition = 1; shelfPosition <= shelvesCapacity; ++shelfPosition) {
                        String address = "" + (char) ('A' + zone - 1) + shelf + section + shelfPosition; // Генерация адреса
                        cells.put(address, new Cell(address)); // Добавление новой ячейки в карту
                    }
                }
            }
        }
    }

    // Метод для добавления товара в указанную ячейку
    public void addProduct(String productName, int quantity, String cellAddress) {
        Cell cell = cells.get(cellAddress); // Получение ячейки по адресу
        if (cell != null) {
            cell.addProduct(productName, quantity); // Добавление товара в ячейку
        } else {
            System.out.println("Ячейка не существует.");
        }
    }

    // Метод для удаления товара из указанной ячейки
    public void removeProduct(String productName, int quantity, String cellAddress) {
        Cell cell = cells.get(cellAddress); // Получение ячейки по адресу
        if (cell != null) {
            cell.removeProduct(productName, quantity); // Удаление товара из ячейки
        } else {
            System.out.println("Ячейка не существует.");
        }
    }

    // Метод для вывода информации о заполненных ячейках склада
    public void getInfo() {
        int totalFilledCapacity = 0; // Общее количество заполненных ячеек
        for (Cell cell : cells.values()) {
            if (!cell.products.isEmpty()) { // Проверка наличия товаров в ячейке
                totalFilledCapacity += cell.products.size(); // Увеличение счетчика заполненных ячеек
                cell.showContents(); // Вывод содержимого ячейки
            }
        }
        double filledPercentage = ((double) totalFilledCapacity / totalCapacity) * 100.0; // Вычисление процента заполненности
        System.out.println("Склад заполнен на " + filledPercentage + "%.");
    }

    // Метод для вывода списка пустых ячеек
    public void showEmptyCells() {
        System.out.println("Пустые ячейки:");
        for (Cell cell : cells.values()) {
            if (cell.products.isEmpty()) { // Проверка пустоты ячейки
                System.out.println(cell.address); // Вывод адреса пустой ячейки
            }
        }
    }
}

// Основной класс программы
public class FirstZ {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Warehouse warehouse = new Warehouse(2, 19, 4, 8); // Создание склада с заданными параметрами

        // Вывод инструкции по использованию программы
        System.out.println("Для добавления товара в ячейку используйте команду ADD <наименование товара> <количество> <адрес ячейки>.");
        System.out.println("Пример: ADD Апельсины 8 А1739");
        System.out.println("Для удаления товара из ячейки используйте команду REMOVE <наименование товара> <количество> <адрес ячейки>.");
        System.out.println("Пример: REMOVE Апельсины 3 А1739");
        System.out.println("Для получения информации о состоянии заполненных ячеек склада используйте команду INFO.");
        System.out.println("Для получения списка пустых ячеек используйте команду EMPTY.");
        System.out.println("Команда HELP - выводит инструкцию по вводу.");
        System.out.println("Команда EXIT - завершает программу.");

        // Цикл обработки команд пользователя
        while (true) {
            System.out.print("Введите команду: ");
            String command = scanner.nextLine();

            if (command.equals("EXIT")) { // Проверка команды на завершение программы
                break;
            } else if (command.equals("HELP")) { // Вывод справочной информации
                System.out.println("Для добавления товара в ячейку используйте команду ADD <наименование товара> <количество> <адрес ячейки>.");
                System.out.println("Пример: ADD Апельсины 8 А1739");
                System.out.println("Для удаления товара из ячейки используйте команду REMOVE <наименование товара> <количество> <адрес ячейки>.");
                System.out.println("Пример: REMOVE Апельсины 3 А1739");
                System.out.println("Для получения информации о состоянии заполненных ячеек склада используйте команду INFO.");
                System.out.println("Для получения списка пустых ячеек используйте команду EMPTY.");
                System.out.println("Команда HELP - выводит инструкцию по вводу.");
                System.out.println("Команда EXIT - завершает программу.");
            } else {
                if (command.startsWith("ADD")) { // Обработка команды добавления товара
                    String[] parts = command.split(" ");
                    if (parts.length == 4) {
                        String productName = parts[1];
                        int quantity = Integer.parseInt(parts[2]);
                        String cellAddress = parts[3];
                        warehouse.addProduct(productName, quantity, cellAddress); // Вызов метода добавления товара на склад
                    } else {
                        System.out.println("Некорректная команда.");
                    }
                } else if (command.startsWith("REMOVE")) { // Обработка команды удаления товара
                    String[] parts = command.split(" ");
                    if (parts.length == 4) {
                        String productName = parts[1];
                        int quantity = Integer.parseInt(parts[2]);
                        String cellAddress = parts[3];
                        warehouse.removeProduct(productName, quantity, cellAddress); // Вызов метода удаления товара со склада
                    } else {
                        System.out.println("Некорректная команда.");
                    }
                } else if (command.equals("INFO")) { // Обработка команды вывода информации о складе
                    warehouse.getInfo(); // Вызов метода вывода информации о складе
                } else if (command.equals("EMPTY")) { // Обработка команды вывода списка пустых ячеек
                    warehouse.showEmptyCells(); // Вызов метода вывода списка пустых ячеек
                } else {
                    System.out.println("Неизвестная команда.");
                }
            }
        }

        scanner.close();
    }
}
