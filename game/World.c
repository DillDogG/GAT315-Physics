#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "World.h"
#include "Body.h"

ncBody* ncBodies = NULL;
int bodyCount = 0;
Vector2 ncGravity;

ncBody* CreateBody()
{
	ncBody* newBody;
	newBody = malloc(sizeof(ncBody));
	assert(newBody);

	memset(newBody, 0, sizeof(ncBody));

	newBody->prev = NULL;
	newBody->next = ncBodies;
	if (bodyCount > 0)
	{
		ncBodies->prev = newBody;
	}
	ncBodies = newBody;
	bodyCount++;
	return newBody;
}

void DestroyBody(ncBody* body)
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
	if (body == ncBodies) {
		ncBodies = body->next;
	}
	bodyCount--;
	free(body);
}

void DestroyAllBodies()
{

}