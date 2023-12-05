#ifndef object_h
#define object_h

#include "vector3.h"

class object {
public:
	vector3 position = vector3();
	color shade = color();
	double emission = 0.0;
	double reflectance = 0.0;
	double transparency = 0.0;

	object() { }
	object(vector3 _position, color _color, double _emission, double _radius, double _transparency)
	: position(_position), shade(_color), emission(_emission), reflectance(_radius), transparency(_transparency) { }

	virtual double intersectsAlong(ray r) = 0;
	virtual vector3 normalAt(vector3 pos) = 0;
	bool intersects(ray r) {
		if (intersectsAlong(r) != -1) {
			return true;
		}
		return false;
	}
};

#endif
