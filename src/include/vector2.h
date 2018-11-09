#ifndef VECTOR_H
#define VECTOR_H

struct vector2
{
  float x;
  float y;
};

void vector2_init(struct vector2 *v, float x, float y);
void vector2_add(struct vector2 *v, struct vector2 v1, struct vector2 v2, float k);
void vector2_scale(struct vector2 *vector, float k);
void vector2_multiply(struct vector2 *v, struct vector2 v1, struct vector2 v2);
void vector2_cpy(struct vector2 *v1, struct vector2 v2);
void vector2_normalize(struct vector2 *v);
float vector2_len(struct vector2 v);

#endif /*VECTOR2_H_*/
