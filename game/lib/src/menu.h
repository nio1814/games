#ifndef MENU
#define MENU

#include <string.h>

#include "datastructs.h"
//#include "text.h"

class menuTree : public NodeClass<void*>
{
	public:
//	font_s* font;
//	font3d_s* font3d;
	
	menuTree();
	//~menuTree();

	virtual void addLeaf(void* input, dataType tp, string name);
	void runKeys();
	void display();
};

#endif
