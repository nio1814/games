#ifndef TextureLoader_H
#define TextureLoader_H

#include "frame.h"

#include <vector>
#include <string>
#include <map>
#include <memory>

class TextureLoader
{
public:
	TextureLoader();

	std::vector<std::shared_ptr<Frame> > load(std::vector<std::string> filenames);
private:
	std::map<std::string, uint> m_IDs;
};

#endif // TextureLoader_H
