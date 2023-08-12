#include <SFML/Graphics.hpp>
using namespace std;
using namespace sf;
const int width = 1280;
const int height = 768;

class Point {
public:
	Point(): pos(1, 1), vel(0, 0), color(Color(255, 255, 255)) {
		point.position = pos;
		point.color = color;
	}
	void setPos(Vector2f pos) {
		this->pos = pos;
	}
	void setColor(Color color) {
		this->color = color;
	}
	void setVelocity(Vector2f vector) {
		vel = vector;
	}

	void updateShape() {
		if (pos.x >= width || pos.x <= 0) {
			vel.x = -vel.x;
		}
		if (pos.y >= height || pos.y <= 0) {
			vel.y = -vel.y;
		}
		pos.x += vel.x;
		pos.y += vel.y;
		point.position = pos;
		point.color = color;
	}
	void drawShape(RenderWindow &window) {
		window.draw(&point, 1, Points);
	}
	void setMove() {
		switch (rand() % 2) {
		case 0:
			linearMove(rand() % 2, (rand() % 150) * 0.1); break;
		case 1:
			customMove((rand() % 150) * 0.1, (rand() % 150) * 0.1); break;
		}
	}
protected:
	Vector2f pos;
	Vector2f vel;
	Color color;
	Vertex point;
private:
	void linearMove(int type, float dz) {
		switch (type) {
		case 0:
			vel = {dz,0}; break;
		case 1:
			vel = {0,dz}; break;
		}
	}
	void customMove(float dx, float dy) {
		vel = {dx,dy};
	}
};