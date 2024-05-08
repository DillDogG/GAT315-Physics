#pragma once
//#include <Body.h>
#include "raylib.h"

typedef struct ncBody ncBody;

extern ncBody* ncBodies;
extern int bodyCount;
extern Vector2 ncGravity;

ncBody* CreateBody();
void DestroyBody(ncBody* body);
void DestroyAllBodies();