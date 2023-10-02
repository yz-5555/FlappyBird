#include "Game.h"
#include <format>

constexpr u32 SCRN_W = 256 * 2;
constexpr u32 SCRN_H = 256 * 2;

constexpr float GRAVITY_SCALE = 0.1f;
constexpr float GRAVITY = 9.8f * GRAVITY_SCALE;

constexpr float JUMP_POWER = 15.0f;

constexpr float OBS_MOVE_SPEED = 7.f;

constexpr float GAP = 130.f;

void CreateObstaclePair(Object& top, Object& bottom);

int main()
{
	// Create window
	InitWindow(SCRN_W, SCRN_H, "FlappyBird");
	InitAudioDevice();
	SetTargetFPS(60);

	// Load sounds
	auto jumpSound = LoadSound("Assets/sfx-press.wav");
	auto scoreSound = LoadSound("Assets/sfx-reached.wav");
	auto deathSound = LoadSound("Assets/sfx-hit.wav");

	// Create objects.
	Object bird{};
	bird.Sprite.Image = LoadImage("Assets/Player/bird3.png");
	bird.Sprite.Data = { 1 * 16, 0, 16, 16 };
	bird.Body = { 0, SCRN_H / 2, bird.Sprite.Data.width * 3, bird.Sprite.Data.height * 3 };

	Object obTop{};
	obTop.Sprite.Image = LoadImage("Assets/Tiles.png");
	obTop.Sprite.Data = { 0, 0, 32, 80 };
	obTop.Body = { SCRN_W, 0, obTop.Sprite.Data.width * 3, obTop.Sprite.Data.height * 3 };
	obTop.Velocity.x = -OBS_MOVE_SPEED;

	Object obBottom{};
	obBottom.Body = obTop.Body;
	obBottom.Velocity = obTop.Velocity;

	// Load bird texture
	Texture2D birdTex;
	bird.Sprite.ToTexture(birdTex);

	Texture2D obstacleTex;
	obTop.Sprite.ToTexture(obstacleTex);

	CreateObstaclePair(obTop, obBottom);

	while (!WindowShouldClose())
	{
		// Out of bounds (bird-bottom)
		if (B(bird.Body) >= SCRN_H)
		{
			bird.Body.y = SCRN_H - bird.Body.height;
			bird.Acceleration.y = 0;
		}
		// Out of bounds (bird-top)
		else if (T(bird.Body) <= 0)
		{
			bird.Body.y = 0;
		}
		// Out of bounds (obs-left)
		if (L(obTop.Body) <= SCRN_W / 2)
		{

		}
		// Jump
		if (IsKeyPressed(KEY_SPACE))
		{
			bird.Velocity.y = -JUMP_POWER;
			PlaySound(jumpSound);
		}
		BeginDrawing();
		{
			ClearBackground(BLUE);

			DrawTexturePro(birdTex, bird.Sprite.Data, bird.Body, { 0, 0 }, 0.f, WHITE);
			// bird.DrawBox(GREEN);

			DrawTexturePro(obstacleTex, obTop.Sprite.Data, obTop.Body, { 0, 0 }, 0.f, WHITE);
			// obTop.DrawBox(BLACK);
			DrawTexturePro(obstacleTex, obTop.Sprite.Data, obBottom.Body, { 0, 0 }, 0.f, WHITE);
			// obBottom.DrawBox(RED);

			// DrawText(std::format("TOP {}, {}", obTop.Body.x, obTop.Body.y).c_str(), 0, 0, 30, BLACK);
			// DrawText(std::format("BOTTOM {}, {}", obBottom.Body.x, obBottom.Body.y).c_str(), 0, 40, 30, BLACK);
		}
		EndDrawing();

		bird.Update();
		obTop.Update();
		obBottom.Update();

		bird.Acceleration.y = GRAVITY;
	}
	// Cleanup
	UnloadSound(jumpSound);
	UnloadSound(scoreSound);
	UnloadSound(deathSound);

	UnloadTexture(birdTex);

	CloseWindow();
}
// TODOS
// 1. Draw score.
// 5. Make hit process.
// 7. Add animation to bird.

void CreateObstaclePair(Object& top, Object& bottom)
{
	auto min = SCRN_H - GAP - top.Body.height;
	top.Body.y = GetRandomValue(min - top.Body.height, 0);
	bottom.Body.y = top.Body.y + top.Body.height + GAP;
}