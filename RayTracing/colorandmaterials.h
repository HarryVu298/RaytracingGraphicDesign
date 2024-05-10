/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#include <vector>
#include "defs.h"

typedef dvec3 color;

const color black(0, 0, 0);
const color red(1, 0, 0);
const color green(0, 1, 0);
const color blue(0, 0, 1);
const color magenta(1, 0, 1);
const color yellow(1, 1, 0);
const color cyan(0, 1, 1);
const color white(1, 1, 1);
const color gray(0.5, 0.5, 0.5);
const color lightGray(0.8, 0.8, 0.8);
const color darkGray(0.3, 0.3, 0.3);
const color paleGreen(0.75, 1.0, 0.76);
/**
 * @struct	Material
 * @brief	Represents all the material information.
 */

struct Material {
	color ambient;		//!< ambient material property
	color diffuse;		//!< diffuse material property
	color specular;		//!< specular material property
	double shininess;	//!< shininess material property

	Material() : Material(black, black, black, 0.0) {}
	Material(const color& amb, const color& diff,
		const color& spec, double shininess);
	Material(const vector<double>& C);
	Material(const color& oneColor);

	friend Material operator *(double w, const Material& mat);
	Material operator *(double w) const;
	Material& operator +=(const Material& mat);
	Material operator +(const Material& mat) const;
};

// http://www.it.hiof.no/~borres/j3d/explain/light/p-materials.html
const Material brass(vector<double>{0.329412, 0.223529, 0.027451,
	0.780392, 0.568627, 0.113725,
	0.992157, 0.941176, 0.807843,
	27.8974});
const Material bronze(vector<double>{0.2125, 0.1275, 0.054,
	0.714, 0.4284, 0.18144,
	0.393548, 0.271906, 0.166721,
	25.6});
const Material polishedBronze(vector<double>{0.25, 0.148, 0.06475,
	0.4, 0.2368, 0.1036,
	0.774597, 0.458561, 0.200621,
	76.8});
const Material chrome(vector<double>{0.25, 0.25, 0.25,
	0.4, 0.4, 0.4,
	0.774597, 0.774597, 0.774597,
	76.8});
const Material copper(vector<double>{0.19125, 0.0735, 0.0225,
	0.7038, 0.27048, 0.0828,
	0.256777, 0.137622, 0.086014,
	12.8});
const Material polishedCopper(vector<double>{0.2295, 0.08825, 0.0275,
	0.5508, 0.2118, 0.066,
	0.580594, 0.223257, 0.0695701,
	51.2});
const Material gold(vector<double>{0.24725, 0.1995, 0.0745,
	0.75164, 0.60648, 0.22648,
	0.628281, 0.555802, 0.366065,
	51.2});
const Material polishedGold(vector<double>{0.24725, 0.2245, 0.0645,
	0.34615, 0.3143, 0.0903,
	0.797357, 0.723991, 0.208006,
	83.2});
const Material tin(vector<double>{0.105882, 0.058824, 0.113725,
	0.427451, 0.470588, 0.541176,
	0.333333, 0.333333, 0.521569,
	9.84615});
const Material silver(vector<double>{0.19225, 0.19225, 0.19225,
	0.50754, 0.50754, 0.50754,
	0.508273, 0.508273, 0.508273,
	51.2});
const Material polishedSilver(vector<double>{0.23125, 0.23125, 0.23125,
	0.2775, 0.2775, 0.2775,
	0.773911, 0.773911, 0.773911,
	89.6});
const Material blackPlastic(vector<double>{0.0, 0.0, 0.0,
	0.01, 0.01, 0.01,
	0.50, 0.50, 0.50,
	32.0});
const Material cyanPlastic(vector<double>{0.0, 0.1, 0.06,
	0.0, 0.50980392, 0.50980392,
	0.50196078, 0.50196078, 0.50196078,
	32.0});
const Material greenPlastic(vector<double>{0.0, 0.0, 0.0,
	0.1, 0.35, 0.1,
	0.45, 0.55, 0.45,
	32.0});
const Material redPlastic(vector<double>{0.0, 0.0, 0.0,
	0.5, 0.0, 0.0,
	0.7, 0.6, 0.6,
	32.0});
const Material whitePlastic(vector<double>{0.0, 0.0, 0.0,
	0.55, 0.55, 0.55,
	0.70, 0.70, 0.70,
	32.0});
const Material mysteryPlastic(vector<double>{0.0, 0.0, 0.0,
	0.25, 0.25, 0.25,
	0.00, 0.00, 0.00,
	0.0}); 
const Material yellowPlastic(vector<double>{0.0, 0.0, 0.0,
	0.5, 0.5, 0.0,
	0.60, 0.60, 0.50,
	32.0});
const Material blackRubber(vector<double>{0.02, 0.02, 0.02,
	0.01, 0.01, 0.01,
	0.4, 0.4, 0.4,
	10.0});
const Material cyanRubber(vector<double>{0.0, 0.05, 0.05,
	0.4, 0.5, 0.5,
	0.04, 0.7, 0.7,
	10.0});
const Material greenRubber(vector<double>{0.0, 0.05, 0.0,
	0.4, 0.5, 0.4,
	0.04, 0.7, 0.04,
	10.0});
const Material redRubber(vector<double>{0.05, 0.0, 0.0,
	0.5, 0.4, 0.4,
	0.7, 0.04, 0.04,
	10.0});
const Material whiteRubber(vector<double>{0.05, 0.05, 0.05,
	0.5, 0.5, 0.5,
	0.7, 0.7, 0.7,
	10.0});
const Material yellowRubber(vector<double>{0.05, 0.05, 0.0,
	0.5, 0.5, 0.4,
	0.7, 0.7, 0.04,
	10.0});
const Material pewter(vector<double>{0.105882, 0.058824, 0.113725,
	0.427451, 0.470588, 0.541176,
	0.333333, 0.333333, 0.521569,
	9.846150});

// Translucent materials - this code base does not support material alpha values
const Material emerald(vector<double>{0.0215, 0.1745, 0.0215,
	0.07568, 0.61424, 0.07568,
	0.633, 0.727811, 0.633,
	76.8});
const Material jade(vector<double>{0.135, 0.2225, 0.1575,
	0.54, 0.89, 0.63,
	0.316228, 0.316228, 0.316228,
	12.8});
const Material obsidian(vector<double>{0.05375, 0.05, 0.06625,
	0.18275, 0.17, 0.22525,
	0.332741, 0.328634, 0.346435,
	38.4});
const Material perl(vector<double>{0.25, 0.20725, 0.20725,
	1.0, 0.829, 0.829,
	0.296648, 0.296648, 0.296648,
	11.264});
const Material ruby(vector<double>{0.1745, 0.01175, 0.01175,
	0.61424, 0.04136, 0.04136,
	0.727811, 0.626959, 0.626959,
	76.8});
const Material turquoise(vector<double>{0.1, 0.18725, 0.1745,
	0.396, 0.74151, 0.69102,
	0.297254, 0.30829, 0.306678,
	12.8});
