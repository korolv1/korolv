#include "mainwindow.h"
#include <iostream>
#include <algorithm>

Product::Product() : name(""), price(0.0), expiration_date(0) {}

Product::Product(const Product& other)
    : name(other.name), price(other.price),
    expiration_date(other.expiration_date), composition(other.composition) {}

Product::Product(std::string n, double p, int e, std::vector<std::string> c) {
    name = n;
    price = (p >= 0) ? p : 0;
    expiration_date = (e >= 0) ? e : 0;
    composition = c;
}

Product::~Product() {
    composition.clear();
    std::cout << "Destructor called: " << name << "\n";
}

Product& Product::operator=(const Product& other) {
    if (this != &other) {
        name = other.name;
        price = other.price;
        expiration_date = other.expiration_date;
        composition = other.composition;
    }
    return *this;
}

std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getExpirationDate() const { return expiration_date; }
std::vector<std::string> Product::getComposition() const { return composition; }

void Product::setPrice(double p) {
    if (p >= 0) price = p;
}

void Product::decreaseExpiration(int days) {
    if (days > 0) expiration_date -= days;
    if (expiration_date < 0) expiration_date = 0;
}

void Product::printInfo() const {
    std::cout << name << " | Price: " << price << " | Exp: " << expiration_date << " | Comp: [";
    for (size_t i = 0; i < composition.size(); ++i) {
        std::cout << composition[i] << (i == composition.size() - 1 ? "" : ", ");
    }
    std::cout << "]\n";
}

Product Product::operator+(const Product& other) const {
    std::string new_name = "смесь " + name + " и " + other.name;
    double new_price = (price + other.price) * 0.9;
    int new_exp = std::min(expiration_date, other.expiration_date);

    std::vector<std::string> new_comp = composition;
    for (size_t i = 0; i < other.composition.size(); ++i) {
        if (std::find(new_comp.begin(), new_comp.end(), other.composition[i]) == new_comp.end()) {
            new_comp.push_back(other.composition[i]);
        }
    }

    return Product(new_name, new_price, new_exp, new_comp);
}

Product Product::operator-(const Product& other) const {
    std::string new_name = "выбор " + name + " без " + other.name;
    double new_price = price * 0.9;
    int new_exp = expiration_date - 2;

    std::vector<std::string> new_comp;
    for (size_t i = 0; i < composition.size(); ++i) {
        if (std::find(other.composition.begin(), other.composition.end(), composition[i]) == other.composition.end()) {
            new_comp.push_back(composition[i]);
        }
    }
    new_comp.push_back("консервант Т1000");

    return Product(new_name, new_price, new_exp, new_comp);
}

Product& Product::operator-=(const Product& other) {
    name = "выбор " + name + " без " + other.name;
    price = price * 0.9;
    expiration_date -= 2;

    std::vector<std::string> new_comp;
    for (size_t i = 0; i < composition.size(); ++i) {
        if (std::find(other.composition.begin(), other.composition.end(), composition[i]) == other.composition.end()) {
            new_comp.push_back(composition[i]);
        }
    }
    new_comp.push_back("консервант Т1000");
    composition = new_comp;

    return *this;
}
