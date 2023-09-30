#pragma once

#include <raylib.h>

// Type names too long! D:
typedef Vector2 vec2;
typedef unsigned int u32;
typedef Rectangle rect;

// Vector2 utils
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

// Rectangle utils
constexpr float L(const rect& val)
{
	return val.x;
}
constexpr float R(const rect& val)
{
	return val.x + val.width;
}
constexpr float T(const rect& val)
{
	return val.y;
}
constexpr float B(const rect& val)
{
	return val.y + val.height;
}

struct Sprite
{
	Image Image;
	rect Data;

	void ToTexture(Texture2D& tex);
};

struct Object
{
	rect Body;
	vec2 Velocity;
	vec2 Acceleration;

	Sprite Sprite;

	bool Visible;

	void Update();
	void DrawBox(Color color);
};