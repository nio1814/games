#include "audiotest.h"

#include <QVBoxLayout>
#include <qcombobox.h>
#include <qaudiodeviceinfo.h>

#include "generator.h"

AudioTest::AudioTest()
	: m_deviceBox(0)
{
	initializeWindow();
}

AudioTest::~AudioTest()
{
	delete m_generator;
}

void AudioTest::initializeWindow()
{
	QScopedPointer<QWidget> window(new QWidget);
	QScopedPointer<QVBoxLayout> layout(new QVBoxLayout);

	m_deviceBox = new QComboBox(this);
	const QAudioDeviceInfo &defaultDeviceInfo = QAudioDeviceInfo::defaultOutputDevice();
	m_deviceBox->addItem(defaultDeviceInfo.deviceName(), qVariantFromValue(defaultDeviceInfo));
	foreach(const QAudioDeviceInfo &deviceInfo, QAudioDeviceInfo::availableDevices(QAudio::AudioOutput))
	{
#if QT_VERSION > 0x040806
		if(deviceInfo != defaultDeviceInfo)
#else
        if(deviceInfo.deviceName()!=defaultDeviceInfo.deviceName())
#endif
			m_deviceBox->addItem(deviceInfo.deviceName(), qVariantFromValue(deviceInfo));
	}

	layout->addWidget(m_deviceBox);

	window->setLayout(layout.data());
	layout.take();

	setCentralWidget(window.data());
	QWidget* const windowPtr = window.take();
	windowPtr->show();

	return;
}

void AudioTest::initializeAudio()
{
	int durationSeconds = 1;
	int toneSampleRateHz = 600;
//	int dataSampleRateHz = 44100;
//	int bufferSize      = 32768;

//	m_generator = new Generator(m_format, durationSeconds*1e6, toneSampleRateHz, this);

	return;
}

void AudioTest::createAudioOutput()
{

}
