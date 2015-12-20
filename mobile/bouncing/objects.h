#ifndef OBJECTS_H
#define OBJECTS_H

#include <qvector.h>

class QOpenGLShaderProgram;

template <class T>
class Objects
{
public:
	void draw(QOpenGLShaderProgram* program)
	{
		for(int a=0; a<m_objs.size(); a++)
		{
			if(m_objs[a]->doDraw())
				m_objs[a]->draw(program);
		}

		return;
	}

	int size() const
	{
		return m_objs.size();
	}

private:
	QVector<T*> m_objs;
};

#endif // OBJECTS_H
