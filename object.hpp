#ifndef object_h
#define object_h

#include "vector3.hpp"
#include "shader.hpp"

class object {
public:
	vector3 position = vector3();
	shader texture = shader();

	object() { }
	object(vector3 _position, color _color, double _emission, double _reflectance, double _fuzz, double _transparency, double _ior)
	: position(_position), texture(_color, _emission, _reflectance, _fuzz, _transparency, _ior) { }

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
