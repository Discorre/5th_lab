import java.util.*;

public class SecondZ {
    // Метод для распределения очереди посетителей на окна
    private static void distributeQueue(int numWindows, Queue<Pair<Integer, String>> visitors) {
        // Создаем список окон, где каждое окно представлено парой <продолжительность обслуживания, список талонов>
        List<Pair<Integer, List<String>>> windows = new ArrayList<>();
        for (int i = 0; i < numWindows; i++) {
            windows.add(new Pair<>(0, new ArrayList<>()));
        }

        // Пока есть посетители в очереди
        while (!visitors.isEmpty()) {
            // Извлекаем следующего посетителя из очереди
            Pair<Integer, String> currentVisitor = visitors.poll();

            // Ищем окно с наименьшей очередью
            Pair<Integer, List<String>> minWindow = Collections.min(windows, Comparator.comparingInt(o -> o.first));

            // Добавляем посетителя к выбранному окну
            assert minWindow != null;
            minWindow.second.add(currentVisitor.second);

            // Увеличиваем продолжительность обслуживания окна на продолжительность посещения посетителя
            minWindow.first += currentVisitor.first;
        }

        // Выводим распределение посетителей на окна
        for (int i = 0; i < numWindows; i++) {
            System.out.print("Окно " + (i + 1) + " (" + windows.get(i).first + " минут): ");
            for (String token : windows.get(i).second) {
                System.out.print(token + ", ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Введите кол-во окон: ");
        int numWindows;
        while (true) {
            try {
                numWindows = Integer.parseInt(scanner.nextLine());
                if (numWindows > 0) {
                    break;
                } else {
                    System.out.print("Некорректный ввод. Пожалуйста, введите положительное целое число: ");
                }
            } catch (NumberFormatException e) {
                System.out.print("Некорректный ввод. Пожалуйста, введите положительное целое число: ");
            }
        }

        Queue<Pair<Integer, String>> visitors = new LinkedList<>();

        System.out.println("Введите команды (ENQUEUE <продолжительность посещения>, DISTRIBUTE для завершения):");
        while (true) {
            System.out.print(">>> ");
            String command = scanner.next();
            if (command.equals("ENQUEUE")) {
                int duration;
                try {
                    duration = Integer.parseInt(scanner.next());
                    if (duration <= 0) {
                        System.out.print("Некорректная продолжительность посещения. Пожалуйста, введите положительное целое число: ");
                        continue;
                    }
                } catch (NumberFormatException e) {
                    System.out.print("Некорректная продолжительность посещения. Пожалуйста, введите положительное целое число: ");
                    continue;
                }
                String token = "T" + visitors.size() + 1; // Генерация уникального талона
                visitors.add(new Pair<>(duration, token)); // Добавление посетителя в очередь
                System.out.println(token); // Вывод номера талона
            } else if (command.equals("DISTRIBUTE")) {
                distributeQueue(numWindows, visitors); // Вызов метода для распределения посетителей по окнам
                break;
            } else {
                System.out.println("Некорректный синтаксис"); // Вывод сообщения об ошибке
            }
        }

        scanner.close();
    }

    static class Pair<U, V> {
        public U first;
        public final V second;

        public Pair(U first, V second) {
            this.first = first;
            this.second = second;
        }
    }
}
