#ifndef shader_h
#define shader_h

class shader {
public:
	color shade = color();
	double emission = 0.0;
	double reflectance = 0.0;
	double fuzz = 0.0;
	double transparency = 0.0;

	shader() { }
	shader(color _color, double _emission, double _reflectance, double _fuzz, double _transparency)
	: shade(_color), emission(_emission), reflectance(_reflectance), fuzz(_fuzz), transparency(_transparency) { }
};

#endif
