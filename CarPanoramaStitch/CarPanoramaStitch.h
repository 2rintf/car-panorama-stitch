#pragma once

#include <QtWidgets/QWidget>
#include "ui_CarPanoramaStitch.h"

class CarPanoramaStitch : public QWidget
{
	Q_OBJECT

public:
	CarPanoramaStitch(QWidget *parent = Q_NULLPTR);

private:
	Ui::CarPanoramaStitchClass ui;
};
