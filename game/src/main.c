#include "raylib.h"
#include "World.h"

int main(void)
{
	InitWindow(800, 450, "raylib [core] example - basic window");
	while (!WindowShouldClose())
	{
		// update / draw bodies
		Body* body = bodies;
		BeginDrawing();
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{

			// update body position
			//body->position = ;
			// draw body
			DrawPixel(body->position.x, body->position.y, LIGHTGRAY);

			body = body->next; // get next body
		}
		EndDrawing();
	}
	CloseWindow();
	/*InitWindow(800, 450, "raylib [core] example - basic window");
	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		EndDrawing();
	}
	CloseWindow();*/
	return 0;
}