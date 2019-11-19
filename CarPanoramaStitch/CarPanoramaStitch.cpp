#include "CarPanoramaStitch.h"

/*����ת��������תΪ�������룬��ֹ���롣*/
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

void CarPanoramaStitch::on_backSelectBtn_clicked()
{
	QString filePath = QFileDialog::getOpenFileName(this, "��ѡ��Back Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		backFlag = false;
		return;
	}
	else {
		backFilePath = filePath;
		backFlag = true;
		ui.debugDisplay->append("Back Cam is selected. " + backFilePath);
	}
}

void CarPanoramaStitch::on_leftSelectBtn_clicked()
{
	qDebug("left select.");
	QString filePath = QFileDialog::getOpenFileName(this, "��ѡ��Left Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		leftFlag = false;
		return;
	}
	else {
		leftFilePath = filePath;
		leftFlag = true;
		ui.debugDisplay->append("Left Cam is selected. " + leftFilePath);
	}
}

void CarPanoramaStitch::on_frontSelectBtn_clicked()
{
	qDebug("front select.");
	QString filePath = QFileDialog::getOpenFileName(this, "��ѡ��Front Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		frontFlag = false;
		return;
	}
	else {
		frontFilePath = filePath;
		frontFlag = true;
		ui.debugDisplay->append("Front Cam is selected. " + frontFilePath);
	}
}

void CarPanoramaStitch::on_rightSelectBtn_clicked()
{
	qDebug("right select.");
	QString filePath = QFileDialog::getOpenFileName(this, "��ѡ��Right Cam...", "./", "*.jpg;*.mp4");//.toUtf8()
	if (filePath.isEmpty())
	{
		ui.debugDisplay->append("File path wrong!");
		rightFlag = false;
		return;
	}
	else {
		rightFilePath = filePath;
		rightFlag = true;
		ui.debugDisplay->append("Right Cam is selected. " + rightFilePath);
	}
	//Mat img = imread(qstr2str(rightFilePath));
}

void CarPanoramaStitch::on_startBtn_clicked()
{
	ui.debugDisplay->append("start.");
}

void CarPanoramaStitch::on_cancelBtn_clicked()
{
	ui.debugDisplay->append("cancel.");
}
