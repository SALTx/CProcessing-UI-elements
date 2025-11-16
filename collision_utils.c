#include "shape_utils.h"

int pointInRect(Point point, Quad rect) {
	int xOverlap = (point.x > rect.position.x) && (point.x < (rect.position.x + rect.width));
	int yOverlap = (point.y >= rect.position.y) && (point.y <= (rect.position.y + rect.height));

	return xOverlap && yOverlap;
}