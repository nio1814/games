#ifndef TextureLoader_H
#define TextureLoader_H

#include <vector>
#include <string>
#include <map>

class TextureLoader
{
public:
	TextureLoader();

	std::vector<unsigned int> load(std::vector<std::string> filenames);
private:
	std::map<std::string, uint> m_IDs;
};

#endif // TextureLoader_H
