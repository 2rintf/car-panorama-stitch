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
	: QWidget(parent)
{
	ui.setupUi(this);
}


void CarPanoramaStitch::orderImage()
{

	//to-do: better way of order image.
}

void CarPanoramaStitch::imageStitchProcess()
{
	Ptr<Stitcher> stitcher = Stitcher::create();
	stitcher->setFeaturesFinder((Ptr<Feature2D>)xfeatures2d::SIFT::create());
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
	orderImage();
	imageStitchProcess();
}

void CarPanoramaStitch::on_cancelBtn_clicked()
{
	ui.debugDisplay->append("cancel.");
}
