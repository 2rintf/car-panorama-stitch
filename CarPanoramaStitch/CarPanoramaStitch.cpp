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


//*@param clone true 表示与 Mat 不共享内存，更改生成的 mat 不会影响原始图像，false 则会与 mat 共享内存
//* @param rb_swap 只针对 CV_8UC3 格式，如果 true 则会调换 R 与 B RGB->BGR，如果共享内存的话原始图像也会发生变化
QImage cvMat2QImage(const cv::Mat& mat, bool clone, bool rb_swap)
{
	const uchar *pSrc = (const uchar*)mat.data;
	// 8-bits unsigned, NO. OF CHANNELS = 1
	if (mat.type() == CV_8UC1)
	{
		//QImage image(mat.cols, mat.rows, QImage::Format_Grayscale8);
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		if (clone) return image.copy();
		return image;
	}
	// 8-bits unsigned, NO. OF CHANNELS = 3
	else if (mat.type() == CV_8UC3)
	{
		// Create QImage with same dimensions as input Mat
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		if (clone)
		{
			if (rb_swap) return image.rgbSwapped();
			return image.copy();
		}
		else
		{
			if (rb_swap)
			{
				cv::cvtColor(mat, mat, COLOR_BGR2RGB);
			}
			return image;
		}

	}
	else if (mat.type() == CV_8UC4)
	{
		qDebug() << "CV_8UC4";
		QImage image(pSrc, mat.cols, mat.rows, mat.step, QImage::Format_ARGB32);
		if (clone) return image.copy();
		return image;
	}
	else
	{
		qDebug() << "ERROR: Mat could not be converted to QImage.";
		return QImage();
	}
}

cv::Mat QImage2cvMat(QImage &image, bool clone, bool rb_swap)
{
	cv::Mat mat;
	//qDebug() << image.format();
	switch (image.format())
	{
	case QImage::Format_ARGB32:
	case QImage::Format_RGB32:
	case QImage::Format_ARGB32_Premultiplied:
		mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void *)image.constBits(), image.bytesPerLine());
		if (clone)  mat = mat.clone();
		break;
	case QImage::Format_RGB888:
		mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void *)image.constBits(), image.bytesPerLine());
		if (clone)  mat = mat.clone();
		if (rb_swap) cv::cvtColor(mat, mat, COLOR_BGR2RGB);
		break;
	case QImage::Format_Indexed8:
	case QImage::Format_Grayscale8:
		mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void *)image.bits(), image.bytesPerLine());
		if (clone)  mat = mat.clone();
		break;
	}
	return mat;
}

/***************************************************************************/

CarPanoramaStitch::CarPanoramaStitch(QWidget *parent)
	: QWidget(parent),srcImg(4),showImg(4)
{
	ui.setupUi(this);
	ui.startBtn->setEnabled(false);
}


void CarPanoramaStitch::orderImage()
{
	//to-do: better way of order image.
	//! 注意。因为此处使用vector来存储4张QImage，所以必须将临时变量深拷贝出来，再赋值。否则那段内存temp2.data一直被刷新和共用。
	for (int i = 0; i < 4; i++)
	{

		if (camFlag[i])
		{
			temp = imread(qstr2str(imageFilePath[i]));
			Mat temp2 = temp;
			QImage help;
			//? 是否深拷贝？
			srcImg[i] = temp;

			cvtColor(temp, temp2, COLOR_BGR2RGB);
			qDebug()<< ui.backPic->width()<< ui.backPic->height();

			cv::resize(temp2, temp2, Size(320,180));
			qDebug() << temp2.step;
			
			//! 因为这里使用temp2.data，所以后面需要深拷贝copy
			help = QImage((const unsigned char*)(temp2.data),temp2.cols, temp2.rows,temp2.step, QImage::Format_RGB888);
			showImg[i] = help.copy();
			//showTestImg = help;
			//ui.testPic->setPixmap(QPixmap::fromImage(showTestImg));
			//ui.testPic->setPixmap(QPixmap::fromImage(showImg[i]));
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
		else
		{
			switch (i)
			{
			default:
				break;
			case 0:
				ui.backPic->clear();
				break;
			case 1:
				ui.leftPic->clear();
				break;
			case 2:
				ui.frontPic->clear();
				break;
			case 3:
				ui.rightPic->clear();
				break;
			}
		}
	}
	ui.startBtn->setEnabled(true);

}
