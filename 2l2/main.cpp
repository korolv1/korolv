#include "item.h"

int main() {
    std::vector<std::string> ing1 = { "А", "Б", "В" };
    std::vector<std::string> ing2 = { "А", "М", "Н" };

    item item1("А", 100, 50, ing1);
    item item2("Б", 100, 30, ing2);

    std::cout << "Товар 1" << std::endl;
    item1.print_info();

    std::cout << "Товар 2" << std::endl;
    item2.print_info();

    std::cout << "Проверка оператора +" << std::endl;
    item item3 = item1 + item2;
    item3.print_info();

    std::cout << "Проверка оператора -" << std::endl;
    item item4 = item1 - item2;
    item4.print_info();

    std::cout << "Проверка оператора -=" << std::endl;
    item item5("В", 200, 10, ing1);
    item5 -= item2;
    item5.print_info();

    std::cout << "Завершение работы" << std::endl;
    return 0;
}