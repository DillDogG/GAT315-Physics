#pragma once
//#include <Body.h>
#include "raylib.h"

typedef struct gpBody gpBody;

extern gpBody* gpBodies;
extern int bodyCount;
extern Vector2 gpGravity;

gpBody* CreateBody();
void DestroyBody(gpBody* body);
void DestroyAllBodies();