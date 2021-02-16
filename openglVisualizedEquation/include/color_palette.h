#ifndef COLOR_PALETTE_H
#define COLOR_PALETTE_H

#include <string>
#include <locale>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <filesystem>

struct color
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

struct color_double
{
	double r;
	double g;
	double b;
};

//using ColorPalette = std::vector<color_double>;

class ColorPalette
{
	public:
		std::vector<color> data;
		void ToCArray(unsigned char* result);
		unsigned char * c_array();
		ColorPalette(const std::filesystem::path & file_path);
	private:
};

// Goal: convert "06" to decimal number 6
// do not accept the following strings "6."," 6","x7", "6 "
long hexadecimal_to_long(const std::string & hex_number);

unsigned char hexadecimal_to_unsigned_char(const std::string & hex_number);

color hex_triplet_to_rgb(const std::string & hex_triplet);

color_double color_to_color_double(color c);

color_double gen_linear_color_palette(float interpolant, ColorPalette palette);

ColorPalette LoadColorPalette(const std::filesystem::path & color_palette_path);

//void ColorPaletteToCArray(ColorPalette color_palette, unsigned char* result);

#endif
