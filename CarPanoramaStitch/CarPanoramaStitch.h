#pragma once

#include <QtWidgets/QWidget>
#include <qdebug.h>
#include <qfiledialog.h>
#include "ui_CarPanoramaStitch.h"

#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching.hpp>
#include <xfeatures2d/nonfree.hpp>

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

	bool camFlag[4] = { 0,0,0,0 };

	/* For only image stitching. */
	Mat Img1;
	Mat Img2;
	Mat Img3;
	Mat Img4;

	QImage backImg;//Img1.
	QImage leftImg;//Img2.
	QImage frontImg;//Img3.
	QImage rightImg;//Img4.
	/* For only image stitching. */



private:
	Ui::CarPanoramaStitchClass ui;

	void stitchProcess();

private slots:
	void on_backSelectBtn_clicked();
	void on_leftSelectBtn_clicked();
	void on_frontSelectBtn_clicked();
	void on_rightSelectBtn_clicked();
	void on_startBtn_clicked();
	void on_cancelBtn_clicked();
};
