#include "mididevice.h"

#include <rtmidi/RtMidi.h>

/// TODO: handle exceptions from RtMidi

const QString constNoPortsError("No ports available");

namespace alisemidi {

MidiDevice::MidiDevice(QObject *parent):
    QObject(parent),
    m_out(new RtMidiOut())
{

}

MidiDevice::~MidiDevice()
{
    close();
}

bool MidiDevice::open(const QString _portName)
{
    const int p_portCount = m_out->getPortCount();
    if ( 0 == p_portCount ) {
        m_error = constNoPortsError;
        return false;
    }

    /// TODO: check
    m_out->openPort(0, _portName.toStdString());

    return m_out->isPortOpen();
}

bool MidiDevice::open(const int _portNumber)
{
    const int p_portCount = m_out->getPortCount();
    if ( 0 == p_portCount ) {
        m_error = constNoPortsError;
        return false;
    }

    m_out->openPort( _portNumber );

    return m_out->isPortOpen();
}

bool MidiDevice::close()
{
    m_out->closePort();
    m_error.clear();
    return false == m_out->isPortOpen();
}

QString MidiDevice::lastError() const
{
    return m_error;
}

void MidiDevice::noteOn(const unsigned char _pitch, const unsigned char _velocity, unsigned char _port)
{
    static unsigned char p_portMask = (unsigned char)0x0F;
    static unsigned char p_noteOn = (unsigned char)0b10000000;
    static unsigned char p_mask = (unsigned char) 0x7F;

    std::vector<unsigned char> p_msg = {(unsigned char)(p_noteOn | (p_portMask & _port)),
                                        (unsigned char)(p_mask & _pitch),
                                        (unsigned char)(p_mask & _velocity)};
    m_out->sendMessage(&p_msg);
}

void MidiDevice::noteOff(const unsigned char _pitch, const unsigned char _velocity, unsigned char _port)
{
    static unsigned char p_portMask = (unsigned char)0x0F;
    static unsigned char p_noteOff = (unsigned char)0b10010000;
    static unsigned char p_mask = (unsigned char) 0x7F;

    std::vector<unsigned char> p_msg = {(unsigned char)(p_noteOff | (p_portMask & _port)),
                                        (unsigned char)(p_mask & _pitch),
                                        (unsigned char)(p_mask &_velocity)};
    m_out->sendMessage(&p_msg);
}

}
