#include "item.h"

item::item() : name("Неизвестно"), price(0.0), expiration_date(0) {
    ingredients = new std::vector<std::string>();
}

item::item(std::string n, double p, int exp, const std::vector<std::string>& ing) {
    name = n;
    price = p;
    expiration_date = exp;
    ingredients = new std::vector<std::string>(ing);
}

item::item(const item& other) {
    name = other.name;
    price = other.price;
    expiration_date = other.expiration_date;
    ingredients = new std::vector<std::string>(*(other.ingredients));
}

item::~item() {
    if (ingredients) {
        ingredients->clear();
        delete ingredients;
    }
    std::cout << "Деструктор вызван" << std::endl;
}

item& item::operator=(const item& other) {
    if (this == &other) return *this;

    name = other.name;
    price = other.price;
    expiration_date = other.expiration_date;

    delete ingredients;
    ingredients = new std::vector<std::string>(*(other.ingredients));

    return *this;
}

bool item::has_ingredient(const std::string& ing) const {
    for (const auto& i : *ingredients) {
        if (i == ing) return true;
    }
    return false;
}

void item::add_ingredient(const std::string& ing) {
    if (!has_ingredient(ing)) {
        ingredients->push_back(ing);
    }
}

item item::operator+(const item& other) const {
    item result;
    result.name = "Смесь " + this->name + " и " + other.name;
    result.price = (this->price + other.price) * 0.9;
    result.expiration_date = (this->expiration_date < other.expiration_date) ? this->expiration_date : other.expiration_date;

    for (const auto& ing : *(this->ingredients)) {
        result.add_ingredient(ing);
    }
    for (const auto& ing : *(other.ingredients)) {
        result.add_ingredient(ing);
    }

    return result;
}

item item::operator-(const item& other) const {
    item result;
    result.name = "Выбор " + this->name + " без " + other.name;
    result.price = this->price * 0.9;
    result.expiration_date = this->expiration_date - 2;

    for (const auto& ing : *(this->ingredients)) {
        if (!other.has_ingredient(ing)) {
            result.add_ingredient(ing);
        }
    }
    result.add_ingredient("Консервант Т1000");

    return result;
}

item& item::operator-=(const item& other) {
    *this = *this - other;
    return *this;
}

void item::print_info() const {
    std::cout << "Товар: " << name << std::endl;
    std::cout << "Цена: " << price << std::endl;
    std::cout << "Срок годности: " << expiration_date << " дней" << std::endl;
    std::cout << "Состав: ";
    if (ingredients->empty()) {
        std::cout << "Нет состава";
    }
    else {
        std::cout << "[";
        for (size_t i = 0; i < ingredients->size(); ++i) {
            std::cout << (*ingredients)[i] << (i == ingredients->size() - 1 ? "" : ", ");
        }
        std::cout << "]";
    }
    std::cout << "\n" << std::endl;
}