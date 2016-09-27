#ifndef CIRCULARPROGRESSBAR_H
#define CIRCULARPROGRESSBAR_H
#include <QWidget>
#include <QString>
#include <QPixmap>
#include <QPen>

class CircularProgressBar : public QWidget 
{
	Q_OBJECT

public:
	CircularProgressBar(QWidget * parent = Q_NULLPTR);
	~CircularProgressBar();
    int maximum() const;
    int minimum() const;
    QString text() const;
    bool isTextVisible();
    bool isValueVisible();
    void setTitle(const QString & text);
    void setTextVisible(bool visible);
    void setValueVisible(bool visible);
    float ratio() const;
    void setRatio(float ratio);
    const QPen & arcPen() const;
    void setArcPen(const QPen & pen);
    const QPen & titlePen() const;
    void setTitlePen(const QPen & pen);
    const QFont & titleFont() const;
    void setTitleFont(const QFont & font);
    const QPen & valuePen() const;
    void setValuePen(const QPen & pen);
    const QFont & valueFont() const;
    void setValueFont(const QFont & font);

signals:
    void valueChanged(int newValue);

public slots:
    void setValue(int value);
    void setRange(int minimum, int maximum);
    void setMinimum(int minimum);
    void setMaximum(int maximum);
    void reset();

protected:
    virtual void paintEvent(QPaintEvent *event);

private:
    int curValue;
    int maxValue;
    int minValue;
    bool textVisible;
    bool valueVisible;
    float drawRatio;
    QString title;
    QPixmap buffer;
    QPen drawArcPen;
    QPen drawValuePen;
    QFont drawValueFont;
    QPen drawTitlePen;
    QFont drawTitleFont;
    QPixmap generatePixmap() const;
};

#endif // CIRCULARPROGRESSBAR_HPP