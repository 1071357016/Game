#ifndef CHOOSELEVELWINDOW_H
#define CHOOSELEVELWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include"mypushbutton.h"
#include"gameworld.h"

class ChooseLevelwindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseLevelwindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);

signals:

};

#endif // CHOOSELEVELWINDOW_H
