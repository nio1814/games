#include "keys.h"

Keys::Keys()
{

}

void Keys::setKeyIndex(Keys::KeyAction action, int index)
{
	m_keyActionIndex[action] = index;
}

bool Keys::keyPressed(KeyAction action)
{
	return keyPressed(m_keyActionIndex[action]);
}

bool Keys::keyPressed(int index)
{
	return m_keyState[index];
}

void Keys::setKeyPressed(Keys::KeyAction action, bool status)
{
	int index = keyIndex(action);
	setKeyPressed(index, status);
}

void Keys::setKeyPressed(int index, bool status)
{
	m_keyState[index] = status;
}

int Keys::keyIndex(Keys::KeyAction action)
{
	return m_keyActionIndex[action];
}

