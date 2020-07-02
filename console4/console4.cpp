#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int **a;
int *base; // база
int *d;    // посещенные, 1000 - база, 1 - просто посещенная
// вершина считается посещенной = 1, если
// она смежна с вершиной из базы графа = 1000
string f_name;
string f_base = "base.txt"; // файл с базой графа

void get_matrix(int &n)
{
    ifstream fin(f_name);
    fin >> n;
    a = new int *[n];
    for (int i = 0; i < n; i++)
    {
        a[i] = new int[n];
        for (int j = 0; j < n; j++)
            fin >> a[i][j];
    }
    fin.close();
}

void show(int &n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

// формирование базы графа
void base_function(int &n)
{
    ofstream bfout(f_base);
    int k = 0;
    d = new int[n];
    bool f = false;
    for (int i = 0; i < n; i++)
        d[i] = 0;

    // вычисляем непосещенные вершины
    for (int i = 0; i < n; i++)
    {
        f = false;
        for (int j = 0; j < n && !f; j++)
            if (d[j] == 0)
            {
                d[j] = 1000;
                k++;
                f = true; // как только находим новую непосещенную, выходим из цикла
            }
        if (d[i] == 1000)
            for (int j = 0; j < n; j++)
                if (a[i][j] == 1)
                    d[j] = 1;
    }
    base = new int[k];
    k = 0;

    // вычисляем вершины базы графа
    for (int i = 0; i < n; i++)
        if (d[i] == 1000)
        {
            base[k] = i;
            k++;
        }

    cout << "\nBase of graph:\n";
    for (int i = 0; i < k; i++)
    {
        if (i != k - 1)
            bfout << base[i] << endl;
        else
            bfout << base[i];
        cout << base[i] << "\t";
    }
}

int main()
{
    system("cls");
    int n;
    cout << "File name: ";
    cin >> f_name;
    cout << endl;

    get_matrix(n);

    show(n);

    base_function(n);
}