
#include "analogclock.h"
#include "./ui_analogclock.h"
#include <QPainter>
#include <QTime>
#include <QTimer>


AnalogClock::AnalogClock(QWidget *parent)
    : QWidget(parent)

{

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&AnalogClock::update));
    timer->start(1000);
    setWindowTitle(tr("Стрілковий годинник Алли Коханюк"));
    resize(500, 500);
    setStyleSheet("background-color:black;");

}

AnalogClock::~AnalogClock()
{
    delete ui;
}

void AnalogClock::paintEvent(QPaintEvent *)
{
    static const QPoint hourHand[4] = {
        QPoint(3, -20),
        QPoint(0, 0),
        QPoint(-3, -20),
        QPoint(0, -60)

    };
    static const QPoint minuteHand[4] = {
        QPoint(4, -30),
        QPoint(0, 0),
        QPoint(-4, -30),
        QPoint(0, -80)
    };
    static const QPoint secHand[3] = {
        QPoint(1, 8),
        QPoint(-1, 8),
        QPoint(0, -80)

    };
    QColor hourColor(25, 255, 255);
    QColor minuteColor(255, 216, 0);
    QColor secColor(255,0,0);
    QColor circleColor(255,0,0);
    QColor dotColor(255,255,255);
    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);
    painter.scale(side / 200.0, side / 200.0);

    QTime time = QTime::currentTime();

    painter.setPen(Qt::NoPen);
    painter.setBrush(secColor);
    painter.save();
    painter.rotate(6 * (time.second()));
    painter.drawConvexPolygon(secHand, 3);
    painter.restore();


    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.save();
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 4);
    painter.restore();
    painter.setPen(dotColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(95, 0, 96, 0);
        painter.rotate(6.0);
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.save();
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 4);
    painter.restore();
    painter.setPen(secColor);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }



    painter.setPen(Qt::NoPen);
    painter.setBrush(circleColor);
    painter.save();


    QPainter myellip(this);

    QPen epen;
    epen.setWidth(9);
    epen.setBrush(circleColor);
    myellip.setPen(epen);
    myellip.drawEllipse(width() / 2-5, height() / 2-5, 10, 10);


}

