/* Лаба по проге №1(Программирование) */

#include <iostream>
#include<math.h>
#include<iomanip>
using namespace std;
int main()
{
  setlocale(LC_ALL, "Rus");
  double X[11], G[11], S = 0.8, el1, sum = 0;

  //1. Заполнение массива
  cin >> el1;

  for (int i = 0; i < 11; i++)
  {
    X[i] = el1 + S * i;
  }

  //2. Расчёт заданной функции (сложение)
  for (int j = 0; j < 11; j++)
  {
    sum += X[j];
  }
  cout << "Сумма всех элементов массива равна: " << scientific << setprecision(3) <<  sum << endl;

  //3. Расчёт элементов массива по формуле
  for (int k = 0; k < 11; k++)
  {
    if (X[k] < 0)
    {
      G[k] = 5 * pow(X[k], 2) + 3;
    }
    else if ((X[k] >= 0) && (X[k] <= 20))
    {
      G[k] = (X[k] - 5) / (X[k] - 1);
    }
    else
    {
      G[k] = X[k] / 6;
    }
  }
  //Округление чисел в массиве
  for (int r = 0; r < 11; r++)
  {
    G[r] = (round(G[r] * 1000)) / 1000;
  }
  for (int t = 0; t < 11; t++)
  {
    cout << fixed << "y" << t + 1 << "   " << G[t] << endl;
  }
  system("pause");
}
