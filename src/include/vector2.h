#ifndef VECTOR_H
#define VECTOR_H

struct vector2
{
  double x;
  double y;
};

struct vector2 vector2_init(double x, double y);
struct vector2 vector2_add(struct vector2 v1, struct vector2 v2, double k);
struct vector2 vector2_scale(struct vector2 vector, double k);
struct vector2 vector2_multiply(struct vector2 v1, struct vector2 v2);
double vector2_norm(struct vector2 v);

#endif /*VECTOR2_H_*/
