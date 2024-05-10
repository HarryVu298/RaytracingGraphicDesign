/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include "utilities.h"
#include "colorandmaterials.h"

 /**
  * @fn	Material::Material(const color &amb, const color &diff, const color &spec, double S)
  * @brief	Construct a Materials based on the basic color and shinieness values.
  * @param	amb			Ambient
  * @param	diff		Diffuse
  * @param	spec		Specular
  * @param	S	        Shinieness
  */

Material::Material(const color& amb,
	const color& diff,
	const color& spec, double S) {
	ambient = amb;
	diffuse = diff;
	specular = spec;
	shininess = S;
}

/**
 * @fn	Material::Material(const vector<double> &C)
 * @brief	Construct a Materials based on the basic color and shinieness values.
 * @param	C			Vector holding 10 values: ambient, diffuse, specular, shinieness
 */

Material::Material(const vector<double>& C) :
	Material(color(C[0], C[1], C[2]),
		color(C[3], C[4], C[5]),
		color(C[6], C[7], C[8]),
		C[9]) {
}

/**
 * @fn	Material::Material(const color &oneColor)
 * @brief	Constructs a material that has ambient values only. Diffuse and specular are black.
 *          This really should not be frequently used for opaque objects, since the object will
 *          not have any shading. Its main purpose is to support transparent objects.
 * @param	oneColor	Ambient values
 */

Material::Material(const color& oneColor) {
	ambient = oneColor;
	diffuse = specular = black;
	shininess = 0.0;
}

/**
 * @fn	Material operator*(double w) const
 * @brief	Multiply a Material by a scalar value.
 * @param	w	Weight of multiplication.
 * @return	The Material resulting from multiplying the given Material by the given weight.
 */

Material Material::operator *(double w) const {
	Material result = *this;
	result.ambient *= w;
	result.diffuse *= w;
	result.specular *= w;
	return result;
}

/**
 * @fn	Material &Material::operator+=(const Material &mat)
 * @brief	Add in a second material.
 * @param	mat	The second Material.
 * @return	The revised Material.
 */

Material& Material::operator +=(const Material& mat) {
	Material result = *this;
	ambient += mat.ambient;
	diffuse += mat.diffuse;
	specular += mat.specular;
	return *this;
}

/**
 * @fn	Material Material::operator+(const Material &mat) const
 * @brief	Adds two Materials
 * @param	mat	The second Material.
 * @return	The sum of two Materials.
 */

Material Material::operator +(const Material& mat) const {
	Material result = *this;
	result.ambient += mat.ambient;
	result.diffuse += mat.diffuse;
	result.specular += mat.specular;
	return result;
}

/**
 * @fn	Material operator*(double w, const Material &mat)
 * @brief	Multiply a Material and a scalar.
 * @param	w  	The scalar multiplicand
 * @param	mat	Material
 * @return	The original material multiplied by given weight.
 */

Material operator *(double w, const Material& mat) {
	return mat * w;
}