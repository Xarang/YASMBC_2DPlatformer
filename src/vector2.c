#include "vector2.h"

struct vector2 vector2_init(double x, double y)
{
    struct vector2 res = { x, y };
    return res;
}

struct vector2 vector2_add(struct vector2 v1, struct vector2 v2, double k)
{
    struct vector2 res;
    res.x = v1.x + v2.x * k;
    res.y = v1.y + v2.y * k;
    return res;
}

struct vector2 vector2_multiply(struct vector2 v1, struct vector2 v2)
{
    struct vector2 res;
    res.x = v1.x * v2.x;
    res.y = v1.y * v2.y;
    return res;
}

struct vector2 vector2_scale(struct vector2 vector, double k)
{
    struct vector2 res;
    res.x = vector.x * k;
    res.y = vector.y * k;
    return res;
}

double vector2_norm(struct vector2 v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}
