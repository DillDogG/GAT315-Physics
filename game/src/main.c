#include "World.h"
#include "mathf.h"
#include "Integrator.h"
#include "Force.h"
#include "render.h"
#include "editor.h"

#include "raylib.h"
#include "raymath.h"

#include <assert.h>
#include <stdlib.h>


int main(void)
{
	InitWindow(1260, 680, "raylib [core] example - basic window");
	SetTargetFPS(60);

	// initialize world
	ncGravity = (Vector2){ 0, 0 };

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		Vector2 position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(position);

		if (IsMouseButtonDown(0))
		{
			float angle = GetRandomFloatValue(0, 360);
			for (int i = 0; i < 1; i++)
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassMinValue, ncEditorData.BodyTypeActive);
				//body->position = ConvertScreenToWorld(position);
				//body->mass = ncEditorData.MassMinValue;
				//body->inverseMass = 1 / body->mass;
				//body->type = BT_DYNAMIC;
				//body->type = ncEditorData.BodyTypeActive;
				//body->damping = 0;//2.5f;
				//body->gravityScale = 20;
				//Vector2 force = Vector2Scale(GetVector2FromAngle(angle), GetVector2FromAngle(angle));
				//ApplyForce(body, force, FM_IMPULSE);
				AddBody(body);
			}
		}


		// apply force

		ApplyGravitation(ncBodies, ncEditorData.GravitationValue);
		ncBody* body = ncBodies;
		while (body)
		{
			//ApplyForce(body, CreateVector2(0, -50), FM_FORCE);
			body = body->next;
		}

		body = ncBodies;
		while (body)
		{
			Step(body, dt);
			body = body->next;
		}

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f", fps), 10, 10, 20, LIME);
		DrawText(TextFormat("DT: %.4f", dt), 10, 30, 20, LIME);
		body = ncBodies;
		while (body)	
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), RED);
			body = body->next;
		}
		DrawEditor(position);
		EndDrawing();
	}
	CloseWindow();
	DestroyAllBodies();
	return 0;
}