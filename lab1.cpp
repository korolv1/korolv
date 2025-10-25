#include <iostream>
#include <cmath>

int main()
{
    setlocale(LC_ALL, "Russian");
    float s1; // сторона может быть и 3.5 - вещественное число 
    int s2;
    int s3;
    std::cin >> s1 >> s2 >> s3;

    float Pp = (s1 + s2 + s3) / 2.0f; // может получиться дробное число, поэтому float
    float S = sqrt(Pp * (Pp - s1) * (Pp - s2) * (Pp - s3));

    float mx = FLT_MAX;
    float mn = FLT_MIN;
    short r = sizeof(s1) * 8;

    std::cout << "Ответ:" << S << std::endl;
    std::cout << "Тип float занимает " << r << " бита" << std::endl;
    std::cout << "Максимальное значение - " << mx << std::endl;
    std::cout << "Минимумальное значение - " << mn << std::endl;
}