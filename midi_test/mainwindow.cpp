#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->m_startBtn, SIGNAL(clicked(bool)),  SLOT(start()) );
    connect(&m_timer, SIGNAL(timeout()), SLOT(timerShot()) );
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::start()
{
    ui->m_startBtn->setDisabled(true);

    m_count = ui->m_count->value();
    m_duration = ui->m_duration->value();
    m_notePitch = ui->m_pitch->value();
    m_noteVelocity = ui->m_velocity->value();
    m_pause = ui->m_pause->value();

    timerShot();
}

void MainWindow::timerShot()
{
    qDebug() << "shot";
                if (m_count == 0)
    {
        m_state = S_Closed;
        ui->m_startBtn->setEnabled(true);
        return;
    }

    if (S_Closed == m_state)
    {
        if (false == m_midi.open() )
        {
            qCritical() << "could't open midi " << m_midi.lastError();
            return;
        }
        m_state = S_Off;
    }

    if (S_On == m_state)
    {
        m_midi.noteOff(m_notePitch, m_noteVelocity);
        m_state = S_Off;
        m_count--;

        m_timer.start(m_pause);
    } else if (S_Off == m_state)
    {
        m_midi.noteOn(m_notePitch, m_noteVelocity);
        m_state = S_On;

        m_timer.start(m_duration);
    }

}
