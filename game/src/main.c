#include "World.h"
#include "mathf.h"
#include "Integrator.h"

#include "raylib.h"
#include "raymath.h"

#include <assert.h>
#include <stdlib.h>


int main(void)
{
	InitWindow(800, 450, "raylib [core] example - basic window");
	SetTargetFPS(60);

	// initialize world
	gpGravity = (Vector2){ 0, 30 };

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
			body->inverseMass = 1 / body->mass;
			body->type = BT_DYNAMIC;
			body->damping = 0.5f;
			body->gravityScale = 20;
			ApplyForce(body, (Vector2){ GetRandomFloatValue(-100, 100), GetRandomFloatValue(-100, 100) }, FM_VELOCITY);
		}

		// apply force
		gpBody* body = gpBodies;
		while (body)
		{
			//ApplyForce(body, CreateVector2(0, -50), FM_FORCE);
			body = body->next;
		}

		body = gpBodies;
		while (body)
		{
			Step(body, dt);
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