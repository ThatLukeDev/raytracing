#ifndef object_h
#define object_h

#include "vector3.h"

class object {
public:
	vector3 position;
	color shade = color();
	double emission;
	double reflectance;
	double transparency;

	object() { }
	object(vector3 _position, color _color, double _emission, double _radius, double _transparency)
	: position(_position), shade(_color), emission(_emission), reflectance(_radius), transparency(_transparency) { }

	virtual double intersectsAlong(ray r) = 0;
	bool intersects(ray r) {
		if (intersectsAlong(r) != -1) {
			return true;
		}
		return false;
	}
};

#endif
