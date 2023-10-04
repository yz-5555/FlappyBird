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

// Debug utils
void DrawBox(const rect& r, Color color);

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

	void Update();
};

struct PipePair
{
	rect Body;
	float TopY;
	float BottomY;

	vec2 Velocity;

	rect SpriteData;

	void Create(const rect& source, const rect& spriteData, const vec2& velocity);
	void GenerateRandom(float gap, float screenHeight);
	void Update();
	void Draw(const Texture2D& tex);
};