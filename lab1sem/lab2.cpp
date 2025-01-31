/* Лаба по проге №2(Программирование */
#include<iostream>
#include<math.h>
using namespace std;
//Заполнение матриц
void completion(int size1, int size2, double** matrix1, double** matrix2) 
{
  for (int i = 0; i < size1; i++)
  {
    for (int j = 0; j < size1; j++)
    {
      matrix1[i][j] = rand() / 1000 + (double)(rand() % 100) / 100;
    }
  }
  for (int i = 0; i < size2; i++)
  {
    for (int j = 0; j < size2; j++)
    {
      matrix2[i][j] = rand() / 1000 + (double)(rand() % 100) / 100;
    }
  }
}
//Вывод матриц
void print(int size1, int size2, double** matrix1, double** matrix2)
{
  for (int i = 0; i < size1; i++)
  {
    for (int j = 0; j < size1; j++)
    {
      cout << matrix1[i][j] << ' ';
    }
    cout << "\n";
  }
  cout << "\n\n";
  for (int i = 0; i < size2; i++)
  {
    for (int j = 0; j < size2; j++)
    {
      cout << matrix2[i][j] << ' ';
    }
    cout << "\n";
  }
  cout << "\n\n\n";
}
//Сортировка матриц
void sorting(int size, double** matrix)
{
  for (int i = 0; i < size; i++)
  {
    for (int k = 0; k < size; k++)
    {
      for (int j = 0; j < size - 1; j++)
      {
        if (matrix[j][i] < matrix[j + 1][i])
        {
          double v = matrix[j + 1][i];
          matrix[j + 1][i] = matrix[j][i];
          matrix[j][i] = v;
        }
      }
    }
  }
}

//Логрифм 
void log(double x, int size, double** matrix)
{
  double y, logarifm, logarifm5;
  y = matrix[0][0];
  logarifm = log10(y) / log10(x);
  logarifm5 = logarifm * 5;
  logarifm = 0;
  int d = 0;
  for (int i = 0; i < size; i++)
  {
    if (d == 1)
    {
      break;
    }
    for (int j = 0; j < size; j++)
    {
      logarifm += matrix[i][j];
      if (logarifm > logarifm5)
      {
        cout << "Индексы элемента: " << i + 1 << " " << j + 1 << "\n" << endl;
        d = 1;
        break;
      }
    }
  }
}
//Сравнение матриц (минимальный элемент)
double** min_element(int size1, int size2, double** matrix1, double** matrix2, int &size)
{
  double *arr1 = new double[size1];
  double *arr2 = new double[size2];

  for (int i = 0; i < size1; i++)
  {
    arr1[i] = matrix1[0][i];
  }
  for (int i = 0; i < size2; i++)
  {
    arr2[i] = matrix2[0][i];
  }

  for (int i = 0; i < size1; i++)
  {
    for (int j = 0; j < size1-1; j++)
    {
      if (arr1[j] > arr1[j + 1])
      {
        double x = arr1[j + 1];
        arr1[j + 1] = arr1[j];
        arr1[j] = x;
      }
    }
  }
  for (int i = 0; i < size2; i++)
  {
    for (int j = 0; j < size2-1; j++)
    {
      if (arr2[j] > arr2[j + 1])
      {
        double x = arr2[j + 1];
        arr2[j + 1] = arr2[j];
        arr2[j] = x;
      }
    }
  }

  if (arr1[0] < arr2[0])
  {
    delete[] arr1;
    delete[] arr2;
    size = size1;
    return matrix1;
  }
  else
  {
    delete[] arr1;
    delete[] arr2;
    size = size2;
    return matrix2;
  }
}
//Квадрат матрицы
void umnothenie(int size, double** matrix)
{
  //Объявление новой матрицы
  double** matrix_2 = new double* [size];
  for (int i = 0; i < size; i++)
  {
    matrix_2[i] = new double[size];
  }
  //Заполнение новой матрицы (умножение)
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      double sum = 0;
      for (int k = 0; k < size; k++)
      {
        sum += matrix[i][k] * matrix[k][j];
      }
      matrix_2[i][j] = sum;
    }
  }
  //Выведем полученную матрицу
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      cout << matrix_2[i][j] << " ";
    }
    cout << "\n";
  }
  //Освобождаем динамическую память
  for (int i = 0; i < size; i++)
  {
    delete[] matrix_2[i];
  }
  delete[] matrix_2;
}

int main()
{
  setlocale(LC_ALL, "RUS");
  srand(time(NULL));

  int size1, size2;
  cin >> size1 >> size2;
  cout << "Заданные матрицы" << endl;
  /*Объявление двумерных динамических массивов*/
  double** matrix1 = new double* [size1];
  for (int i = 0; i < size1; i++)
  {
    matrix1[i] = new double[size1];
  }


  double** matrix2 = new double* [size2];
  for (int i = 0; i < size2; i++)
  {
    matrix2[i] = new double[size2];
  }
  /*Заполнение матриц случайными вещественными числами*/

  completion(size1, size2, matrix1, matrix2);
  print(size1, size2, matrix1, matrix2);

  /*Сортировка элементов столбцов матриц в порядке убывания*/

  cout << "Задание 1. Сортировка." << endl;
  sorting(size1, matrix1);
  sorting(size2, matrix2);
  print(size1, size2, matrix1, matrix2);

  /*Логарифм*/
  cout << "Задание 2. Логарифм." << endl;

  cout << "Для матрицы (1).";
  cout << "Введите основание логарифма: ";
  double x1;
  cin >> x1;
  log(x1, size1, matrix1);

  cout << "Для матрицы (2).";
  cout << "Введите основание логарифма: ";
  double x2;
  cin >> x2;
  log(x2, size2, matrix2);

  /*Квадрат матрицы*/
  cout << "\n\n" << "Задание 3. Квадрат матрицы" << "\n" << endl;

  /*Определим нужную нам матрицу*/
  /*Расчитаем квадрат выбранной матрицы*/
  int size = 0;
  umnothenie(size, min_element(size1, size2, matrix1, matrix2, size));

  /*Очистка динамической памяти*/
  for (int i = 0; i < size1; i++)
  {
    delete[] matrix1[i];
  }
  delete[] matrix1;

  for (int i = 0; i < size2; i++)
  {
    delete[] matrix2[i];
  }
  delete[] matrix2;
}
