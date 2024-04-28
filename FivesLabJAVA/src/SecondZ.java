import java.util.*;

// Класс для представления пары значений
class Pair<F, S> {
    private F first; // Первый элемент пары
    private final S second; // Второй элемент пары

    public Pair(F first, S second) {
        this.first = first;
        this.second = second;
    }

    public F getFirst() {
        return first;
    }

    public S getSecond() {
        return second;
    }

    public void setFirst(F first) {
        this.first = first;
    }

}

public class SecondZ {
    // Метод для распределения очереди посетителей на окна
    static void distributeQueue(int numWindows, Queue<Pair<Integer, String>> visitors) {
        // Создаем список пар, представляющий окна, и заполняем его парами (0, пустой список талонов)
        List<Pair<Integer, List<String>>> windows = new ArrayList<>(numWindows);
        for (int i = 0; i < numWindows; i++) {
            windows.add(new Pair<>(0, new ArrayList<>()));
        }

        // Сортируем окна по продолжительности обслуживания (по первому элементу пары)
        windows.sort(Comparator.comparingInt(Pair::getFirst));

        // Пока очередь посетителей не пуста
        while (!visitors.isEmpty()) {
            // Извлекаем текущего посетителя из очереди
            var currentVisitor = visitors.poll();

            // Находим окно с минимальной продолжительностью обслуживания
            var minWindow = Collections.min(windows, Comparator.comparingInt(Pair::getFirst));

            // Добавляем талон текущего посетителя в список талонов окна с минимальной продолжительностью
            minWindow.getSecond().add(currentVisitor.getSecond());

            // Увеличиваем продолжительность обслуживания этого окна на продолжительность текущего посетителя
            minWindow.setFirst(minWindow.getFirst() + currentVisitor.getFirst());
        }

        // Выводим информацию о каждом окне и списках талонов
        for (int i = 0; i < numWindows; ++i) {
            System.out.print("Окно " + (i + 1) + " (" + windows.get(i).getFirst() + " минут): ");
            for (var token : windows.get(i).getSecond()) {
                System.out.print(token + ", ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Запрос количества окон
        System.out.print("Введите кол-во окон: ");
        int numWindows = scanner.nextInt();

        // Создаем очередь посетителей
        Queue<Pair<Integer, String>> visitors = new LinkedList<>();

        // Запрос команд управления системой
        System.out.println("Введите команды (ENQUEUE <продолжительность посещения>, DISTRIBUTE для завершения):");
        while (true) {
            System.out.print(">>> ");
            String command = scanner.next();
            if (command.equals("ENQUEUE")) { // Если команда - добавление посетителя в очередь
                int duration = scanner.nextInt(); // Считываем продолжительность посещения
                String token = "T" + (visitors.size() + 1); // Генерируем номер талона
                visitors.add(new Pair<>(duration, token)); // Добавляем посетителя в очередь
                System.out.println(token); // Выводим номер талона
            } else if (command.equals("DISTRIBUTE")) { // Если команда - распределение посетителей по окнам
                distributeQueue(numWindows, visitors); // Вызываем метод распределения посетителей
                break; // Завершаем цикл
            } else { // Если введена неверная команда
                System.out.println("Invalid command"); // Выводим сообщение об ошибке
            }
        }
    }
}
