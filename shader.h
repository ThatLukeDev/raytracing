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

	virtual color getPixel(color _influence) {
		double refl = reflectance;
		double inverserefl = 1.0 - reflectance;

		color output = shade * emission * inverserefl + _influence * refl;
		output.R *= (_influence.R * inverserefl / 255.999) + 1.0;
		output.G *= (_influence.G * inverserefl / 255.999) + 1.0;
		output.B *= (_influence.B * inverserefl / 255.999) + 1.0;

		return output;
	}
};

#endif
