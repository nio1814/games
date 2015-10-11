#ifndef GENERATOR_H
#define GENERATOR_H

#include <QIODevice>

class QAudioFormat;

class Generator : public QIODevice
{
	Q_OBJECT
public:
	Generator(QAudioFormat &format, quint64 durationUs, int sampleRate, QObject *parent = 0);
	~Generator();

signals:

public slots:

private:
	void generateData(const QAudioFormat &format, quint64 durationUs, int sampleRate);

	qint64 m_pos;
	QByteArray m_buffer;

};

#endif // GENERATOR_H
