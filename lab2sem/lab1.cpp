/* Лаба №1 двумерные массивы(2 сем 1 лаба) */
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void transponirovanie(double** mass, int n, int m, double** Tmass)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      Tmass[j][i] = mass[i][j];
}
void umnothenie(double** pr_mass, double** mass1, double** mass2, int n1, int m1, int n2, int m2)
{
  for (int i = 0; i < n1; i++)
  {
    double sum;
    for (int j = 0; j < m2; j++)
    {
      sum = 0;
      for (int k = 0; k < m1; k++)
      {
        sum += mass1[i][k] * mass2[k][j];
      }
      pr_mass[i][j] = sum;
    }
  }
}
void umn_na_k(double** mass_kA, double** massA, double k, int nA, int mA)
{
  for (int i = 0; i < nA; i++)
    for (int j = 0; j < mA; j++)
      mass_kA[i][j] = k * massA[i][j];
}
void summa(double** sum, double** mass1, double** mass2, int n, int m)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++)
      sum[i][j] = mass1[i][j] + mass2[i][j];
}
int main()
{
  setlocale(LC_ALL, "Rus");
  system("chcp 1251 > NULL");

  cout << "Данная программа выполняет расчет выражения с матрицами вида: k*A+B*C^T ." << endl;
  int nA = 1, mA = 1, nB = 1, mB = 1, nC = 1, mC = 1;
  double k = 1;
  string Completion;
  cout << "Как вы хотите задать размеры массивов и число k? Если взять данные из файла, то введите file, если вручную, то hands: ";
  cin >> Completion;
  if (Completion == "file")
  {
    cout << "Введите название файла из которого хотите взять размеры матриц: ";
    string Name;
    cin >> Name;
    ifstream fcout;
    fcout.open(Name);
    if (!fcout.is_open())
    {
      cout << "Файл не удалось открыть.";
      return 0;
    }
    else
    {
      fcout >> nA >> mA >> nB >> mB >> nC >> mC >> k;
      if ((mB != mC) || (nA != nB) || (mA != nC))
      {
        cout << "Ошибка! Заданные операции с такими матрицами совершить не получится.";
        return 0;
      }
    }
    fcout.close();
  }
  else if (Completion == "hands")
  {
    cout << "Введите размерности матриц и число k." << endl;
    cout << "Матрица А: ";
    cin >> nA >> mA;
    cout << "Матрица В: ";
    cin >> nB >> mB;
    cout << "Матрица С: ";
    cin >> nC >> mC;
    if ((mB != mC) || (nA != nB) || (mA != nC))
    {
      cout << "Ошибка! Заданные операции с такими матрицами совершить не получится.";
      return 0;
    }
    cout << "Число k: ";
    cin >> k;
    cout << endl;
  }
  else
  {
    cout << "Ошибка! Такого варианта нет.";
    return 0;
  }
  //Создание двумерных динамических массивов
  double** massA = new double* [nA];
  for (int i = 0; i < nA; i++)
    massA[i] = new double[mA];
  double** massB = new double* [nB];
  for (int i = 0; i < nB; i++)
    massB[i] = new double[mB];
  double** massC = new double* [nC];
  for (int i = 0; i < nC; i++)
    massC[i] = new double[mC];


  cout << "Если хотите взять данные для матриц из файла введите [file], а если хотите ввести вручную, то [hands]" << endl;
  string completion;
  cin >> completion;
  if (completion == "file")
  {
    cout << "Введите название файла из которого хотите взять данные для матриц: ";
    string Name;
    cin >> Name;
    ifstream fcout;
    fcout.open(Name, ios_base::app);
    if (!fcout.is_open())
    {
      cout << "Файл не удалось открыть.";
      return 0;
    }
    else
    {
      int s;
      for (int i = 0; i < 7; i++)
        fcout >> s;
      for (int i = 0; i < nA; i++)
        for (int j = 0; j < mA; j++)
          fcout >> massA[i][j];
      for (int i = 0; i < nB; i++)
        for (int j = 0; j < mB; j++)
          fcout >> massB[i][j];
      for (int i = 0; i < nC; i++)
        for (int j = 0; j < mC; j++)
          fcout >> massC[i][j];
    }
    fcout.close();
  }
  else if (completion == "hands")
  {
    //Заполнение массивов вручную
    cout << "Заполните массивы значениями." << endl;
    cout << "Массив А: " << endl;
    for (int i = 0; i < nA; i++)
      for (int j = 0; j < mA; j++)
        cin >> massA[i][j];
    cout << "Массив B: " << endl;
    for (int i = 0; i < nB; i++)
      for (int j = 0; j < mB; j++)
        cin >> massB[i][j];
    cout << "Массив C: " << endl;
    for (int i = 0; i < nC; i++)
      for (int j = 0; j < mC; j++)
        cin >> massC[i][j];
  }
  else
  {
    cout << "Ошибка! Такого способа нет.";
    return 0;
  }

  //Выполнение арифметических действий над матрицами
  //Транспонирование
  double** Tmass = new double* [mC];
  for (int i = 0; i < mC; i++)
    Tmass[i] = new double[nC];
  transponirovanie(massC, nC, mC, Tmass);

  //Произведение массивов B и транспонированного С
  double** pr_mass = new double* [nB];
  for (int i = 0; i < nB; i++)
    pr_mass[i] = new double[nC];
  if (mB != mC)
    cout << "Ошибка! Такие матрицы перемножить нельзя.";
  else
    umnothenie(pr_mass, massB, Tmass, nB, mB, mC, nC);

  //Умножение матрицы А на число k
  double** mass_kA = new double* [nA];
  for (int i = 0; i < nA; i++)
    mass_kA[i] = new double[mA];
  umn_na_k(mass_kA, massA, k, nA, mA);
  

  //Сумма матриц
  double** sum = new double* [nA];
  for (int i = 0; i < nA; i++)
    sum[i] = new double[mA];
  summa(sum, mass_kA, pr_mass, nA, mA);
  ///////////////////////////////////////////////
  cout << "Ввести данные матрицы и последущие операции с ними в файл или вывести их в консоль? Введите 1, если в файл и 2, если в консоль." << endl;
  int x;
  cin >> x;
  if (x == 1)
  {
    cout << "Введите название файла, в котором вы хотите сохранить ваши матрицы: ";
    string name;
    cin >> name;
    ofstream fcin;
    fcin.open(name, ios_base::app);
    if (!fcin.is_open())
    {
      cout << "Файл не удалось открыть.";
      return 0;
    }
    else
    {
      fcin << nA << " " << mA << "   " << nB << " " << mB << "   " << nC << " " << mC << "   " << k << endl << endl;
      for (int i = 0; i < nA; i++)
      {
        for (int j = 0; j < mA; j++)
          fcin << massA[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      for (int i = 0; i < nB; i++)
      {
        for (int j = 0; j < mB; j++)
          fcin << massB[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      for (int i = 0; i < nC; i++)
      {
        for (int j = 0; j < mC; j++)
          fcin << massC[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      for (int i = 0; i < mC; i++)
      {
        for (int j = 0; j < nC; j++)
          fcin << Tmass[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      for (int i = 0; i < nA; i++)
      {
        for (int j = 0; j < mA; j++)
          fcin << mass_kA[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      for (int i = 0; i < nB; i++)
      {
        for (int j = 0; j < nC; j++)
          fcin << pr_mass[i][j] << " ";
        fcin << endl;
      }
      fcin << endl;
      fcin << "Ответ: " << endl;
      for (int i = 0; i < nA; i++)
      {
        for (int j = 0; j < mA; j++)
          fcin << sum[i][j] << " ";
        fcin << endl;
      }
    }
    fcin.close();
  }
  else if (x == 2)
  {
    cout << endl;
    cout << nA << " " << mA << "   " << nB << " " << mB << "   " << nC << " " << mC << "   " << k << endl << endl;
    for (int i = 0; i < nA; i++)
    {
      for (int j = 0; j < mA; j++)
        cout << massA[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    for (int i = 0; i < nB; i++)
    {
      for (int j = 0; j < mB; j++)
        cout << massB[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    for (int i = 0; i < nC; i++)
    {
      for (int j = 0; j < mC; j++)
        cout << massC[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    for (int i = 0; i < mC; i++)
    {
      for (int j = 0; j < nC; j++)
        cout << Tmass[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    for (int i = 0; i < nA; i++)
    {
      for (int j = 0; j < mA; j++)
        cout << mass_kA[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    for (int i = 0; i < nB; i++)
    {
      for (int j = 0; j < nC; j++)
        cout << pr_mass[i][j] << " ";
      cout << endl;
    }
    cout << endl;
    cout << "Ответ: " << endl;
    for (int i = 0; i < nA; i++)
    {
      for (int j = 0; j < mA; j++)
        cout << sum[i][j] << " ";
      cout << endl;
    }
  }
  else
    cout << "Допущена ошибка в выборе варианта действий.";

  //Освобождаем выделенную память
  for (int i = 0; i < nA; i++)
    delete[] sum[i];
  delete[] sum;
  for (int i = 0; i < nA; i++)
    delete[] mass_kA[i];
  delete[] mass_kA;
  for (int i = 0; i < nB; i++)
    delete[] pr_mass[i];
  delete[] pr_mass;
  for (int i = 0; i < nC; i++)
    delete[] Tmass[i];
  delete[] Tmass;
  for (int i = 0; i < nA; i++)
    delete[] massA[i];
  delete[] massA;
  for (int i = 0; i < nB; i++)
    delete[] massB[i];
  delete[] massB;
  for (int i = 0; i < nC; i++)
    delete[] massC[i];
  delete[] massC;
}