#pragma once

#include <QString>
#include <QObject>
#include <QScopedPointer>

#undef COMPILING_DLL
#ifdef NOTEFACE_DLL
    #define COMPILING_DLL
#endif
#include <dllapi.h>

class RtMidiOut;

namespace alisemidi {

class DLL_API MidiDevice: QObject
{
    Q_OBJECT
public:
    MidiDevice(QObject *parent = NULL);
    ~MidiDevice();

    bool open(const QString _portName = QString());
    bool open(const int _portNumber);
    bool close();

    QString lastError() const;

public slots:
    //void setVolume(const unsigned char _volume);
    void noteOn(const unsigned char _pitch, const unsigned char _velocity, unsigned char _port = 0);
    void noteOff(const unsigned char _pitch, const unsigned char _velocity, unsigned char _port = 0);

protected:
    void setErrorText(const QString &_text);
    RtMidiOut* rawMidi();

private:
    QScopedPointer<RtMidiOut> m_out;
    QString m_error;
};

}
