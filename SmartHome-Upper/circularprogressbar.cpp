#include <QPainter>
#include <QDebug>
#include "circularprogressbar.h"

CircularProgressBar::CircularProgressBar(QWidget * parent) : QWidget(parent) 
{
    this->curValue = 24;
    this->maxValue = 100;
    this->minValue = 0;
    this->title = "Title";
    this->textVisible = true;
    this->valueVisible = true;
    this->drawRatio = 0.8;
    this->drawArcPen = QPen(Qt::black, 4, Qt::SolidLine);
    this->drawValuePen = QPen(Qt::black, 2, Qt::SolidLine);
}

CircularProgressBar::~CircularProgressBar() {
	
}

int CircularProgressBar::maximum() const
{
    return maxValue;
}

int CircularProgressBar::minimum() const
{
    return minValue;
}

QString CircularProgressBar::text() const
{
    return title;
}

bool CircularProgressBar::isTextVisible()
{
    return textVisible;
}

bool CircularProgressBar::isValueVisible()
{
    return valueVisible;
}

void CircularProgressBar::setTitle(const QString & text)
{
    this->title = text;
}

void CircularProgressBar::setTextVisible(bool visible)
{
    this->textVisible = visible;
}

void CircularProgressBar::setValueVisible(bool visible)
{
    this->valueVisible = visible;
}

float CircularProgressBar::ratio() const
{
    return drawRatio;
}

void CircularProgressBar::setRatio(float ratio)
{
    this->drawRatio = ratio;
}

const QPen & CircularProgressBar::arcPen() const
{
    return drawArcPen;
}

void CircularProgressBar::setArcPen(const QPen & pen)
{
    this->drawArcPen = pen;
}

const QPen & CircularProgressBar::titlePen() const
{
    return this->drawTitlePen;
}

void CircularProgressBar::setTitlePen(const QPen & pen)
{
    this->drawTitlePen = pen;
}

const QFont & CircularProgressBar::titleFont() const
{
    return this->drawTitleFont;
}

void CircularProgressBar::setTitleFont(const QFont & font)
{
    this->drawTitleFont = font;
}

const QPen & CircularProgressBar::valuePen() const
{
    return drawValuePen;
}

void CircularProgressBar::setValuePen(const QPen & pen)
{
    this->drawValuePen = pen;
}

const QFont & CircularProgressBar::valueFont() const
{
    return drawValueFont;
}

void CircularProgressBar::setValueFont(const QFont & font)
{
    this->drawValueFont = font;
}

void CircularProgressBar::setValue(int value)
{
    this->curValue = value;
    emit valueChanged(value);
}

void CircularProgressBar::setRange(int minimum, int maximum)
{
    setMinimum(minimum);
    setMaximum(maximum);
}

void CircularProgressBar::setMinimum(int minimum)
{
    this->minValue = minimum;
}

void CircularProgressBar::setMaximum(int maximum)
{
    this->maxValue = maximum;
}

void CircularProgressBar::reset()
{
    this->curValue = minValue;
}

void CircularProgressBar::paintEvent(QPaintEvent *event)
{
    // draw pixmap at center of item
    QPainter painter(this);
    painter.drawPixmap(rect(), buffer);

    buffer = generatePixmap();
}

QPixmap CircularProgressBar::generatePixmap() const
{
    QPixmap pixmap(width(), height());
    pixmap.fill(QColor(0, 0, 0, 0));
    QPainter painter(&pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);

    // draw the arc
    painter.setPen(drawArcPen);
    int arcWidth = drawRatio * (width() - drawArcPen.width() * 2);
    int arcHeight = drawRatio * (height() - drawArcPen.width() * 2);
    int arcX = (1 - drawRatio) / 2 * width() + drawArcPen.width();
    int arcY = (1 - drawRatio) / 2 * height() + drawArcPen.width() * 4;
    painter.drawArc(QRect(arcX, arcY, arcWidth, arcHeight), -16 * 150, -16 * int(240 * (float(curValue) / maxValue)));
    
    painter.setPen(QPen(QColor(255, 255, 255, 100), 4, Qt::SolidLine));
    painter.drawArc(QRect(arcX, arcY, arcWidth, arcHeight), -16 * (150 + int(240 * (float(curValue) / maxValue))), -16 * int(240 * (1 - (float(curValue) / maxValue))));

    // draw the value text
    QString valueText = QString::number(curValue);
    int valueX = arcX + 0.25 * arcWidth;
    int valueY = arcY + 0.3 * arcHeight;
    painter.setFont(drawValueFont);
    painter.setPen(drawValuePen);
    painter.drawText(QRect(valueX, valueY, 0.5 * arcWidth, 0.5 * arcHeight), Qt::AlignCenter, valueText);

    // draw the title text
    int textX = valueX;
    int textY = valueY - 0.05 * arcHeight;
    painter.setFont(drawTitleFont);
    painter.setPen(drawTitlePen);
    painter.drawText(QRect(textX, textY, 0.5 * arcWidth, 0.125 * arcHeight), Qt::AlignCenter, title);

    return pixmap;
}
