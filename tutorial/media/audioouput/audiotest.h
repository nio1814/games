#ifndef AUDIOTEST_H
#define AUDIOTEST_H

#include <QMainWindow>
#include <qaudioformat.h>

class QComboBox;
class Generator;

class AudioTest : public QMainWindow
{
	Q_OBJECT

public:
	AudioTest();
	~AudioTest();

private:
	void initializeWindow();
	void initializeAudio();
	void createAudioOutput();

	QComboBox* m_deviceBox;
	Generator* m_generator;
	QAudioFormat m_format;
};

#endif // AUDIOTEST_H
