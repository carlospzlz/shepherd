#include <vec2.h>


void Vec2::normalize(float norm) {
	float magnitude = sqrt(pow(x, 2) + pow(y, 2));
	x /= magnitude * norm;
	y /= magnitude * norm;
}


float Vec2::magnitude() {
	return sqrt(pow(x, 2) + pow(x, 2));
}


Vec2 Vec2::operator+(Vec2 other) {
	return Vec2(x + other.x, y + other.y);
}


Vec2 Vec2::operator-(Vec2 other) {
	return Vec2(x - other.x, y - other.y);
}


Vec2 Vec2::operator+=(Vec2 other) {
	x += other.x;
	y += other.y;
	return *this;
}


Vec2 Vec2::operator/=(float scalar) {
	x /= scalar;
	y /= scalar;
	return *this;
}
