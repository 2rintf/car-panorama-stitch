#include "CarPanoramaStitch.h"

/*编码转换，可以转为本机编码，防止乱码。*/
QString str2qstr(const std::string str)
{
	return QString::fromLocal8Bit(str.data());
}

std::string qstr2str(const QString qstr)
{
	QByteArray cdata = qstr.toLocal8Bit();
	return std::string(cdata);
}
/*************************************/

CarPanoramaStitch::CarPanoramaStitch(QWidget *parent)
	: QWidget(parent),showImg(4)
{
	ui.setupUi(this);
	ui.startBtn->setEnabled(false);
}


void CarPanoramaStitch::orderImage()
{
	//to-do: better way of order image.
	for (int i = 0; i < 4; i++)
	{
		if (camFlag[i])
		{
			temp = imread(qstr2str(imageFilePath[i]));
			Mat temp2;
			temp.convertTo(temp2, CV_8UC3);
			srcImg.push_back(temp2);
			cvtColor(temp2, temp2, COLOR_BGR2RGB);
			qDebug()<< ui.backPic->width()<< ui.backPic->height();
			//！ 这里resize有问题，会导致QIamge显示错误
			cv::resize(temp2, temp2, Size(ui.backPic->width(), ui.backPic->height()));
			qDebug() << temp2.step;
			
			showImg[i] = QImage((const unsigned char*)(temp2.data),temp2.cols, temp2.rows,temp2.step[0], QImage::Format_RGB888);
		}
		else
		{
			showImg[i] = QImage();
		}
	}
}

void CarPanoramaStitch::imageStitchProcess()
{
	//Ptr<Stitcher> stitcher = Stitcher::create();
	//stitcher->setFeaturesFinder((Ptr<Feature2D>)xfeatures2d::SIFT::create());
	Mat pano;
	//Stitcher::Status status = stitcher->stitch(, pano);

	
}

void CarPanoramaStitch::on_backSelectBtn_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, "请选择Back Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		//backFlag = false;
		camFlag[0] = false;
		return;
	}
	else {
		imageFilePath[0] = filePath;
		//backFlag = true;
		camFlag[0] = true;
		ui.debugDisplay->append("Back Cam is selected. " + imageFilePath[0]);
	}
}

void CarPanoramaStitch::on_leftSelectBtn_clicked()
{
	qDebug("left select.");
	QString filePath = QFileDialog::getOpenFileName(this, "请选择Left Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		//leftFlag = false;
		camFlag[1] = false;
		return;
	}
	else {
		imageFilePath[1] = filePath;
		//leftFlag = true;
		camFlag[1] = true;
		ui.debugDisplay->append("Left Cam is selected. " + imageFilePath[1]);
	}
}

void CarPanoramaStitch::on_frontSelectBtn_clicked()
{
	qDebug("front select.");
	QString filePath = QFileDialog::getOpenFileName(this, "请选择Front Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		camFlag[2] = false;
		return;
	}
	else {
		imageFilePath[2] = filePath;
		camFlag[2] = true;
		ui.debugDisplay->append("Front Cam is selected. " + imageFilePath[2]);
	}
}

void CarPanoramaStitch::on_rightSelectBtn_clicked()
{
	qDebug("right select.");
	QString filePath = QFileDialog::getOpenFileName(this, "请选择Right Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		camFlag[3] = false;
		return;
	}
	else {
		imageFilePath[3] = filePath;
		camFlag[3] = true;
		ui.debugDisplay->append("Right Cam is selected. " + imageFilePath[3]);
	}
	//Mat img = imread(qstr2str(rightFilePath));
}

void CarPanoramaStitch::on_startBtn_clicked()
{
	ui.debugDisplay->append("start.");
	//imageStitchProcess();
}

void CarPanoramaStitch::on_cancelBtn_clicked()
{
	ui.debugDisplay->append("cancel.");
}

void CarPanoramaStitch::on_lockBtn_clicked()
{
	orderImage();
	for (int i = 0; i < 4; i++)
	{
		if (!showImg[i].isNull())
		{
			switch (i)
			{
			default:
				break;
			case 0:
				ui.backPic->setPixmap(QPixmap::fromImage(showImg[0]));
				break;
			case 1:
				ui.leftPic->setPixmap(QPixmap::fromImage(showImg[1]));
				break;
			case 2:
				ui.frontPic->setPixmap(QPixmap::fromImage(showImg[2]));
				break;
			case 3:
				ui.rightPic->setPixmap(QPixmap::fromImage(showImg[3]));
				break;
			}
		}
	}
	ui.startBtn->setEnabled(true);

}
