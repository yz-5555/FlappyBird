#include "Game.h"

constexpr u32 SCRN_W = 256 * 2;
constexpr u32 SCRN_H = 256 * 2;

constexpr float GRAVITY_SCALE = 0.1f;
constexpr float GRAVITY = 9.8f * GRAVITY_SCALE;

constexpr float JUMP_POWER = 15.0f;

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

	Object obstacle{};
	obstacle.Sprite.Image = LoadImage("Assets/Tiles.png");
	obstacle.Sprite.Data = { 0, 0, 32, 80 };
	obstacle.Body = { 0, 0, obstacle.Sprite.Data.width * 3, obstacle.Sprite.Data.height * 4 };

	// Load bird texture
	Texture2D birdTex;
	bird.Sprite.ToTexture(birdTex);

	Texture2D obstacleTex;
	obstacle.Sprite.ToTexture(obstacleTex);

	while (!WindowShouldClose())
	{
		// Out of bounds (bottom)
		if (B(bird.Body) >= SCRN_H)
		{
			bird.Body.y = SCRN_H - bird.Body.height;
			bird.Acceleration.y = 0;
		}
		// Out of bounds (top)
		else if (T(bird.Body) <= 0)
		{
			bird.Body.y = 0;
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
			// Draw bird's box.
			// bird.DrawBox(GREEN);

			DrawTexturePro(obstacleTex, obstacle.Sprite.Data, obstacle.Body, { 0, 0 }, 0.f, WHITE);
		}
		EndDrawing();

		bird.Update();

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
// 2. Draw obstacles.
// 5. Make hit process.
// 7. Add animation to bird.