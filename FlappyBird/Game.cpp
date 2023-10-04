#include "Game.h"

void DrawBox(const rect& r, Color color)
{
	DrawRectangle(r.x, r.y, r.width, r.height, { color.r, color.g, color.b, 150 });
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
void PipePair::Create(const rect& source, const rect& spriteData, const vec2& velocity)
{
	Body = source;
	SpriteData = spriteData;
	Velocity = velocity;
}

void PipePair::GenerateRandom(float gap, float screenHeight)
{
	float min = screenHeight - gap - Body.height;

	TopY = GetRandomValue(min - Body.height, 0);
	BottomY = TopY + Body.height + gap;
}
void PipePair::Update()
{
	Body.x += Velocity.x;
}
void PipePair::Draw(const Texture2D& tex)
{
	rect dest = Body;

	dest.y = TopY;
	DrawTexturePro(tex, SpriteData, dest, { 0, 0 }, 0.f, WHITE);

	dest.y = BottomY;
	DrawTexturePro(tex, SpriteData, dest, { 0, 0 }, 0.f, WHITE);
}