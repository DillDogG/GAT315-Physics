#pragma once
#include "raylib.h"
#include "Body.h"

typedef struct ncEditorData
{
	float MassMinValue;
	float MassMaxValue;
	float GravitationValue;
	float GravityScaleValue;
	float DampingValue;
	ncBodyType BodyTypeActive;
} ncEditorData_t;

extern ncEditorData_t ncEditorData;

extern bool ncEditorActive;
extern bool ncEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);