#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>

#include <noteface/mididevice.h>

namespace Ui {
class MainWindow;
}

enum State {
    S_Off = 0,
    S_On,
    S_Closed
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void start();
    void timerShot();

private:
    Ui::MainWindow *ui;
    QTimer m_timer;
    int m_notePitch;
    int m_noteVelocity;
    int m_duration;
    int m_pause;
    int m_count;
    State m_state;
    alisemidi::MidiDevice m_midi;
};

#endif // MAINWINDOW_H
