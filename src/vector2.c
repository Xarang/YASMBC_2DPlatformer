#include "include/vector2.h"

void vector2_add(struct vector2 *vector, struct vector2 v1, struct vector2 v2, double k)
{
    vector->x = v1.x + v2.x * k;
    vector->y = v1.y + v2.y * k;
}

void vector2_multiply(struct vector2 *vector, struct vector2 v1, struct vector2 v2)
{
    vector->x = v1.x * v2.x;
    vector->y = v1.y * v2.y;
}

void vector2_scale(struct vector2 *vector, double k)
{
    vector->x *= k;
    vector->y *= k;
}

void vector2_cpy(struct vector2 *v1, struct vector2 v2)
{
    v1->x = v2.x;
    v1->y = v2.y;
}

/*
double vector2_len(struct vector2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
*/

/*
void vector2_normalize(struct vector2 *v)
{
    double len = vector2_len(*v);
    vector2_scale(v, 1/len);
}
*/
