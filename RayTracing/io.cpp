#include "defs.h"
#include "io.h"

std::string getLine(std::istream& in) {
	const int BUFLEN = 1000;
	char buf[BUFLEN + 1];
	in.getline(buf, BUFLEN);
	return std::string(buf);
}

char nextChar(istream& is) {
	while (iswspace(is.peek())) {
		is.get();
	}
	return is.peek();
}

bool ae(double a, double b) {
	return glm::abs(a - b) <= 0.01;
}
bool ave(const dvec2& v1, const dvec2& v2) {
	return ae(v1.x, v2.x) && ae(v1.y, v2.y);
}
bool ave(const dvec3& v1, const dvec3& v2) {
	return ae(v1.x, v2.x) && ae(v1.y, v2.y) && ae(v1.z, v2.z);
}

bool equal(double a, double b) { return ae(a, b); }
bool equal(int a, int b) { return a == b; }
bool equal(bool a, bool b) { return a == b; }
bool equal(dvec2 a, dvec2 b) { return ave(a, b); }
bool equal(const glm::ivec2& a, const glm::ivec2& b) { return a == b; }
bool equal(const glm::ivec3& a, const glm::ivec3& b) { return a == b; }
bool equal(const dvec3& a, const dvec3& b) { return ave(a, b); }

ostream& operator << (ostream& os, const Material& mat) {
	os << mat.ambient << ' ' << mat.diffuse << ' ' << mat.specular << ' ' << mat.shininess;
	return os;
}

istream& operator >> (std::istream& is, Material& mat) {
	is >> mat.ambient >> mat.diffuse >> mat.specular >> mat.shininess;
	return is;
}

//ostream& operator << (ostream& os, const IPlane& plane) {
//	os << plane.a << ' ' << plane.n;
//	return os;
//}
//
//istream& operator >> (std::istream& is, IPlane& plane) {
//	is >> plane.a >> plane.n;
//	return is;
//}

//ostream& operator << (ostream& os, const Ray& ray) {
//	os << ray.origin << ' ' << ray.dir;
//	return os;
//}
//
//istream& operator >> (std::istream& is, Ray& ray) {
//	is >> ray.origin >> ray.dir;
//	return is;
//}

//ostream& operator << (ostream& os, const LightColor& L) {
//	os << "[ " << L.ambient << ' ' << L.diffuse << ' ' << L.specular << " ]";
//	return os;
//}
//
//istream& operator >> (std::istream& is, LightColor& L) {
//	char ch;
//	is >> ch >> L.ambient >> L.diffuse >> L.specular >> ch;
//	return is;
//}


/**
* @fn	ostream &operator << (ostream &os, const LightAttenuationParameters &at)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	at		Attenuation parameters.
* @return	The output stream.
*/

ostream& operator << (ostream& os, const LightATParams& at) {
	os << dvec3(at.constant, at.linear, at.quadratic);
	return os;
}

istream& operator >> (std::istream& is, LightATParams& params) {
	dvec3 atParams;
	is >> atParams;
	params.constant = atParams[0];
	params.linear = atParams[1];
	params.quadratic = atParams[2];
	return is;
}

bool equal(const dmat4& a, const dmat4& b) {
	for (int r = 0; r < 4; r++)
		for (int c = 0; c < 4; c++)
			if (!ae(a[c][r], b[c][r]))
				return false;
	return true;
}
/**
* @fn	ostream &operator << (ostream &os, const dvec2 &V)
* @brief	Output stream for vec2.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream& operator << (ostream& os, const dvec2& V) {
	os << "[ " << V.x << " " << V.y << " ]";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dvec3 &V)
* @brief	Output stream for vec3.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream& operator << (ostream& os, const dvec3& V) {
	os << std::setprecision(10);
	os << "[ " << V.x << " " << V.y << " " << V.z << " ]";
	return os;
}

bool equal(const vector<dvec3>& v1, const vector<dvec3>& v2) {
	if (v1.size() != v2.size())
		return false;
	for (int i = 0; i < v1.size(); i++) {
		if (!ave(v1[i], v2[i]))
			return false;
	}
	return true;
}
istream& operator >> (istream& is, glm::ivec2& V) {
	char ch1, ch2;
	is >> ch1 >> V.x >> V.y >> ch2;
	return is;
}
ostream& operator << (ostream& os, const glm::ivec2& V) {
	os << std::setprecision(0);
	os << "[ " << V.x << " " << V.y << " ]";
	return os;
}

istream& operator >> (istream& is, dvec2& V) {
	char ch;
	is >> ch >> V.x >> V.y >> ch;
	return is;
}
istream& operator >> (istream& is, dvec3& V) {
	char ch;
	is >> ch >> V.x >> V.y >> V.z >> ch;
	return is;
}
istream& operator >> (istream& is, dvec4& V) {
	char ch;
	is >> ch >> V.x >> V.y >> V.z >> V.w >> ch;
	return is;
}

/**
* @fn	ostream &operator << (ostream &os, const dvec4 &V)
* @brief	Output stream for vec4.
* @param	os		Output stream.
* @param	V		The vector.
*/

