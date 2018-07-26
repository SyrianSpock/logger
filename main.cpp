#include <iostream>

#include "Logger.h"

struct Rectangle
{
    int h;
    int w;
};

struct Circle
{
    int r;
};

struct Sprite
{
    std::string path;
};

void display(const Rectangle&)
{
    std::cout << "Logged rectangle" << std::endl;
}
void display(const Circle&)
{
    std::cout << "Logged circle" << std::endl;
}
void display(const Sprite&)
{
    std::cout << "Logged sprite" << std::endl;
}

int main()
{
    Logger logger;

    logger.record(Rectangle{12, 42});
    logger.record(Circle{10});
    logger.record(Sprite{"monster.png"});

    logger.displayEvents();
}