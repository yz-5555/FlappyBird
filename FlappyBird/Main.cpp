#include <iostream>
#include <raylib.h>

int main()
{
	Vector2 windowSize = { 800, 600 };

	InitWindow(windowSize.x, windowSize.y, "FlappyBird");
	SetTargetFPS(60);

	auto bird = LoadTexture("Assets/Player/bird1.png");
	auto rect = Rectangle(0, 0, 16, 16);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		{
			ClearBackground(RAYWHITE);
			DrawTexture(bird, 50, 50, RAYWHITE);
			DrawTextureRec(bird, rect, { 0, 0 }, RAYWHITE);
		}
		EndDrawing();
	}
	CloseWindow();
}