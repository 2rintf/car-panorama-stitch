#pragma once

#include <QtWidgets/QWidget>
#include <qdebug.h>
#include <qfiledialog.h>
#include "ui_CarPanoramaStitch.h"

#include <opencv2/opencv.hpp>

using namespace cv;

class CarPanoramaStitch : public QWidget
{
	Q_OBJECT

public:
	CarPanoramaStitch(QWidget *parent = Q_NULLPTR);

	QString backFilePath;
	QString leftFilePath;
	QString frontFilePath;
	QString rightFilePath;

	//bool backFlag = false;
	//bool leftFlag = false;
	//bool frontFlag = false;
	//bool rightFlag = false;

	int camFlag = 0x0000;

private:
	Ui::CarPanoramaStitchClass ui;

private slots:
	void on_backSelectBtn_clicked();
	void on_leftSelectBtn_clicked();
	void on_frontSelectBtn_clicked();
	void on_rightSelectBtn_clicked();
	void on_startBtn_clicked();
	void on_cancelBtn_clicked();
};
