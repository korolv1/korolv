#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>

class item {
private:
    std::string name;
    double price;
    int expiration_date;
    std::vector<std::string>* ingredients;

public:
    item();
    item(std::string n, double p, int exp, const std::vector<std::string>& ing);
    item(const item& other);

    ~item();

    item& operator=(const item& other);

    item operator+(const item& other) const;
    item operator-(const item& other) const;
    item& operator-=(const item& other);

    void print_info() const;

private:
    void add_ingredient(const std::string& ing);
    bool has_ingredient(const std::string& ing) const;
};

#endif