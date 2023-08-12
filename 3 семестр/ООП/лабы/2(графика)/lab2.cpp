#include <iostream>
#include <ctime>
#include "point.cpp"
#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;

int main() {
    setlocale(0, "");
    srand(time(0));

    const int count = 100;
    Point *point = new Point[count];
    for (int i = 0; i < count; i++) {
        point[i].setPos({(rand() % width + 1) / 1.f, (rand() % height + 1) / 1.f});
        point[i].setColor(Color(rand() % 256 + 1, rand() % 256 + 1, rand() % 256 + 1));
        point[i].setMove();
    }

    RenderWindow window(VideoMode(width, height), "Points", Style::Close);
    Clock clock;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }
        if (clock.getElapsedTime().asSeconds() > 1.0 / 60.0) {
            for (int i = 0; i < count; i++) {
                point[i].updateShape();
            }
            clock.restart();
        }
        for (int i = 0; i < count; i++) {
            point[i].drawShape(window);
        }
        window.display();
        window.clear();
    }
    delete[] point;
}