#include <QHBoxLayout>
#include "counterwidget.h"
#include "config.h"

CounterWidget::CounterWidget(QWidget *parent)
    : QWidget(parent), m_count(0), m_timer(this), m_gpio(this)
{
    setWindowTitle("BinaryCounter");
    resize(300, 200);
    QHBoxLayout* layout = new QHBoxLayout(this);
    setLayout(layout);

    // QLCDNumber zur Anzeige des Zaehlerstandes dezimal:
    m_lcd = new QLCDNumber(2);

    layout->addWidget(m_lcd);

    m_lcd->display(m_num);


    connect(&m_timer, &QTimer::timeout, this, &CounterWidget::updateCounter);
    m_timer.start(T_UPDATE);
}

CounterWidget::~CounterWidget()
{

}

void CounterWidget::updateLEDs()
{
    for(int idx = 0; idx < 4; idx++)
        m_gpio.set(LEDS[idx], (m_num >> idx) & 0b1);
}


// Zaehlerstand im Widget und dual ueber LEDs anzeigen:
void CounterWidget::updateCounter()
{

    if(m_gpio.isActivated(BUTTONS[2]))
    {
    if(m_num < 15) m_num++;
    else m_num = 0;
    }

    if(m_gpio.isActivated(BUTTONS[0]))
    {
     if(m_num > 0) m_num--;
     else m_num = 15;
    }

     if(m_gpio.isActivated(BUTTONS[1]))
                    m_num = 0;


     m_lcd->display(m_num);
     updateLEDs();




}


