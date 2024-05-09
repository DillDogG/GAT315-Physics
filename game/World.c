#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "World.h"
#include "Body.h"

ncBody* ncBodies = NULL;
int bodyCount = 0;
Vector2 ncGravity;

ncBody* CreateBody(Vector2 position, float mass, ncBodyType bodyType)
{
	ncBody* newBody = malloc(sizeof(ncBody));
	assert(newBody);

	memset(newBody, 0, sizeof(ncBody));
	newBody->position = position;
	newBody->mass = mass;
	newBody->inverseMass = (bodyType == BT_DYNAMIC) ? 1 / mass : 0;
	newBody->type = bodyType;

	return newBody;
}

void AddBody(ncBody* body)
{
	assert(body);
	body->prev = NULL;
	body->next = ncBodies;
	if (ncBodies) ncBodies->prev = body;
	ncBodies = body;
	bodyCount++;
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