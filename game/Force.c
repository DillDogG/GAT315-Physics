#include "Force.h"
#include "body.h"

void ApplyGravitation(ncBody* bodies, float strength)
{
	for (ncBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (ncBody* body2 = bodies; body2; body2 = body2->next)
		{
			if (body2 != body1)
			{
				Vector2 direction = Vector2Subtract(body1->position, body2->position);
				float distance = Vector2Length(direction);

				distance = fmaxf(distance, 1);
				float force = (body1->mass * body2->mass / (distance * distance)) * strength;

				direction = Vector2Scale(Vector2Normalize(direction), force);

				ApplyForce(body1, Vector2Scale(direction, -1), FM_IMPULSE);
				ApplyForce(body2, direction, FM_IMPULSE);
			}
			
		}
	}
}