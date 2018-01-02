#include "tga.h"

#include <fstream>
#include <iostream>

TGA::TGA(std::string filename)
{
	std::ifstream file;
	file.open(filename);
	if(file.is_open())
	{
		int8_t length;
		file >> length;
		file.ignore(1);
		int8_t type;
		file >> type;
		file.ignore(9);
		uint8_t bits;
		file >> m_width >> m_height >> bits;
		file.ignore(length+1);

		int channels;
		int stride;
		if(type == RLE)
		{
			uint8_t rleID = 0;
//			int colorsRead = 0;
			channels = bits/8;
			stride = channels*m_width;
//			m_data.resize(stride*m_height);
			m_data.clear();
			std::vector<uint8_t> pixelColors(channels);
//			uint8_t* pixelColorsData = pixelColors.data();

			int i=0;
			while(i<m_width*m_height)
			{
				file >> rleID;
				if(rleID<128)
				{
					rleID++;
					while(rleID)
					{
//						file.read(pixelColorsData, channels*sizeof(uint8_t));
						for (uint8_t& color : pixelColors)
							file >> color;

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
//					file.read(pixelColorsData, channels*sizeof(uint8_t));
					for (uint8_t& color : pixelColors)
						file >> color;
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
			switch (bits) {
				case 24:
				case 32:
					{
						channels = bits/8;
						stride = channels*m_width;
						m_data.resize(stride*m_height);
						unsigned char* data = m_data.data();
						for(int y=0; y<m_height; y++)
						{
							unsigned char* pixelLine = &data[stride*y];
//							file.read(pixelLine, stride);
							for (int n=0; n<stride; n++)
								file >> pixelLine[n];
							for (int i=0; i<stride; i+=channels)
							{
								std::swap(pixelLine[i], pixelLine[i+2]);
							}
						}
					}
					break;
				case 16:
					{
						unsigned short pixels = 0;
						channels = 3;
						stride = channels*m_width;
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
//				default:
//					break;
			}
		}

		file.close();
	}
	else
		std::cerr << "Failed to open " << filename;
}

