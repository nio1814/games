#include "textureloader.h"

#include "tga.h"
#include "qtgl.h"
#include <iostream>

std::string getFileExtension(std::string filename)
{
	int lastPeriodIndex = filename.find_last_of('.');

	return filename.substr(lastPeriodIndex+1, filename.size());
}

TextureLoader::TextureLoader()
{

}

std::vector<std::shared_ptr<Frame> > TextureLoader::load(std::vector<std::string> filenames)
{
	int numImages = filenames.size();
	std::vector<std::shared_ptr<Frame> > frames;
	std::vector<unsigned int> indices(numImages);
	glEnable(GL_TEXTURE_2D);
	glGenTextures(numImages, indices.data());
	std::cerr << glGetError() << std::endl;
	for(int n=0; n<numImages; n++)
	{
		frames.push_back(std::make_shared<Frame>());
		frames.back()->textureIndex = indices[n];
		glBindTexture(GL_TEXTURE_2D,  indices[n]);

		std::string filename = filenames[n];
		std::string extension = getFileExtension(filename);
		if(extension=="tga")
		{
			TGA tga(filename);
			int textureType = tga.channels()==4 ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, textureType, tga.width(), tga.height(), 0, textureType, GL_UNSIGNED_BYTE, tga.data());
			frames.back()->width = tga.width();
			frames.back()->height = tga.height();
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//	std::cerr << glGetError() << std::endl;

	return frames;
}


