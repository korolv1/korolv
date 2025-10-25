#include <iostream>
#include <cmath>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Задание 1" << std::endl;

    int vl[9];
    int temp = 0;

    for (int p = 0; p < 9; ++p)
    {
        std::cin >> vl[p];
    }

    for (int p = 0; p < 9; ++p)
    {
        temp = vl[p];
        while (temp >= 10)
        {
            temp /= 10;
        }

        if (temp == 3)
        {
            for (int i = 0; i < 9; ++i)
            {
                for (int j = i + 1; j < 9; ++j)
                {
                    if (vl[i] > vl[j])
                    {
                        std::swap(vl[i], vl[j]);
                    }
                }
            }
        }
    }

    std::cout << "Данный массив после всех операций " << std::endl;
    for (int p = 0; p < 9; ++p)
    {
        std::cout << vl[p] << std::endl;
    }

    std::cout << "Задание 2" << std::endl;

    const int s = 3;
    const int c = 4;
    int ans = 0;
    int str = -1;
    int sc[s][c];

    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            std::cin >> sc[i][j];
        }
    }

    for (int i = 0; i < s; ++i)
    {
        int sm = 0;
        for (int j = 0; j < c; ++j)
        {
            sm += sc[i][j];
        }

        if (abs(sm) > ans)
        {
            ans = sm;
            str = i;
        }
    }

    for (int j = 0; j < c; ++j)
    {
        sc[str][j] = 999;
    }

    for (int i = 0; i < s; ++i)
    {
        for (int j = 0; j < c; ++j)
        {
            std::cout << sc[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
