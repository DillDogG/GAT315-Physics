#include "World.h"
#include "mathf.h"
#include "Integrator.h"

#include "raylib.h"
#include "raymath.h"

#include <assert.h>
#include <stdlib.h>


int main(void)
{
	SetTargetFPS(60);

	InitWindow(800, 450, "raylib [core] example - basic window");
	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		Vector2 position = GetMousePosition();

		if (IsMouseButtonDown(0))
		{
			gpBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(1, 10);
		}

		// apply force
		gpBody* body = gpBodies;
		while (body)
		{
			ApplyForce(body, CreateVector2(0, -50));
			body = body->next;
		}

		body = gpBodies;
		while (body)
		{
			ExplicitEuler(body, dt);
			ClearForce(body);
			body = body->next;
		}

		BeginDrawing();
		ClearBackground(BLACK);
		DrawText(TextFormat("FPS: %.2f", fps), 10, 10, 20, LIME);
		DrawText(TextFormat("DT: %.4f", dt), 10, 30, 20, LIME);
		body = gpBodies;
		while (body)	
		{
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, RED);
			body = body->next;
		}
		EndDrawing();
	}
	CloseWindow();
	DestroyAllBodies();
	return 0;
}