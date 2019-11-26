#pragma once

#include <QtWidgets/QWidget>
#include <qdebug.h>
#include <qfiledialog.h>
#include "ui_CarPanoramaStitch.h"

#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/stitching.hpp>
//#include <xfeatures2d/nonfree.hpp>

using namespace cv;

class CarPanoramaStitch : public QWidget
{
	Q_OBJECT

public:
	CarPanoramaStitch(QWidget *parent = Q_NULLPTR);

	//QString backFilePath;
	//QString leftFilePath;
	//QString frontFilePath;
	//QString rightFilePath;

	QString imageFilePath[4];

	bool camFlag[4] = { 0,0,0,0 };

	/* For only image stitching. */
	std::vector<Mat> srcImg;// 固定大小为4
	std::vector<QImage> showImg;// 固定大小为4，用于QIamge显示。
							 //类中初始化另一个类时，应该在初始化列表中完成！
	QImage showTestImg;
	int numOfImg = 0;
	
	//Mat Img1;
	//Mat Img2;
	//Mat Img3;
	//Mat Img4;

	QImage backImg;//Img1.
	QImage leftImg;//Img2.
	QImage frontImg;//Img3.
	QImage rightImg;//Img4.
	/* For only image stitching. */

	struct CAM
	{
		Mat cv_img;
		QImage qt_img;
		bool isNull = true;

	};

	



private:
	Ui::CarPanoramaStitchClass ui;

	Mat temp;

	void orderImage();
	void imageStitchProcess();

private slots:
	void on_backSelectBtn_clicked();
	void on_leftSelectBtn_clicked();
	void on_frontSelectBtn_clicked();
	void on_rightSelectBtn_clicked();
	void on_startBtn_clicked();
	void on_cancelBtn_clicked();
	void on_lockBtn_clicked();
};
