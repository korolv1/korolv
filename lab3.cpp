#include <iostream>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Задание 1" << std::endl;
    short p;
    std::cin >> p;
    int ch;
    int l = 0;
    int mx = 0;
    int pmx = 0;

    for (int s = 1; p >= s; ++s)
    {
        std::cin >> ch;
        if ((ch % 3 == 0) || (ch % 5 == 0) || (ch % 7 == 0))
        {
            ch = 0;
        }
        else
        {
            if (mx < ch)
            {
                mx = ch;
                pmx = s;
            }
            l += ch;
        }
    }

    if (l > 0 && mx > 0 && pmx > 0)
    {
        std::cout << "Сумма всех подходящих чисел = " << l << std::endl;
        std::cout << "Максимальное число = " << mx << std::endl;
        std::cout << "Его номер = " << pmx << std::endl;
    }
    else
    {
        std::cout << "Подходящие числа не найдены" << std::endl;
    }

    std::cout << "Задание 2" << std::endl;

    int x;
    int q = 0;
    std::cin >> x;

    if (x < 1000)
    {
        do
        {
            x = x / 10;
            q += 1;

            if (x < 10 && x > 0)
            {
                std::cout << "Первая цифра = " << x << std::endl;
            }

        } while (x > 0);

        std::cout << "Количество разрядов = " << q << std::endl;
    }
    else
    {
        std::cout << "Введите число ниже 1000" << std::endl;
    }
}
