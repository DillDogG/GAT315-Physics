#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "World.h"
#include "Body.h"

gpBody* gpBodies = NULL;
int bodyCount = 0;
Vector2 gpGravity;

gpBody* CreateBody()
{
	gpBody* newBody;
	newBody = malloc(sizeof(gpBody));
	assert(newBody);

	memset(newBody, 0, sizeof(gpBody));

	newBody->prev = NULL;
	newBody->next = gpBodies;
	if (bodyCount > 0)
	{
		gpBodies->prev = newBody;
	}
	gpBodies = newBody;
	bodyCount++;
	return newBody;
}

void DestroyBody(gpBody* body)
{
	assert(body);
	if (body->next != NULL)
	{
		body->next->prev = body->prev;
	}
	if (body->prev != NULL)
	{
		body->prev->next = body->next;
	}
	if (body == gpBodies) {
		gpBodies = body->next;
	}
	bodyCount--;
	free(body);
}

void DestroyAllBodies()
{

}