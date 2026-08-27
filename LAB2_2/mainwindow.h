#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <string>
#include <vector>

class Product {
private:
    std::string name;
    double price;
    int expiration_date;
    std::vector<std::string> composition;

public:
    Product();
    Product(const Product& other);
    Product(std::string n, double p, int e, std::vector<std::string> c);
    ~Product();

    Product& operator=(const Product& other);

    std::string getName() const;
    double getPrice() const;
    int getExpirationDate() const;
    std::vector<std::string> getComposition() const;

    void setPrice(double p);
    void decreaseExpiration(int days);
    void printInfo() const;

    Product operator+(const Product& other) const;
    Product operator-(const Product& other) const;
    Product& operator-=(const Product& other);
};

#endif
