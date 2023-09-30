#include "Game.h"

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

void Object::DrawBox(Color color)
{
	DrawRectangle(Body.x, Body.y, Body.width, Body.height, { color.r, color.g, color.b, 150 });
}
