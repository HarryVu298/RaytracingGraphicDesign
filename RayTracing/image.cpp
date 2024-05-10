/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#include <iostream>
#include <fstream>
#include <utility>
#include <set>
#include "utilities.h"
#include "image.h"

static unsigned int getNextChar(std::ifstream& input, string& str) {
	const int N = 2000;
	char buf;
	input.read(&buf, 1);
	unsigned int result = (unsigned char)buf;
	return result;
}

static void p3(std::ifstream& input, Image& im) {
	const int N = 100;
	char buf[N + 1];

	int maxValue;
	input >> im.W >> im.H >> maxValue;
	input.getline(buf, N);

	im.pixels = new color[im.W * im.H];
	color* p = im.pixels;
	for (int row = 0; row < im.H; row++) {
		for (int col = 0; col < im.W; col++, p++) {
			int r, g, b;
			input >> r >> g >> b;
			double R = map((double)r, 0.0, (double)maxValue, 0.0, 1.0);
			double G = map((double)g, 0.0, (double)maxValue, 0.0, 1.0);
			double B = map((double)b, 0.0, (double)maxValue, 0.0, 1.0);
			*p = color(R, G, B);
		}
	}
}

static void p6(std::ifstream& input, Image& im) {
	const int N = 100;
	char buf[N + 1];

	int maxValue;
	input >> im.W >> im.H >> maxValue;
	input.getline(buf, N);

	im.pixels = new color[im.W * im.H];
	string buffer;
	color* p = im.pixels;
	for (int row = 0; row < im.H; row++) {
		for (int col = 0; col < im.W; col++, p++) {
			int r, g, b;
			r = getNextChar(input, buffer);
			g = getNextChar(input, buffer);
			b = getNextChar(input, buffer);
			double R = map((double)r, 0.0, (double)maxValue, 0.0, 1.0);
			double G = map((double)g, 0.0, (double)maxValue, 0.0, 1.0);
			double B = map((double)b, 0.0, (double)maxValue, 0.0, 1.0);
			*p = color(R, G, B);
		}
	}
}

/**
 * @fn	Image::Image(char *ppmFileName)
 * @brief	Constructs and image given the name of a PPM file. The file must be
 * 			P3 or P6.
 * @param [in,out]	ppmFileName	Filename of the ppm file.
 */

Image::Image(std::string ppmFileName) : W(0), H(0) {
	const int N = 100;
	char buf1[N + 1];
	char buf2[N + 1];
	std::ifstream input(ppmFileName.c_str(), std::ios::binary);
	input.getline(buf1, N);
	int type = 3;
	pixels = nullptr;

	while (input.peek() == '#') {
		input.getline(buf2, N);
	}
	string header(buf1);
	header = header.substr(0, 2);
	if (header == "P3") {
		p3(input, *this);
	} else if (header == "P6") {
		p6(input, *this);
	} else {
		std::cerr << "Problem with PPM file: " << ppmFileName << "(" << header << ")" << endl;
		return;
	}

	input.close();
}

/**
 * @fn	color Image::getPixelUV(double u, double v) const
 * @brief	Gets the color that corresponds to the coordinate (u, v). This is
 * 			done by finding the texel whose center is closest to (u, v). In the
 * 			event of a tie, picks one of these.
 * @param	u	The u in (u, v).
 * @param	v	The v in (u, v).
 * @return	The color corresponding to the position (u, v).
 */

color Image::getPixelUV(double u, double v) const {
	int x = glm::clamp((int)(W * u), 0, W - 1);
	int y = glm::clamp((int)(H * v), 0, H - 1);
	return pixels[y * W + x];
}
