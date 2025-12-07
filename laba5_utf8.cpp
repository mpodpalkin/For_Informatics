#include <iostream>
#include <locale>
#include <fstream>
#include <iomanip>
using namespace std;


const unsigned N = 50;

void Inp(float A[N][N], unsigned t, string name) {
    ifstream f(name);
    if (!f.is_open()) {
        cout << "Не удалось открыть файл для чтения" << endl;
        exit(1);
    }
    else {
        char ch;

        for (unsigned i = 0; i < t; i++) {
            f >> skipws;
            for (unsigned j = 0; j < t; j++)
            {
                f >> A[i][j];
            }
            f >> noskipws;
            while (1) {
                f >> ch;
                if (ch == '\n' || f.eof()) {
                    break;
                }
            }
        }
    }
    f.close();
}

void Calc(unsigned* t, string s) {
    ifstream f(s);

    if (!f.is_open()) {
        cout << "Не удалось открыть файл для чтения." << endl;
        exit(1);
    }

    // Первый проход: Подсчет строк, чисел и минимального количества чисел в строке
    f >> noskipws; // Отключаем автоматический пропуск пробелов

    int total_rows = 0;
    int min_numbers_in_a_row = N;
    char ch;
    bool line_has_numbers = false; // Флаг: встречались ли числа в текущей строке
    int current_numbers_in_line = 0; // Счётчик чисел в текущей строке

    while (f >> ch) {
        if (ch == '\n') {
            // Конец строки
            if (line_has_numbers) {
                total_rows++;
                // Обновляем минимум
                min_numbers_in_a_row = min(min_numbers_in_a_row, current_numbers_in_line);
                current_numbers_in_line = 0; // Сброс счётчика для новой строки
                line_has_numbers = false;
                if (min_numbers_in_a_row < total_rows)
                    break;
            }
            else
                break;
            continue;
        }

        if (ch != ' ' && ch != '\t') {
            f.unget(); // Возвращаем символ 'ch' обратно в поток

            float num;
            f >> skipws; // Включаем пропуск пробелов
            if (f >> num) {
                current_numbers_in_line++; // Увеличиваем счётчик для текущей строки
                line_has_numbers = true; // Отмечаем, что в строке было число
            }
            f >> noskipws; // Снова отключаем
        }
    }

    // Проверяем последнюю строку
    if (line_has_numbers) {
        total_rows++;
        min_numbers_in_a_row = min(min_numbers_in_a_row, current_numbers_in_line);
    }

    f.close();


    if (total_rows == 0) {
        cout << "Некорректный файл." << endl;
        exit(1); // Хотя бы одна строка пуста, невозможно заполнить квадрат
    }


    // Итоговый размер - минимум из всех трёх ограничений
    *t = min({ total_rows, min_numbers_in_a_row });

}


void Process(float A[N][N], float *res, unsigned t) {
    for (unsigned i = 0; i < t; i++) {
        unsigned k = (i < t - 1 - i ? i : t - 1 - i);
        unsigned left = k;
        unsigned right = t - 1 - k;

        for (unsigned j = left; j <= right; j++) {
            *res += A[i][j];
        }
    }
}

void Out2(ofstream* outputFile, float g[N], unsigned t) {
    unsigned i;
    for (i = 0; i < t; i++) {
        *outputFile << setprecision(6) << fixed << setw(15) << g[i] << " ";
    }
    *outputFile << '\n';
}


void Out1(ofstream* outputFile, float tmp[N][N], unsigned t) {
    unsigned i;
    for (i = 0; i < t; i++) {
        Out2(outputFile, tmp[i], t);
    }
}

void Out3(ofstream* outputFile, float res) {
    *outputFile << "Результат сложения элементов матрицы: " << setprecision(6) << fixed << setw(15) << res;
}



int main()
{
    float A[N][N];
    unsigned t = 0;
    float res = 0;
    string s = "input3_1.txt";

    ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        cerr << "Ошибка открытия файла!" << endl;
        return 1;
    }

    setlocale(LC_ALL, "Russian");
    outputFile << "Лабораторная работа #5" << endl;
    outputFile << "ФИО: Подпалкин Михаил Романович" << endl;
    outputFile << "Номер группы: 5352" << endl << endl;

    Calc(&t, s);
    Inp(A,t, s);
    Out1(&outputFile, A, t);
    Process(A,&res, t);
    Out3(&outputFile, res);

    outputFile.close();

    return 0;
}