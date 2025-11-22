#include <iostream>

int TwoNumbers(int x, int y)
{
    std::cout << "Исп функция для 2 чисел" << std::endl;

    int temp = y;
    int multiplier = 1;
    while (temp > 0)
    {
        temp /= 10;
        multiplier *= 10;
    }

    return x * multiplier + y;
}


int OneNumber(int x)
{   
    std::cout << "Исп функция для 1 числа" << std::endl;
    

    return -x;
}

void Geron(float x, float y, float z)
{
    float Pp = (x + y + z) / 2.0f;
    float S = sqrt(Pp * (Pp - x) * (Pp - y) * (Pp - z));
    std::cout << S << std::endl;
}

int main()
{   
    setlocale(LC_ALL, "Russian");
    int p;
    std::cout << "Выберите задание" << std::endl;
    std::cin >> p; 
    if (p == 1)
    {
        const int i = 3;
        int mass[i];
        int lp = 0;
        int arr[i];
        int res = 0;
        std::cout << "Введите 3 числа" << std::endl;

        for (int j = 0; j < i; ++j)
        {
            std::cin >> mass[j];

            if (mass[j] > 0)
            {
                if (lp < i)
                    arr[lp] = mass[j];
                lp++;
            }
        }

        if (lp == 0)
        {
            std::cout << "Все числа 0";
        }

        else if (lp == 1)
        {
            res = OneNumber(arr[0]);
        }

        else if (lp == 2)
        {
            res = TwoNumbers(arr[0], arr[1]);
        }

        else
        {
            std::cout << "Алгоритм для 3 чисел не найден";
        }
        
        if ( lp < 3)
        {
             std::cout << res << std::endl;
        }
    }

    else if (p == 2)
    {
        float s1;
        float s2;
        float s3;
        std::cin >> s1 >> s2 >> s3;
        Geron(s1, s2, s3);
    }
    else
    {
        std::cout << "Существуют лишь задания 1 и 2";
    }
} 
