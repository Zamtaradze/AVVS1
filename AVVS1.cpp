// AVVS1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random>
#include <chrono>
#include <locale.h>
#include <ctime>

using namespace std;
using namespace std::chrono;

long long branch_predictor(double x)
{
    long long sum = 0;
    int G = RAND_MAX * x;
    int a = 0;
    for (int i = 0; i < 1000000; i++)
    {
        a = rand();
        if (a < G)
            sum += a;
        else
            sum -= a;
    }
    //cout<<"G=" << G <<"\n" << endl;
    //cout << "a=" << a << "\n" << endl;
    return sum;
}
void array_Din(int G, int*** arr)
{
    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            for (int k = 0; k < G; k++) {
                arr[i][j][k] = 0;
            }
        }
    }
}

void mem(int*** arr, int G)
{

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            for (int k = 0; k < G; k++) {
                arr[i][j][k] += 5;
            }
        }
    }
}

void mem2(int*** arr, int G)
{

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            for (int k = 0; k < G; k++) {
                arr[k][j][i] += 5;
            }
        }
    }
}

int main()
{   
    setlocale(LC_ALL, "Rus");
    srand(time(0));

    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> duration;

    //Исследуем работу предсказателя переходов:
    long long sum = 0;
    cout << "Исследуем работу предсказателя переходов: \n" << endl;
    for (double i = 1.0; i > 0.11; i -= 0.1)
    {
        //double tmp = 1.0 / i;
        t1 = high_resolution_clock::now();
        sum = branch_predictor(i);
        t2 = high_resolution_clock::now();
        duration = (t2 - t1);
        cout << "G = RAND_MAX*" << i << endl;
        
        cout << "Время выполнения:" << duration.count() << endl;
        //cout << sum << endl;
        printf("sum = %lld", sum);
        cout <<"\n" << endl;
    }



    //---------------------------------
    //Исследуем работу иерархии памяти 
    cout << "Исследуем работу иерархии памяти : \n" << endl;
    cout << "Половина кэша, прямой порядок :" << endl;
    int G = 16;
    //arr = array_Din(G);
    int*** arr = new int** [G];
    for (int i = 0; i < G; i++)
    {
        arr[i] = new int* [G];
        for (int j = 0; j < G; j++)
        {
            arr[i][j] = new int[G];
        }
    }
    array_Din(G, arr);
    t1 = high_resolution_clock::now();
    mem(arr, G);
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "G = " << G << endl;
    cout << "Время выполнения:" << duration.count() << endl;

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            delete[] arr[i][j];
        }
    }
    for (int i = 0; i < G; i++)delete[]arr[i];
    delete[] arr;
    //------------------------------------------
    cout << "\n" << endl;
    cout << "Половина кэша, обратный порядок : " << endl;
    G = 16;
    //arr = array_Din(G);
    arr = new int** [G];
    for (int i = 0; i < G; i++)
    {
        arr[i] = new int* [G];
        for (int j = 0; j < G; j++)
        {
            arr[i][j] = new int[G];
        }
    }
    array_Din(G, arr);
    t1 = high_resolution_clock::now();
    mem2(arr, G);
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "G = " << G << endl;
    cout << "Время выполнения:" << duration.count() << endl;

    for (int i = 0; i < G;i++) {
        for (int j = 0; j < G;j++) {
            delete [] arr[i][j];
        }
    }
    for (int i = 0; i < G; i++)delete[]arr[i];
    delete[] arr;
    //------------------------------------------
    cout << "\n" << endl;
    cout << "Полтора кэша, прямой порядок : " << endl;
    G = 24;
    //arr = array_Din(G);
    arr = new int** [G];
    for (int i = 0; i < G; i++)
    {
        arr[i] = new int* [G];
        for (int j = 0; j < G; j++)
        {
            arr[i][j] = new int[G];
        }
    }
    array_Din(G, arr);
    t1 = high_resolution_clock::now();
    mem(arr, G);
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "G = " << G << endl;
    cout << "Время выполнения:" << duration.count() << endl;

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            delete[] arr[i][j];
        }
    }
    for (int i = 0; i < G; i++)delete[]arr[i];
    delete[] arr;
    //------------------------------------------
    cout << "\n" << endl;
    cout << "Полтора кэша, обратный порядок :" << endl;
    G = 24;
    //arr = array_Din(G);
    arr = new int** [G];
    for (int i = 0; i < G; i++)
    {
        arr[i] = new int* [G];
        for (int j = 0; j < G; j++)
        {
            arr[i][j] = new int[G];
        }
    }
    array_Din(G, arr);
    t1 = high_resolution_clock::now();
    mem2(arr, G);
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "G = " << G << endl;
    cout << "Время выполнения:" << duration.count() << endl;

    for (int i = 0; i < G; i++) {
        for (int j = 0; j < G; j++) {
            delete[] arr[i][j];
        }
    }
    for (int i = 0; i < G; i++)delete[]arr[i];
    delete[] arr;
    //------------------------------------------
    

    int key[16][16][16] = {0};

    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++) 
        {
            for (int k = 0; k < 16; k++) 
            {
                key[i][j][k] = 0;
            }
        }
    }


    cout << "______________________________________________" << endl;
    cout << "без выделения памяти" << endl;
    cout << "\n\nПоловина кэша, прямой порядок :" << endl;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 16; i++) 
    {
        for (int j = 0; j < 16; j++) 
        {
            for (int k = 0; k < 16; k++) 
            {
                key[i][j][k] += 5;
            }
        }
    }
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "Время выполнения:" << duration.count() << endl;

    cout << "\n\nПоловина кэша, обратный порядок :" << endl;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 16; i++)
    {
        for (int j = 0; j < 16; j++)
        {
            for (int k = 0; k < 16; k++)
            {
                key[k][j][i] += 5;
            }
        }
    }
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "Время выполнения:" << duration.count() << endl;


    int key2[25][25][25] = { 0 };
    cout << "\n\nПолтора кэша, прямой порядок :" << endl;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            for (int k = 0; k < 25; k++)
            {
                key2[i][j][k] += 5;
            }
        }
    }
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "Время выполнения:" << duration.count() << endl;

    cout << "\n\nПолтора кэша, обратный порядок :" << endl;
    t1 = high_resolution_clock::now();
    for (int i = 0; i < 25; i++)
    {
        for (int j = 0; j < 25; j++)
        {
            for (int k = 0; k < 25; k++)
            {
                key2[k][j][i] += 5;
            }
        }
    }
    t2 = high_resolution_clock::now();
    duration = (t2 - t1);
    cout << "Время выполнения:" << duration.count() << endl;
    return 0;
}


