#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <algorithm>

using namespace std;

class Matrix
{
private:
    int **Item;
    int Row;
    int Col;

public:
    Matrix();
    Matrix(int r, int c, int low, int hight);
    ~Matrix()
    {
        for(int i = 0; i < Row; i++)
        {
            delete[] Item[i];
        }

        delete[] Item;
    }

    void Out();
    void SaveMatrixToFile(char* fileName);
    void SaveMatrixToFile(char* fileName, int maxElement, int minElement, int range, int counter);
    void OisSaveMatrixToFile(char* fileName);
    void SumElementsRow();
    int CalculateMaxElement();
    int CalculateMinElement();
    int CalculateRangeInShadedArea(int maxElement, int minElement);
    int CountElementAboveThreshold(int range, int minElement);
    void RemoveRowWithElement(int minElement);
    int* CreateShadedAreaArray(int &size);
    void SortShadedAreaArray(int* array, int size);
};


Matrix::Matrix()
{
    Row = 11;
    Col = 11;
    Item = new int*[Row];
    for(int i = 0; i < Row; i++)
    {
        Item[i] = new int[Col];
    }

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Col; j++)
        {
            Item[i][j] = 0+rand() % (100 - 0 + 1);
        }
    }
}

Matrix::Matrix(int r, int c, int low, int hight)
{
    if(r < 11 || r % 2 == 0 || c < 11 || c % 2 == 0)
    {
        throw invalid_argument("The matrix size must be odd and not less than 11.");
    }

    Row = r;
    Col = c;
    Item = new int*[Row];
    for(int i = 0; i < Row; i++)
    {
        Item[i] = new int[Col];
    }

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Col; j++)
        {
            Item[i][j] = low+rand() % (hight - low + 1);
        }
    }
}

void Matrix::SaveMatrixToFile(char* fileName)
{
    ofstream out;
    out.open(fileName);

    if(out.is_open())
    {
        for(int i = 0; i < Row; i++)
        {
            for(int j = 0; j < Col; j++)
            {
                out << Item[i][j] << " ";
            }
            out << endl;
        }
        out.close();
    }
    else
    {
        cerr << "Exception opening file.";
    }
}

void Matrix::SaveMatrixToFile(char* fileName, int maxElement, int minElement, int range, int counter)
{
    ofstream out;
    out.open(fileName, ios::app);
    out << endl;
    out << "Max Element: " << counter << endl;
    out << "Min Element: " << minElement << endl;
    out << "Range Area: " << range << endl;
    out << "Counter: " << counter << endl;
    out << endl;
    out.close();
}

void Matrix::OisSaveMatrixToFile(char* fileName)
{
    ofstream out;
    out.open(fileName, ios::app);

    if(out.is_open())
    {
        for(int i = 0; i < Row; i++)
        {
            for(int j = 0; j < Col; j++)
            {
                out << Item[i][j] << " ";
            }
            out << endl;
        }
        out.close();
    }
    else
    {
        cerr << "Exception opening file.";
    }
}

//Задание 2.а
int Matrix::CalculateMaxElement()
{
    int Max = 0;

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Row; j++)
        {
            if(j > i)
            {
                if(Item[i][j] > Max)
                {
                    Max = Item[i][j];
                }
            }
        }
    }

    return Max;
}

int Matrix::CalculateMinElement()
{
    int Min;
    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Row; j++)
        {
            if(j > i)
            {
                if(Item[i][j] < Min)
                {
                    Min = Item[i][j];
                }
            }
        }
    }

    return Min;
}
//Задание 2.b
int Matrix::CalculateRangeInShadedArea(int maxElement, int minElement)
{
    return maxElement - minElement;
}

int Matrix::CountElementAboveThreshold(int range, int minElement)
{
    int count = 0;
    int threshold = minElement + 0.2 * range;

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Row; j++)
        {
            if(j > i)
            {
               if(Item[i][j] > threshold)
               {
                count++;
               }
            }
        }
    }

    return count;
}

//Задание 3
void Matrix::RemoveRowWithElement(int minElement)
{
    int minRow = 0;

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Row; j++)
        {
            if(i < j)
            {
                if(Item[i][j] == minElement)
                {
                    minRow = i;
                }
            }
        }
    }
    delete[] Item[minRow];

    for(int i = minRow; i < Row - 1; i++)
    {
        Item[i] = Item[i+1];
    }

    Row--;

    int** newMatrix = new int*[Row];

    for(int i = 0; i < Row; i++)
    {
        newMatrix[i] = Item[i];
    }

    delete[] Item;
    Item = newMatrix;
}

void Matrix::Out()
{
    cout<<endl;
    cout << Row << "\t" << Col << endl;

    for(int i = 0; i < Row; i++)
    {
        for(int j = 0; j < Col; j++)
        {
            cout<<Item[i][j]<<"\t";
        }
        cout<<endl;
    }
    cout<<endl;
}

//Задание с *

int* Matrix::CreateShadedAreaArray(int &size)
{
    size = (Row * (Row - 1)) / 2;
    int* array = new int[size];
    int index = 0;

    for(int i = 0; i < Row; i++)
    {
        for(int j = i + 1; j < Col; j++)
        {
            array[index++] = Item[i][j];
        }
    }

    return array;
}

void Matrix::SortShadedAreaArray(int* array, int size)
{
    int maxIndex = 0;

    for(int i = 1; i < size; i++)
    {
        if(array[i] > array[maxIndex])
        {
            maxIndex = i;
        }
    }

    // Сортировка слева от максимального элемента по убыванию
    sort(array, array + maxIndex, greater<int>());

    // Сортировка справа от максимального элемента по возрастанию
    sort(array + maxIndex + 1, array + size);

}

int main()
{
    srand(time(0));
    //Вариант 1
    Matrix *X = new Matrix(11, 11, 10, 150);

    //Вывод матрицы на консоль
    X -> Out();
    //Запись в файл
    X -> SaveMatrixToFile("matrix.txt");
    //Рассчет максимального и минимального значения выделенной области
    int maxElement = X -> CalculateMaxElement();
    int minElement = X -> CalculateMinElement();

    cout << "Max Element " << maxElement << endl;
    cout << "Min Element " << minElement << endl;

    //Рассчет диапазона значений
    int range = X -> CalculateRangeInShadedArea(maxElement, minElement);
    cout << "Range Area " << range << endl;

    //Рассчет значений которые больше минимального на 20% диапазона
    int counter = X -> CountElementAboveThreshold(range, minElement);
    cout << "Counter " << counter << endl;
    //Запись результатов в файл
    X -> SaveMatrixToFile("matrix.txt", maxElement, minElement, range, counter);

    //Удаление строки с наименьшим значением
    X -> RemoveRowWithElement(minElement);
    X -> Out();

    //Запись в файл
    X -> OisSaveMatrixToFile("matrix.txt");

    // Создаем одномерный массив из заштрихованной области
    int size;
    int* shadedArray = X -> CreateShadedAreaArray(size);

    // Сортируем массив
    X -> SortShadedAreaArray(shadedArray, size);

    // Выводим отсортированный массив на экран и в файл
    cout << "Sorted shaded area array:" << endl;
    for(int i = 0; i < size; i++)
    {
        cout << shadedArray[i] << " ";
    }
    cout << endl;

    ofstream out;
    out.open("matrix.txt", ios::app); // Открываем файл в режиме добавления
    out << "Sorted shaded area array:" << endl;

    for(int i = 0; i < size; i++)
    {
        out << shadedArray[i] << " ";
    }

    out << endl;
    out.close();

    delete[] shadedArray;
    delete X;
    return 0;
}
