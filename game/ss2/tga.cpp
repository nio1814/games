#include "tga.h"

#include <fstream>
#include <iostream>
#include <cstdio>

TGA::TGA(std::string filename)
{
//	FILE* f = fopen(filename.c_str(), "rb");
//	if(f)
//	{
//		int8_t length;
//		fread(&length, 1, sizeof(int8_t), f);
//		fseek(f, 1, SEEK_CUR);
//		int8_t type;
//		fread(&type, 1, sizeof(int8_t), f);
//		fclose(f);
//	}
//	else
//	{
//		std::cerr << "error";
//	}

	std::ifstream file;
	file.open(filename, std::ios_base::in | std::ios_base::binary);
	if(file.is_open())
	{
		int8_t length;
//		file >> length;
		file.read(reinterpret_cast<char*>(&length), sizeof(int8_t));
		file.ignore(1);
		int8_t type;
//		file >> type;
		file.read(reinterpret_cast<char*>(&type), sizeof(int8_t));
		file.ignore(9);
		uint8_t bits;
//		file >> m_width >> m_height >> bits;
		file.read(reinterpret_cast<char*>(&m_width), sizeof(short));
		file.read(reinterpret_cast<char*>(&m_height), sizeof(short));
		file.read(reinterpret_cast<char*>(&bits), sizeof(uint8_t));
		file.ignore(length+1);

		int stride;
		if(type == RLE)
		{
			uint8_t rleID = 0;
//			int colorsRead = 0;
			m_channels = bits/8;
			stride = m_channels*m_width;
//			m_data.resize(stride*m_height);
			m_data.clear();
			std::vector<uint8_t> pixelColors(m_channels);
			uint8_t* pixelColorsData = pixelColors.data();

			int i=0;
			while(i<m_width*m_height)
			{
//				file >> rleID;
				file.read(reinterpret_cast<char*>(&rleID), sizeof(uint8_t));
				if(rleID<128)
				{
					rleID++;
					while(rleID)
					{
						file.read(reinterpret_cast<char*>(pixelColorsData), m_channels*sizeof(uint8_t));
//						for (uint8_t& color : pixelColors)
//							file >> color;

						m_data.push_back(pixelColors[2]);
						m_data.push_back(pixelColors[1]);
						m_data.push_back(pixelColors[0]);

						if(bits==32)
							m_data.push_back(pixelColors[3]);

						i++;
						rleID--;
					}
				}
				else
				{
					rleID -= 127;
					file.read(reinterpret_cast<char*>(pixelColorsData), m_channels*sizeof(uint8_t));
//					for (uint8_t& color : pixelColors)
//						file >> color;
					while(rleID)
					{
						m_data.push_back(pixelColors[2]);
						m_data.push_back(pixelColors[1]);
						m_data.push_back(pixelColors[0]);

						if(bits==32)
							m_data.push_back(pixelColors[3]);

						i++;
						rleID--;
					}
				}
			}
		}
		else
		{
			switch (bits)
			{
				case 24:
				case 32:
					{
						m_channels = bits/8;
						stride = m_channels*m_width;
						m_data.resize(stride*m_height);
						unsigned char* data = m_data.data();
						for(int y=0; y<m_height; y++)
						{
							unsigned char* pixelLine = &data[stride*y];
							file.read(reinterpret_cast<char*>(pixelLine), stride);
//							for (int n=0; n<stride; n++)
//								file >> pixelLine[n];
							for (int i=0; i<stride; i+=m_channels)
							{
								std::swap(pixelLine[i], pixelLine[i+2]);
							}
						}
					}
					break;
				case 16:
					{
						unsigned short pixels = 0;
						m_channels = 3;
						stride = m_channels*m_width;
						m_data.resize(stride*m_height);
						for(int i=0; i<m_width*m_height; i++)
						{
							file >> pixels;
							int blue = (pixels & 0x1f) << 3;
							int green = ((pixels>>5) & 0x1f) << 3;
							int red = ((pixels>>10) & 0x1f) << 3;

							m_data[i*3] = red;
							m_data[i*3+1] = green;
							m_data[i*3+2] = blue;
						}
					}
					break;
				default:
					std::cerr << "Read invalid number of bits " << bits << std::endl;
//					break;
			}
		}

		file.close();
	}
	else
		std::cerr << "Failed to open " << filename << std::endl;
}

int TGA::channels()
{
	return m_channels;
}

short TGA::width()
{
	return m_width;
}

short TGA::height()
{
	return m_height;
}

unsigned char *TGA::data()
{
	return m_data.data();
}

