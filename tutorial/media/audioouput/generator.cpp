#include "generator.h"

#include <qaudioformat.h>
#include <qmath.h>

Generator::Generator(QAudioFormat &format, quint64 durationUs, int sampleRate, QObject *parent)
	: QIODevice(parent)
{
	generateData(format, durationUs, sampleRate);
}

Generator::~Generator()
{

}


void Generator::generateData(const QAudioFormat &format, quint64 durationUs, int sampleRate)
{
	const int channelBytes = format.sampleSize()/8;
	const int sampleBytes = format.channelCount()*channelBytes;
	quint64 length = 2e6;

	m_buffer.resize(length);
	unsigned char* ptr = reinterpret_cast<unsigned char*>(m_buffer.data());
	int sampleIndex = 0;

	while(length)
	{
		const qreal x = qSin(2*M_PI*sampleRate*qreal(sampleIndex%format.sampleRate()));
		const quint8 value = static_cast<quint8>((1+x)/2*255);
		*reinterpret_cast<quint8*>(ptr) = value;

		sampleIndex++;
	}
}

