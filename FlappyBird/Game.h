#pragma once

#include <raylib.h>

// Type names too long! D:
typedef Vector2 vec2;
typedef unsigned int u32;

// Vector2 utils
constexpr vec2 operator+(const vec2& l, const vec2& r);
constexpr vec2 operator-(const vec2& l, const vec2& r);
constexpr vec2 operator*(float l, const vec2& r);
constexpr bool operator==(const vec2& l, const vec2& r);
constexpr bool operator!=(const vec2& l, const vec2& r);

// Rectangle utils
constexpr float L(const Rectangle& rect);
constexpr float R(const Rectangle& rect);
constexpr float T(const Rectangle& rect);
constexpr float B(const Rectangle& rect);

struct Sprite
{
	Image Image;
	Rectangle Data;

	void ToTexture(Texture2D& tex);
};

struct Object
{
	Rectangle Body;
	Vector2 Velocity;
	Vector2 Acceleration;

	Sprite Sprite;

	bool Visible;

	void Update();
};