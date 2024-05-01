#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum 
{
	STATIC,
	KINEMATIC,
	DYNAMIC
} gpBodyType;

typedef struct gpBody
{
	gpBodyType body;
	// force -> acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	float mass;
	float inverseMass; // i / mass (static = 0)

	struct gpBody* next;
	struct gpBody* prev;
} gpBody;

inline void ApplyForce(gpBody* body, Vector2 force)
{
	body->force = Vector2Add(body->force, force);
}

inline void ClearForce(gpBody* body)
{
	body->force = Vector2Zero();
}