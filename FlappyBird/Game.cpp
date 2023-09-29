#include "Game.h"

constexpr vec2 operator+(const vec2& l, const vec2& r)
{
	return vec2(l.x + r.x, l.y + r.y);
}
constexpr vec2 operator-(const vec2& l, const vec2& r)
{
	return vec2(l.x - r.x, l.y - r.y);
}
constexpr vec2 operator*(float l, const vec2& r)
{
	return vec2(r.x * l, r.y * l);
}
constexpr bool operator==(const vec2& l, const vec2& r)
{
	return (l.x == r.x) && (l.y == r.y);
}
constexpr bool operator!=(const vec2& l, const vec2& r)
{
	return (l.x != r.x) || (l.y != r.y);
}

constexpr float L(const Rectangle& rect)
{
	return rect.x;
}
constexpr float R(const Rectangle& rect)
{
	return rect.x + rect.width;
}
constexpr float T(const Rectangle& rect)
{
	return rect.y;
}
constexpr float B(const Rectangle& rect)
{
	return rect.y + rect.height;
}

void Sprite::ToTexture(Texture2D& tex)
{
	tex = LoadTextureFromImage(Image);
	UnloadImage(Image);
}

void Object::Update()
{
	Body.x += Velocity.x;
	Body.y += Velocity.y;
	Velocity = Velocity + Acceleration;
}