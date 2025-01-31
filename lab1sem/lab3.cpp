/* Лаба по проге №3(программирование) */
#include <iostream>
#include<string>
using namespace std;
struct Books {
  string surname;
  string book;
  unsigned int number = 0;
};
int main()
{
  system("chcp 1251 > text");
  cout << "Введите количество книг в списке: ";
  int size;
  cin >> size;
  cout << "Введите список по строчно: " << endl;
  Books* arr = new Books[size];
  for (int i = 0; i < size; i++)
  {
    cin >> arr[i].surname >> arr[i].book >> arr[i].number;
  }
  cout << "\n\n\n";
  int X = 1;
  while (X != 0)
  {
    cout << "Выберете необходимое вам действие." << endl;
    cout << "Завершить работу - 0\nВывести список - 1\nУстановка новой книги - 2\nПолучение нужной книги - 3\n";
    cout << "Поиск строк по заданным полям - 4\nОбмен значений соответствующих полей - 5\n";
    cout << "Сортировка названий книг по возрастанию - 6\nВывод одного или несколько элементов массива структур - 7\n";
    cin >> X;
    if (X == 0) //Завершение программы
    {
      cout << "Работа закончена." << endl;
      return 0;
    }
    else if (X == 1) // Вывод списка
    {
      for (int i = 0; i < size; i++)
      {
        cout << arr[i].surname << " " << arr[i].book << " " << arr[i].number << endl;
      }
      cout << endl;
    }
    else if (X == 2) // Установка новой книги
    {
      int index, k = 0;
      while (k == 0)
      {
        cout << "Введите индекс элемента: ";
        cin >> index;
        k = 1;
        if ((index < 0) || (index > size - 1))
        {
          cout << "Введен несуществующий индекс." << endl;
          k = 0;
        }
      }
      cout << endl;
      cout << "Введите новую фамилию: ";
      cin >> arr[index].surname;
      cout << endl;
      cout << "Введите новое название книги: ";
      cin >> arr[index].book;
      cout << "Введите новый номер книги: ";
      cin >> arr[index].number;
      cout << "Замена прошла успешно." << endl << endl;
    }
    else if (X == 3) // Получение нужной книги 
    {
      int index, k = 0;
      cout << "Введите индекс элемента: ";
      while (k == 0)
      {
        cin >> index;
        k = 1;
        if ((index < 0) || (index > size - 1))
        {
          cout << "Введен несуществующий индекс. Попробуйте снова: ";
          k = 0;
        }
      }
      cout << endl;
      cout << "Ваш запрос: " << arr[index].surname << " " << arr[index].book << " " << arr[index].number << endl << endl;
    }
    else if (X == 4) // Поиск необходимой строки по одному из полей
    {
      int field, number1, k = 1;
      string surname1, book1;
      cout << "Введите номер поля, по которому будет выполняться поиск: ";
      cin >> field;
      if (field == 1) { // Поле фамилии
        cout << "Введите значение поля, по которому будет выполнятся поиск: ";
        cin >> surname1;
        for (int i = 0; i < size; i++) {
          if (surname1 == arr[i].surname)
          {
            cout << "Результат поиска: " << arr[i].number << " " << arr[i].surname << " " << arr[i].book << endl;
            k = 0;
            break;
          }
        }
        if (k == 1)
        {
          cout << "Эелемент не найден." << endl;
        }      
      }
      else if (field == 2) { // Поле названий книг
        cout << "Введите значение поля, по которому будет выполнятся поиск: ";
        cin >> book1;
        for (int i = 0; i < size; i++) {
          if (book1 == arr[i].book)
          {
            cout << "Результат поиска: " << arr[i].number << " " << arr[i].surname << " " << arr[i].book << endl;
            k = 0;
            break;
          }
        }
        if (k == 1)
        {
          cout << "Эелемент не найден." << endl;
        }    
      }
      else if (field == 3) { // Поле для номеров книг
        cout << "Введите значение поля, по которому будет выполнятся поиск: ";
        cin >> number1;
        for (int i = 0; i < size; i++) {
          if (number1 == arr[i].number)
          {
            cout << "Результат поиска: " << " " << arr[i].surname << " " << arr[i].book << " " << arr[i].number << endl;
            k = 0;
            break;
          }

        }
        if (k == 1)
        {
          cout << "Эелемент не найден." << endl;
        }
      }
      else {
        cout << "Такого поля нет." << endl;
      }
      cout << endl;
    }
    else if (X == 5) //Обмен значений соответствующих полей
    {
      int index1 = 0, index2 = 0, TF = 0;
      while (TF == 0)
      {
        cout << "Введите индекс первого элемента: ";
        cin >> index1;
        TF = 1;
        if ((index1 < 0) || (index1 > size - 1))
        {
          cout << "Ошибка: индекc не может быть меньше 0 или больше " << size << " " << endl;
          TF = 0;
        }
      }
      while (TF == 1)
      {
        cout << "Введите индекс второго элемента: ";
        cin >> index2;
        TF = 2;
        if ((index2 < 0) || (index2 > size - 1))
        {
          cout << "Ошибка: индекc не может быть меньше 0 или больше " << size << " " << endl;
          TF = 1;
        }
        if (index1 == index2)
        {
          cout << "Ошибка: индексы не должны совпадать!" << endl;
          TF = 1;
        }
      }
      // Обмен значений
      Books temp = arr[index1];
      arr[index1] = arr[index2];
      arr[index2] = temp;
      cout << "Замена прошла успешна." << endl << endl;
    }
    else if (X == 6) { // Сортировка названий книг по возрастанию
      for (int i = 0; i < size - 1; i++)
      {
        if (arr[i].book > arr[i + 1].book)
        {
          Books temp = arr[i];
          arr[i] = arr[i + 1];
          arr[i + 1] = temp;
          i = -1;
        }
      }
      cout << "Сортировка книг по возрастанию проведена успешно." << endl << endl;
    }
    else if (X == 7) { //Вывод одного или несколько элементов массива структур
      int k = 0, index1, index2;
      while (k == 0)
      {
        cout << "Введите 2 индекса, которые будут задавать диапазон необходимых полей: ";
        cin >> index1 >> index2;
        k = 1;
        if ((index1 > index2) || (index1 < 0) || (index2 > size - 1)) {
          cout << "Неправильно введен диапазон" << endl;
          k = 0;
        }
      }
      cout << "Запрос выполнен: " << endl;
      for (int i = index1; i <= index2; i++)
      {
        cout << arr[i].surname << " " << arr[i].book << " " << arr[i].number << endl;
      }
    }
    else { // Завершение работы
      cout << "Выбрано несуществующие действие." << endl;
    }
    cout << endl;
  }
  delete[] arr;
}