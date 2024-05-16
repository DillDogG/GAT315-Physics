#include "World.h"
#include "mathf.h"
#include "Integrator.h"
#include "Force.h"
#include "render.h"
#include "editor.h"
#include "collision.h"
#include "contact.h"

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
	InitEditor();

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();
		float fps = (float)GetFPS();
		Vector2 position = GetMousePosition();
		ncScreenZoom += GetMouseWheelMove() * 0.2f;
		ncScreenZoom = Clamp(ncScreenZoom, 0.1f, 10);

		UpdateEditor(position);

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_SHIFT)))
		{
			float angle = GetRandomFloatValue(0, 360);
			for (int i = 0; i < 1; i++)
			{
				ncBody* body = CreateBody(ConvertScreenToWorld(position), ncEditorData.MassValue, ncEditorData.BodyTypeActive);
				//body->position = ConvertScreenToWorld(position);
				//body->mass = ncEditorData.MassMinValue;
				//body->inverseMass = 1 / body->mass;
				//body->type = BT_DYNAMIC;
				//body->type = ncEditorData.BodyTypeActive;
				body->damping = ncEditorData.DampingValue;
				body->gravityScale = ncEditorData.GravityScaleValue;
				body->restitution = 0.8f;
				//Vector2 force = Vector2Scale(GetVector2FromAngle(angle), GetVector2FromAngle(angle));
				//ApplyForce(body, force, FM_IMPULSE);
				AddBody(body);
			}
		}


		// apply force

		ApplyGravitation(ncBodies, ncEditorData.GravitationValue);
		//ncBody* body = ncBodies;
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Step(body, dt);
			//body = body->next;
		}

		// collision
		ncContact_t* contacts = NULL;
		CreateContacts(ncBodies, &contacts);
		SeparateContacts(contacts);
		ResolveContacts(contacts);

		//body = ncBodies;
		for (ncBody* body = ncBodies; body; body = body->next)
		{
			Step(body, dt);
			//body = body->next;
		}

		//ncContact_t* contacts = NULL;

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText(TextFormat("FPS: %.2f", fps), 10, 10, 20, LIME);
		DrawText(TextFormat("DT: %.4f", dt), 10, 30, 20, LIME);
		// draw springs
		/*for (ncBody* body = ncBodies; body; body = body->next)
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass), RED);
		}*/
		// draw bodies
		for (ncBody* body = ncBodies; body; body = body->next)	
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), WHITE);
		}
		// draw contacts
		for (ncContact_t* contact = contacts; contact; contact = contact->next)
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);
		}
		DrawEditor(position);
		EndDrawing();
	}
	CloseWindow();
	DestroyAllBodies();
	return 0;
}