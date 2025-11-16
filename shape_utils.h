#ifndef SHAPE_UTILS_H
#define SHAPE_UTILS_H

typedef struct {
	float x;
	float y;
} Point;

typedef struct {
	Point position;
	float width;
	float height;
} Quad;

typedef struct {
	Point center;
	float radius;
} Circle;

#endif // SHAPE_UTILS_H
