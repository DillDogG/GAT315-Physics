#include <stdlib.h>
#include <assert.h>
#include <World.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody()
{
	Body* newBody;
	newBody = malloc(sizeof(Body));
	assert(newBody);
	newBody->prev = NULL;
	newBody->next = bodies;
	if (bodyCount > 0)
	{
		bodies->prev = newBody;
	}
	bodies = newBody;
	bodyCount++;
	return newBody;
}

void DestroyBody(Body* body)
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
	if (body == bodies) {
		bodies = body->next;
	}
	bodyCount--;
	free(body);
}