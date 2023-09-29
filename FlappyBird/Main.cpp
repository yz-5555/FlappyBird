#include "Game.h"

constexpr u32 SCRN_W = 256 * 2;
constexpr u32 SCRN_H = 256 * 2;

constexpr float GRAVITY_SCALE = 0.05f;
constexpr float GRAVITY = 9.8f * GRAVITY_SCALE;

constexpr float JUMP_POWER = 10.0f;

int main()
{
	// Create window
	InitWindow(SCRN_W, SCRN_H, "FlappyBird");
	InitAudioDevice();
	SetTargetFPS(60);

	// Load sounds
	auto jumpSound = LoadSound("Assets/sfx-press.wav");
	auto scoreSound = LoadSound("Assets/sfx-reached.wav");
	auto deadSound = LoadSound("Assets/sfx-hit.wav");

	// Create objects.
	Object bird{};
	bird.Sprite.Image = LoadImage("Assets/Player/bird3.png");
	bird.Sprite.Data = { 1 * 16, 0, 16, 16 };
	bird.Body = { 0, 0, bird.Sprite.Data.width * 3, bird.Sprite.Data.height * 3 };

	// Load bird texture
	Texture2D birdTex;
	bird.Sprite.ToTexture(birdTex);

	while (!WindowShouldClose())
	{
		// Out of bounds
		if (bird.Body.y >= SCRN_H - bird.Body.height)
		{
			bird.Body.y = SCRN_H - bird.Body.height;
			bird.Acceleration.y = 0;
		}
		if (IsKeyPressed(KEY_SPACE))
		{
			bird.Velocity.y = -JUMP_POWER;
			PlaySound(jumpSound);
		}
		BeginDrawing();
		{
			ClearBackground(BLUE);

			DrawTexturePro(birdTex, bird.Sprite.Data, bird.Body, { 0, 0 }, 0.f, WHITE);
			// DrawRectangle(bird.Body.x, bird.Body.y, bird.Body.width, bird.Body.height, { 0, 0, 0, 100 });
		}
		EndDrawing();

		bird.Update();

		bird.Acceleration.y = GRAVITY;
	}
	// Cleanup
	UnloadSound(jumpSound);
	UnloadSound(scoreSound);
	UnloadSound(deadSound);

	UnloadTexture(birdTex);

	CloseWindow();
}
// TODOS
// 1. Draw score.
// 2. Draw obstacles.
// 5. Make hit process.
// 7. Add animation to bird.