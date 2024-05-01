#include <Body.h>

extern gpBody* gpBodies;
extern int bodyCount;

gpBody* CreateBody();
void DestroyBody(gpBody* body);
void DestroyAllBodies();