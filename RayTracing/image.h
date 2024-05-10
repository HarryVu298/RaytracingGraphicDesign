/****************************************************
 * 2016-2023 Eric Bachmann and Mike Zmuda
 * All Rights Reserved.
 * NOTICE:
 * Dissemination of this information or reproduction
 * of this material is prohibited unless prior written
 * permission is granted.
 ****************************************************/

#pragma once
#include <memory>
#include "defs.h"
#include "colorandmaterials.h"

 /**
  * @struct	Image
  * @brief	Represents a rectangular RGB image.
  */

struct Image {
	int W, H;
	color* pixels;
	Image(std::string ppmFileName);
	~Image() { delete[] pixels; }
	color getPixelUV(double u, double v) const;
};
