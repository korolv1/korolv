#include "mainwindow.h"
#include <iostream>

int main() {
    std::vector<std::string> c1;
    c1.push_back("а");
    c1.push_back("б");
    c1.push_back("в");

    std::vector<std::string> c2;
    c2.push_back("а");
    c2.push_back("м");
    c2.push_back("н");

    Product p1("А", 100, 50, c1);
    Product p2("Б", 100, 30, c2);

    Product p3 = p1 + p2;
    p3.printInfo();

    Product p4 = p1 - p2;
    p4.printInfo();

    p1 -= p2;
    p1.printInfo();

    return 0;
}
