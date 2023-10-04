#include "Game.h"
#include <format>
#include <string>
#include <array>

constexpr u32 SCRN_W = 256 * 2;
constexpr u32 SCRN_H = 256 * 2;

constexpr float GRAVITY_SCALE = 0.1f;
constexpr float GRAVITY = 9.8f * GRAVITY_SCALE;

constexpr float JUMP_POWER = 12.0f;

constexpr float PIPES_MOVE_SPEED = 3.f;
constexpr float PIPES_GAP_Y = 210.f;
constexpr float PIPES_GAP_X = 80.f;

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
	bool alive = true;

	Object pipe{};
	pipe.Sprite.Image = LoadImage("Assets/Tiles.png");
	pipe.Sprite.Data = { 0, 0, 32, 80 };
	pipe.Body = { SCRN_W, 0, pipe.Sprite.Data.width * 3, pipe.Sprite.Data.height * 3 };
	pipe.Velocity.x = -PIPES_MOVE_SPEED;

	u32 score = 0;

	std::array<PipePair, 5> pairs{};
	rect source = pipe.Body;
	for (auto& item : pairs)
	{
		item.Create(source, pipe.Sprite.Data, pipe.Velocity);
		item.GenerateRandom(PIPES_GAP_Y, SCRN_H);

		source.x = R(source) + PIPES_GAP_X;
	}

	// Load bird texture
	Texture2D birdTex;
	bird.Sprite.ToTexture(birdTex);

	Texture2D pipeTex;
	pipe.Sprite.ToTexture(pipeTex);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(BLUE);

			DrawTexturePro(birdTex, bird.Sprite.Data, bird.Body, { 0, 0 }, 0.f, WHITE);
			// bird.DrawBox(GREEN);

			for (auto& pair : pairs)
			{
				pair.Draw(pipeTex);
				DrawBox(pair.Body, BLACK);
				if (R(pair.Body) <= L(bird.Body))
				{
					score += 1;
				}
			}
			DrawText(std::to_string(score).c_str(), 10, 10, 30, BLACK);
		}
		EndDrawing();

		// Bird update
		bird.Update();
		bird.Acceleration.y = GRAVITY;

		// Pipes update
		for (int i = 0; i < pairs.size(); i++)
		{
			pairs[i].Update();

			// Out of bounds (pipes-right)
			if (R(pairs[i].Body) <= 0.f)
			{
				pairs[i].GenerateRandom(PIPES_GAP_Y, SCRN_H);

				// if not first pipe - Follow previous pipe
				if (i != 0) pairs[i].Body.x = R(pairs[i - 1].Body) + PIPES_GAP_X;
				// if first pipe - Follow last pipe
				else pairs[i].Body.x = R(pairs[pairs.size() - 1].Body) + PIPES_GAP_X;
			}
			// Scoring
			if (R(pairs[i].Body) <= L(bird.Body))
			{
				score += 1;
			}
		}

		// Out of bounds (bird-bottom)
		if (B(bird.Body) >= SCRN_H)
		{
			bird.Body.y = SCRN_H - bird.Body.height;
			bird.Acceleration.y = 0;
			alive = false;
		}
		// Out of bounds (bird-top)
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
	}
	// Cleanup
	UnloadSound(jumpSound);
	UnloadSound(scoreSound);
	UnloadSound(deathSound);

	UnloadTexture(birdTex);

	CloseWindow();
}
// TODOS
// 5. Make hit process.
// 7. Add animation to bird.