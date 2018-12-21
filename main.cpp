//---------------------------------------------------------------------------
#pragma hdrstop

#include <conio.h>
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;
//---------------------------------------------------------------------------
int m; // Размер хеш-таблицы
int table[100]; // Хеш-таблица
int n; // Размер массива чисел
int a[100]; // Массив чисел
bool overflow; // Равна true, если было переполнение таблицы
int collisions; // Количество коллизий
// Вычисляет хеш-функцию
int HashF(int num) {
    return num % m;
}

// Создает хеш-таблицу методом линейных проб
void CreateTable1() {
    int i;
    for (i = 0; i < m; i++) // Очищаем хэш-таблицу
        table[i] = 0;
    collisions = 0;
    int h, h0, g;
    for (i = 0; i < n; i++) {
        h = HashF(a[i]);
        h0 = h;
        g = 1;
        while (1) {
            if (table[h] == a[i]) // Если число повторяется
                break;
            if (table[h] == 0) { // Если нашли пустое место в хэш-таблице
                table[h] = a[i];
                break;
            }
            if (g >= m) { // Если переполнение
                overflow = true;
                return;
            }
            collisions++;
            h = h0 + g;
            if (h >= m)
                h -= m;
            g++;
        }
    }
    overflow = false;
}

// Создает хеш-таблицу методом квадратичных проб
void CreateTable2() {
    int i;
    for (i = 0; i < m; i++) // Очищаем хэш-таблицу
        table[i] = 0;
    collisions = 0;
    int h, d;
    for (i = 0; i < n; i++) {
        h = HashF(a[i]);
        d = 1;
        while (1) {
            if (table[h] == a[i]) // Если число повторяется
                break;
            if (table[h] == 0) { // Если нашли пустое место в хэш-таблице
                table[h] = a[i];
                break;
            }
            if (d >= m) { // Если переполнение
                overflow = true;
                return;
            }
            collisions++;
            h += d;
            if (h >= m)
                h -= m;
            d += 2;
        }
    }
    overflow = false;
}

// Выводит хеш-таблицу на экран
void ShowTable() {
    int s = 0;
    if (m > 0) {
        printf("------------------------\n");
        printf("| Cell number | Number |\n");
        printf("------------------------\n");
        for (int i = 0; i < m; i++) {
            s++;
            if (table[i] != 0) {

                printf("|%2d           | %2d     |\n", s, table[i]);
            } else
                printf("   | ");
            printf("------------------------\n");
        }
        cout << endl;
        printf("-----------------------------------------------------------------------\n");
    }
    if (!overflow)
        printf("\nThere was no table overflow\n");
    else
        printf("\nAn overflow occurred in the table\n");
    printf("\nNumber of collisions: \n");
    cout << collisions << endl;
}

// Ищет число в хеш-таблице, построенной методом линейных проб
bool Search1(int num) {
    int h, h0, g;
    h = HashF(num);
    h0 = h;
    g = 1;
    while (1) {
        if (table[h] == num) // Если число найдено
            return true;
        if (g >= m) // Если переполнение
            return false;
        h = h0 + g;
        if (h >= m)
            h -= m;
        g++;
    }
}

// Ищет число в хеш-таблице, построенной методом квадратичных проб
bool Search2(int num) {
    int h, d;
    h = HashF(num);
    d = 1;
    while (1) {
        if (table[h] == num) // Если число найдено
            return true;
        if (d >= m) // Если переполнение
            return false;
        h += d;
        if (h >= m)
            h -= m;
        d += 2;
    }
}

#pragma argsused

int main(int argc, char *argv[]) {
    printf("\nEnter the size of the hash table: \n");
    cin >> m;
    if (m < 1) {
        printf("\nEnter a number greater than 0!\n");
        system("PAUSE");
        return 0;
    }
    printf("\nEnter the number of source numbers: \n");
    cin >> n;
    if (n < 1) {
        printf("\nEnter a number greater than 0!\n");
        system("PAUSE");
        return 0;
    }
    int num; // Число для поиска

//    rand();
    int i;
    for (i = 0; i < n; i++) // Заполняем массив чисел
        a[i] = rand() % n + 1;

    printf("\nLinear sampling method:\n");
    CreateTable1();
    ShowTable();
    printf("\nEnter a number to search: \n");
    cin >> num;
    if (Search1(num))
        printf("\nThe number of found\n");
    else
        printf("\nThe number is not found\n");

    printf("\nQuadratic sample method:\n");
    CreateTable2();
    ShowTable();
    printf("\nEnter a number to search: \n");
    cin >> num;
    if (Search2(num))
        printf("\nThe number of found\n");
    else
        printf("\nThe number is not found\n");
    system("PAUSE");
    return 0;
}
//---------------------------------------------------------------------------