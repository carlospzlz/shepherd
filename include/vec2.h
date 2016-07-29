#include <cmath>


class Vec2 {
	public:
		float x, y;
		Vec2() { };
		Vec2(float x, float y) : x(x), y(y) { };
		float magnitude();
		void normalize(float norm);
		Vec2 operator+(Vec2 other);
		Vec2 operator-(Vec2 other);
		Vec2 operator+=(Vec2 other);
		Vec2 operator/=(float scalar);
};
