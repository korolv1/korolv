#include <iostream>
#include <bitset>

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Задание №1" << std::endl;
    short A;
    short i;
    std::cin >> A >> i;
    std::cout << A << "=" << std::bitset<8>(A) << std::endl;
    short k = (A & (1 << i));
    if (k == 0)
    {
        std::cout << (A * A) << "=" << std::bitset<8>(A * A) << std::endl;
        std::cout << ((A * A) & ~(1 << i)) << "=" << std::bitset<8>((A * A) & ~(1 << i)) << std::endl;
    }
    else
    {
        unsigned char esl = 125;
        std::cout << esl << "=" << std::bitset<8>(esl) << std::endl;
        std::cout << (esl & 0b10101010) << "=" << std::bitset<8>(esl & 0b10101010) << std::endl;
    }
    std::cout << "Задание №2" << std::endl;
    short N; // unsigned int не сохраняет числа с минусом и выводит их как положительные большие числа
    std::cin >> N;
    switch (N)
    {
    case 113: std::cout << "Калининград - Чапаево "; break;
    case 114:
    case 141: std::cout << "Калининград - Зеленоградск "; break;
    case 117: std::cout << "Калининград - Мамоново "; break;
    case 118: std::cout << "Калининград - Светлогорск "; break;
    case 119: std::cout << "Калининград - Пионерский "; break;
    case 125: std::cout << "Калининград - Донское "; break;
    case 136: std::cout << "Калининград - Партизанское "; break;
    case 148:
    case 191: std::cout << "Калининград - Багратионовск "; break;
    case 161: std::cout << "Калининград - Светлое "; break;
    case 593: std::cout << "Калининград - Морское "; break;
    case 802: std::cout << "Калининград - Гданьск "; break;

    default: std::cout << "Маршрут не найден";
    }
    return 0;
}
