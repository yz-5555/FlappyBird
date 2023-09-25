#include <raylib.h>
#include <format>

struct Sprite
{
	Image Image;
	Rectangle Rect;
};
struct Object
{
	Rectangle Body;
	Vector2 Velocity;
	Sprite Sprite;
};
struct Bird
{
	Object Data;
	bool IsFalling;
	bool IsHit;
};

constexpr float GRAVITY_SCALE = 0.5f;
constexpr float GRAVITY = 9.8f * GRAVITY_SCALE;
constexpr float JUMP_POWER = -5.f;

int main()
{
	// Create window.
	Vector2 windowSize = { 500, 700 };

	InitWindow(windowSize.x, windowSize.y, "FlappyBird");
	SetTargetFPS(60);

	// Create objects.
	Bird bird{};
	bird.IsFalling = true;
	bird.Data.Sprite.Image = LoadImage("Assets/Player/bird1.png");
	bird.Data.Sprite.Rect = { 0, 0, 16, 16 };
	bird.Data.Body = { 50, windowSize.y / 2.f - bird.Data.Sprite.Rect.height, bird.Data.Sprite.Rect.width, bird.Data.Sprite.Rect.height };

	// Ready to render textures.
	auto birdTex = LoadTextureFromImage(bird.Data.Sprite.Image);
	UnloadImage(bird.Data.Sprite.Image);

	while (!WindowShouldClose())
	{
		bird.Data.Velocity = { 0.f, 0.f };

		if (bird.Data.Velocity.y == 0.f)
			bird.IsFalling = true;
		// Key update
		if (IsKeyDown(KEY_SPACE))
		{
			bird.IsFalling = false;
			bird.Data.Velocity.y += JUMP_POWER;
		}
		// Draw
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			DrawFPS(0, 0);

			Rectangle dest = { bird.Data.Body.x, bird.Data.Body.y, bird.Data.Body.width * 3, bird.Data.Body.height * 3 };
			float rotate = 0.f;

			if (bird.IsFalling)
				rotate = 45.f;
			else
				rotate = -45.f;
			DrawTexturePro(birdTex, bird.Data.Sprite.Rect, dest, { dest.width / 2, dest.height / 2 }, rotate, RAYWHITE);
			DrawText(std::format("{}", bird.Data.Velocity.y).c_str(), 0, 50, 50, BLACK);
		}
		EndDrawing();

		// Update
		bird.Data.Body.x += bird.Data.Velocity.x;
		bird.Data.Body.y += bird.Data.Velocity.y;

		bird.Data.Body.y += GRAVITY;
	}
	// Cleanup
	CloseWindow();
}
// TODOS
// 1. Draw score.
// 2. Draw obstacles.
// 3. Make bird rotate.
// 4. Get key input and make bird jump.
// 5. Make hit process.
// 6. Add background.
// 7. Add animation to bird.