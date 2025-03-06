#include <iostream>
#include <clocale>

using namespace std;

    // a) Функция для проверки принадлежности точки окружности
    bool isPointInCircle(double x, double y, double R) {
        return ((x * x + y * y) <= (R * R));
    }

    // b) Перегруженные функции belong с переменным числом параметров

    // Функция belong для 1 точки (3 параметра: R, x, y)
    int belong(double R, double x1, double y1) {
        int count = 0;
        if (isPointInCircle(x1, y1, R)) {
            count++;
        }
        return count;
    }

    // Функция belong для 3 точек (9 параметров: R, x1, y1, x2, y2, x3, y3)
    int belong(double R, double x1, double y1, double x2, double y2, double x3, double y3) 
    {
        int count = 0;
        if (isPointInCircle(x1, y1, R)) {
            count++;
        }
        if (isPointInCircle(x2, y2, R)) {
            count++;
        }
        if (isPointInCircle(x3, y3, R)) {
            count++;
        }
        return count;
    }

    // Функция belong для 5 точек (11 параметров: R, x1, y1, x2, y2, x3, y3, x4, y4,
    // x5, y5)
    int belong(double R, double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, double x5, double y5) 
    {
        int count = 0;
        if (isPointInCircle(x1, y1, R)) {
            count++;
        }
        if (isPointInCircle(x2, y2, R)) {
            count++;
        }
        if (isPointInCircle(x3, y3, R)) {
            count++;
        }
        if (isPointInCircle(x4, y4, R)) {
            count++;
        }
        if (isPointInCircle(x5, y5, R)) {
            count++;
        }
        return count;
    }

    int main() {
        setlocale(LC_ALL, "Rus");
        double R;

        // Получение радиуса от пользователя
        cout << "Введите радиус окружности: ";
        cin >> R;

        // Вызов функции belong с 1 точкой
        double x1, y1;
        cout << "Введите координаты первой точки (x; y): ";
        cin >> x1 >> y1;
        int count1 = belong(R, x1, y1);
        cout << "Пример 1: " << count1 << " точек (из 1) принадлежат окружности." << endl;

        // Вызов функции belong с 3 точками
        double x2, y2, x3, y3;
        cout << "Введите координаты трех точек (x; y) (x; y) (x; y): ";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        int count2 = belong(R, x1, y1, x2, y2, x3, y3);
        cout << "Пример 2: " << count2 << " точек (из 3) принадлежат окружности." << endl;

        // Вызов функции belong с 5 точками
        double x4, y4, x5, y5;
        cout << "Введите координаты пяти точек (x; y) (x; y) (x; y) (x; y) (x; y): ";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> x5 >> y5;
        int count3 = belong(R, x1, y1, x2, y2, x3, y3, x4, y4, x5, y5);
        cout << "Пример 3: " << count3 << " точек (из 5) принадлежат окружности." << endl;

        return 0;
    }




    