ostream& operator << (ostream& os, const dvec4& V) {
	os << "[ " << V.x << " " << V.y << " " << V.z << " " << V.w << " ]";
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat3 &M)
* @brief	Output stream for mat3.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream& operator << (ostream& os, const dmat2& M) {
	const int N = 2;
	os << "[ ";
	for (int row = 0; row < N; row++) {
		os << dvec2(M[0][row], M[1][row]) << endl;
	}
	os << "] ";
	return os;
}

istream& operator >> (istream& is, dmat2& M) {
	const int N = 2;
	dvec3 R[N];
	char ch1, ch2;
	is >> ch1 >> R[0] >> R[1] >> ch2;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			M[col][row] = R[row][col];
		}
	}
	return is;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat3 &M)
* @brief	Output stream for mat3.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream& operator << (ostream& os, const dmat3& M) {
	const int N = 3;
	os << "[ ";
	for (int row = 0; row < N; row++) {
		os << dvec3(M[0][row], M[1][row], M[2][row]) << endl;
	}
	os << "] ";
	return os;
}

istream& operator >> (istream& is, dmat3& M) {
	const int N = 3;
	dvec3 R[N];
	char ch1, ch2;
	is >> ch1 >> R[0] >> R[1] >> R[2] >> ch2;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			M[col][row] = R[row][col];
		}
	}
	return is;
}

/**
* @fn	ostream &operator << (ostream &os, const dmat4 &M)
* @brief	Output stream for mat4.
* @param	os		Output stream.
* @param	M		The matrix.
*/

ostream& operator << (ostream& os, const dmat4& M) {
	const int N = 4;
	os << "[ ";
	for (int row = 0; row < N; row++) {
		os << dvec4(M[0][row], M[1][row], M[2][row], M[3][row]) << endl;
	}
	os << "] ";
	return os;
}

istream& operator >> (istream& is, dmat4& M) {
	const int N = 4;
	dvec4 R[N];
	char ch1, ch2;
	is >> ch1 >> R[0] >> R[1] >> R[2] >> R[3] >> ch2;
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			M[col][row] = R[row][col];
		}
	}
	return is;
}

/**
* @fn	ostream &operator << (ostream &os, const Frame &frame)
* @brief	Output stream operator for Frame object
* @param 	os	Output stream.
* @param	frame	Frame to stream.
*/

ostream& operator << (ostream& os, const Frame& frame) {
	os << "Pos: " << frame.origin << endl;
	os << "U: " << frame.u << endl;
	os << "V: " << frame.v << endl;
	os << "W: " << frame.w << endl;
	return os;
}


/**
* @fn	ostream &operator << (ostream &os, const PositionalLight &pl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	pl		Positional light.
* @return	The output stream.
*/

ostream& operator << (ostream& os, const PositionalLight& pl) {
	os << (pl.isOn ? "ON" : "OFF") << endl;
	os << (pl.isTiedToWorld ? "WORLD" : "CAMERA") << endl;
	os << " position " << pl.pos << endl;
	os << " color " << pl.lightColor << endl;
	os << "Attenuation: " << (pl.attenuationIsTurnedOn ? "ON" : "OFF")
		<< " " << pl.atParams << endl;
	return os;
}

/**
* @fn	ostream &operator << (ostream &os, const SpotLight &sl)
* @brief	Output stream for light attenuation parameters.
* @param	os		Output stream.
* @param	sl		Spotlight.
* @return	The output stream.
*/

ostream& operator << (ostream& os, const SpotLight& sl) {
	PositionalLight pl = (sl);
	os << pl;
	os << " FOV " << sl.fov << endl;
	return os;
}
