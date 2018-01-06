#ifndef KEYS_H
#define KEYS_H

#include <map>

class Keys
{
public:
	enum KeyAction{Left, Right, Jump};

	Keys();

	void setKeyIndex(KeyAction action, int index);
	bool keyPressed(KeyAction action);
	bool keyPressed(int index);
	void setKeyPressed(KeyAction action, bool status);
	void setKeyPressed(int index, bool status);

private:
	int keyIndex(KeyAction action);

	std::map<int,bool> m_keyState;
	std::map<KeyAction,int> m_keyActionIndex;
};

#endif // KEYS_H
