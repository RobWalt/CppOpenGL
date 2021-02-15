#include <stdlib.h>

#include <string>
#include <locale>
#include <vector>
#include <cmath>
#include <stdexcept>
#include <filesystem>
#include <iostream>
#include <fstream>


#include "color_palette.h"


// Goal: convert "06" to decimal number 6
// do not accept the following strings "6."," 6","x7", "6 "
long hexadecimal_to_long(const std::string & hex_number)
{
	std::size_t pos;
	if ( std::isspace(hex_number[0]))
	{
		throw std::runtime_error("hex_number has leading white space");
	}
	const long result = std::stol(hex_number, &pos, 16);
	if (pos < hex_number.size())
	{
		throw std::runtime_error("hex_number has trailing characters");
	}
	return result;
}

// Goal: convert "06" to decimal number 6
// do not accept the following strings "6."," 6","x7", "6 "
unsigned char hexadecimal_to_unsigned_char(const std::string & hex_number)
{
	std::size_t pos;
	if ( std::isspace(hex_number[0]))
	{
		throw std::runtime_error("hex_number has leading white space");
	}
	const unsigned char result = std::stoul(hex_number, &pos, 16);
	if (pos < hex_number.size())
	{
		throw std::runtime_error("hex_number has trailing characters");
	}
	return result;
}

color hex_triplet_to_rgb(const std::string & hex_triplet)
{
	if (hex_triplet.size() != 7)
	{
		throw std::runtime_error("hex_triplet should contain precisely 7 characters.");
	}
	if (hex_triplet[0] != '#')
	{
		throw std::runtime_error("hex_triplet should lead with number sign (#).");
	}
	unsigned char r = hexadecimal_to_unsigned_char(hex_triplet.substr(1,2));
	unsigned char g = hexadecimal_to_unsigned_char(hex_triplet.substr(3,2));
	unsigned char b = hexadecimal_to_unsigned_char(hex_triplet.substr(5,2));
	if (r < 0 || g < 0 || b < 0)
	{
		throw std::runtime_error("hex_triplet contained negative number");
	}
	return {r,g,b}; //{r, g, b, 5};
}

color_double color_to_color_double(color c)
{
	return {(1.0/255)*c.r,(1.0/255)*c.g,(1.0/255)*c.b};
}

color_double gen_linear_color_palette(float interpolant, std::vector<color_double> palette)
{
	// takes number between 0 and 1, takes closest element near from array.
	float number_between_zero_and_one = 0.5;
	std::size_t index = std::round(number_between_zero_and_one*255);
	return palette[index];
}


ColorPalette::ColorPalette(const std::filesystem::path & color_palette_path)
{
	std::fstream palette_file(color_palette_path);
	// open file 
	if (!palette_file.is_open())
	{
		throw std::runtime_error("File could not be opened. Does it exist?");
	} else {
		 std::string line{}; 

		while (std::getline(palette_file,line))
		{
			color col = hex_triplet_to_rgb(line);
			//color_double col_double = color_to_color_double(col);
			data.push_back(col);
		}
	} // close file
}


unsigned char * ColorPalette::c_array()
{
	unsigned char * result =  (unsigned char*) malloc( sizeof(unsigned char) * 3 * data.size() );

	for (auto i = 0; i < data.size(); i++)
	{
					result[i*3] = data[i].r;
					result[i*3 + 1] = data[i].g;
					result[i*3 + 2] = data[i].b;
	}

	return result;
}


void ColorPalette::ToCArray(unsigned char* result)
{

				for (auto i = 0; i < data.size(); i++)
				{
								result[i*3] = data[i].r;
								result[i*3 + 1] = data[i].g;
								result[i*3 + 2] = data[i].b;
				}
}
