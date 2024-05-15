#pragma once
#include "raylib.h"
#include "Body.h"

typedef struct ncEditorData
{
	bool BodyTypeEditMode;
	float MassValue;
	float GravitationValue;
	float GravityScaleValue;
	float DampingValue;
	int BodyTypeActive;
	float StiffnessValue;
	float GravityValue;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);
struct ncBody* GetBodyIntersect(struct ncBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct ncBody* body, Vector2 position);