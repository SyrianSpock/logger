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

    LOG_ERROR(logger, Rectangle({12, 42}));
    LOG_WARN(logger, Circle({10}));
    LOG_INFO(logger, Sprite({"monster.png"}));
    LOG_DEBUG(logger, Sprite({"knight.png"}));

    logger.displayEvents(LogLevel::Debug);
}
