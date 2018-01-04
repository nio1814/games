#include "textureloader.h"

#include "tga.h"
#include "qtgl.h"

std::string getFileExtension(std::string filename)
{
	int lastPeriodIndex = filename.find_last_of('.');

	return filename.substr(lastPeriodIndex+1, filename.size());
}

TextureLoader::TextureLoader()
{

}

std::vector<unsigned int> TextureLoader::load(std::vector<std::string> filenames)
{
	int numImages = filenames.size();
	std::vector<unsigned int> indices(numImages);
	glGenTextures(numImages, indices.data());

	for(int n=0; n<numImages; n++)
	{
		glBindTexture(GL_TEXTURE_2D,  indices[n]);

		std::string filename = filenames[n];
		std::string extension = getFileExtension(filename);
		if(extension=="tga")
		{
			TGA tga(filename);
			int textureType = tga.channels()==4 ? GL_RGBA : GL_RGB;
			glTexImage2D(GL_TEXTURE_2D, 0, textureType, tga.width(), tga.height(), 0, textureType, GL_UNSIGNED_BYTE, tga.data());
		}
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	return indices;
}


