#ifndef TGA_H
#define TGA_H

#include <string>
#include <vector>

class TGA
{
public:
	enum Type{RLE=10};

	TGA(std::string filename);

private:
	short m_width;
	short m_height;
	std::vector<unsigned char> m_data;
};

#endif // TGA_H
