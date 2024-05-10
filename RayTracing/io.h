#pragma once

#include <sstream>
#include <iostream>
#include <istream>
#include <fstream>
#include <iomanip>
#include "light.h"
#include "colorandmaterials.h"
#include "ishape.h"

std::string getLine(std::istream& in);

bool ae(double a, double b);
bool ave(const dvec2& v1, const dvec2& v2);
bool ave(const dvec3& v1, const dvec3& v2);

bool equal(double a, double b);

bool equal(int a, int b);

bool equal(bool a, bool b);

bool equal(dvec2 a, dvec2 b);

bool equal(const glm::ivec2& a, const glm::ivec2& b);

bool equal(const glm::ivec3& a, const glm::ivec3& b);

bool equal(const dvec3& a, const dvec3& b);

ostream& operator << (ostream& os, const Material& mat);
istream& operator >> (std::istream& is, Material& mat);

ostream& operator << (ostream& os, const Frame& frame);

ostream& operator << (ostream& os, const PositionalLight& pl);
ostream& operator << (ostream& os, const SpotLight& pl);

ostream& operator << (ostream& os, const LightATParams& params);
istream& operator >> (std::istream& is, LightATParams& params);

template <class T>
bool ave(const vector<T>& v1, const vector<T>& v2) {
	if (v1.size() != v2.size())
		return false;
	for (int i = 0; i < v1.size(); i++)
		if (!equal(v1[i], v2[i]))
			return false;
	return true;
}

bool equal(const vector<dvec3>&, const vector<dvec3>&);

char nextChar(istream& is);

bool equal(const dmat4& a, const dmat4& b);

// Simple streaming for vectors and matrices.
istream& operator >> (istream& os, glm::ivec2& V);
ostream& operator << (ostream& os, const glm::ivec2& V);
istream& operator >> (istream& os, dvec2& V);
ostream& operator << (ostream& os, const dvec2& v);

ostream& operator << (ostream& os, const dvec3& v);
istream& operator >> (istream& os, dvec3& V);
istream& operator >> (istream& os, dvec4& V);

ostream& operator << (ostream& os, const dvec4& v);
ostream& operator << (ostream& os, const dmat2& v);
ostream& operator << (ostream& os, const dmat3& v);
istream& operator >> (istream& is, dmat3& v);
ostream& operator << (ostream& os, const dmat4& v);
istream& operator >> (istream& is, dmat4& v);

template <class T>
ostream& operator << (ostream& os, const vector<T>& V) {
	os << "[" << endl;
	for (size_t i = 0; i < V.size(); i++) {
		os << '\t' << V[i] << endl;
	}
	os << "] ";
	return os;
}

template <class T>
istream& operator >> (istream& is, vector<T>& vec) {
	vec.clear();
	char ch;
	is >> ch;
	while (nextChar(is) != ']') {
		T value;
		is >> value;
		vec.push_back(value);
	}
	is >> ch;
	return is;
}