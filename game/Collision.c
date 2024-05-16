#include "Collision.h"
#include "contact.h"
#include "Body.h"
#include "mathf.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

// Function to check if two bodies intersect based on their positions and masses
bool Intersects(ncBody* body1, ncBody* body2)
{
    // Calculate the distance between the centers of the bodies
    float distance = Vector2Distance(body1->position, body2->position);
    // Calculate the sum of radii (masses) of the bodies
    float radius = body1->mass + body2->mass;
    // Check if the distance is less than or equal to the sum of radii
    return (distance <= radius);
}

// Function to create contacts between interacting bodies
void CreateContacts(ncBody* bodies, ncContact_t** contacts)
{
    // Iterate through each pair of bodies to check for potential contacts
    for (ncBody* body1 = bodies; body1; body1 = body1->next)
    {
        for (ncBody* body2 = body1->next; body2; body2 = body2->next)
        {
            // Skip self-intersections
            if (body1 == body2) continue;
            // Skip pairs where both bodies are not dynamic
            if (body1->type != BT_DYNAMIC && body2->type != BT_DYNAMIC) continue;

            // Check if the two bodies intersect
            if (Intersects(body1, body2))
            {
                // Generate a contact between the two bodies
                ncContact_t* contact = GenerateContact(body1, body2);
                // Add the contact to the list of contacts
                AddContact(contact, contacts);
            }
        }
    }
}

// Function to generate a contact between two intersecting bodies
ncContact_t* GenerateContact(ncBody* body1, ncBody* body2)
{
    // Allocate memory for the contact
    ncContact_t* contact = (ncContact_t*)malloc(sizeof(ncContact_t));
    assert(contact); // Ensure allocation succeeded

    // Initialize the contact structure
    memset(contact, 0, sizeof(ncContact_t));

    // Assign the bodies involved in the contact
    contact->body1 = body1;
    contact->body2 = body2;

    // Calculate direction and distance between bodies' positions
    Vector2 direction = Vector2Subtract(body1->position, body2->position);
    float distance = Vector2Length(direction);

    // If distance is zero (bodies are exactly overlapping), perturb direction slightly
    if (distance == 0)
    {
        direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
    }

    // Calculate the sum of radii
    float radius = body1->mass + body2->mass;

    // Fill in contact details
    contact->depth = radius - distance; // Penetration depth
    contact->normal = Vector2Normalize(direction); // Contact normal (direction of collision)
    contact->restitution = (body1->restitution + body2->restitution) * 0.5f; // Average restitution

    return contact;
}

// Function to separate bodies based on calculated contacts
void SeparateContacts(ncContact_t* contacts)
{
    // Iterate through each contact to resolve overlap
    for (ncContact_t* contact = contacts; contact; contact = contact->next)
    {
        // Calculate total inverse mass for the bodies involved
        float totalInverseMass = contact->body1->inverseMass + contact->body2->inverseMass;
        // Calculate separation vector based on penetration depth
        Vector2 separation = Vector2Scale(contact->normal, contact->depth / totalInverseMass);
        // Move bodies apart according to their inverse masses
        contact->body1->position = Vector2Add(contact->body1->position, Vector2Scale(separation, contact->body1->inverseMass));
        contact->body2->position = Vector2Add(contact->body2->position, Vector2Scale(separation, -contact->body2->inverseMass));
    }
}

// Function to resolve collision impulses between bodies
void ResolveContacts(ncContact_t* contacts)
{
    // Iterate through each contact to resolve collision impulses
    for (ncContact_t* contact = contacts; contact; contact = contact->next)
    {
        // Calculate relative velocity of the bodies at the contact point
        Vector2 rv = Vector2Subtract(contact->body1->velocity, contact->body2->velocity);
        float nv = Vector2DotProduct(rv, contact->normal);

        // Only resolve contacts where bodies are approaching (nv < 0)
        if (nv > 0) continue;

        // Calculate total inverse mass
        float tim = contact->body1->inverseMass + contact->body2->inverseMass;
        // Calculate impulse magnitude
        float impulseMagnitude = -(1 + contact->restitution) * nv / tim;
        // Calculate impulse vector
        Vector2 impulse = Vector2Scale(contact->normal, impulseMagnitude);

        // Apply impulses to the bodies
        ApplyForce(contact->body1, impulse, FM_IMPULSE);
        ApplyForce(contact->body2, Vector2Negate(impulse), FM_IMPULSE);
    }
}
