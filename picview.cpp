#include <QtGui>
#include <QDebug>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include "picview.h"
#include "uirectangle.h"
#include "uicoordinate.h"
#include "uicurve.h"
using std::cout;
using std::endl;
PicView::PicView(QWidget *parent) : QWidget(parent)
{
	picNum = 0;
	pElement = NULL;
	bezierSelected = true;
	paraSelected = false;
	rectSelected = false;
	endpointNum = 0;

	ignoreInput = true;
	edgeFocus = 0;
	arcLength = 0;
	leftArc = NULL;
	rightArc = NULL;
	leftMouseDown = false;

	coordinate = new UiCoordinate(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	connect(this, SIGNAL(hasBeenResized(QSize)), coordinate, SLOT(callToResize(QSize)));
	this->setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}

UiCurve* PicView::addCurve()
{
	UiCurve* curve = new UiCurve(this);
	curve->hide();
	connect(this, SIGNAL(hasBeenResized(QSize)), curve, SLOT(callToResize(QSize)));
	for(int i = 0; i < 4; i++)
	{
		(curve->Points())[i] = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
		(curve->Points())[i]->hide();
		(curve->Points())[i]->setCirColor(Qt::yellow);
		(curve->Points())[i]->setRecColor(Qt::yellow);

		connect(this, SIGNAL(hasBeenResized(QSize)), (curve->Points())[i], SLOT(callToResize(QSize)));
	}
	return curve;
}

void PicView::delCurve(UiCurve* curve)
{
	for(int i = 0; i < 4; i++)
	{
		(curve->Points())[i]->hide();
		delete (curve->Points())[i];
		(curve->Points())[i] = NULL;
	}
	curve->hide();
	delete curve;
	curve = NULL;
}

UiRectangle* PicView::addRectangle()
{
	rectangle = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0,0.0));
	rectangle->hide();
	rectangle->LeftUpRect() = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	rectangle->LeftUpRect()->hide();
	rectangle->LeftUpRect()->setRecColor(Qt::red);
	rectangle->LeftUpRect()->setCirColor(Qt::red);
	rectangle->RightDownRect() = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	rectangle->RightDownRect()->hide();
	rectangle->RightDownRect()->setRecColor(Qt::red);
	rectangle->RightDownRect()->setCirColor(Qt::red);
	connect(this, SIGNAL(hasBeenResized(QSize)), rectangle, SLOT(callToResize(QSize)));
	connect(this, SIGNAL(hasBeenResized(QSize)), rectangle->LeftUpRect(), SLOT(callToResize(QSize)));
	connect(this, SIGNAL(hasBeenResized(QSize)), rectangle->RightDownRect(), SLOT(callToResize(QSize)));
	return rectangle;
}

void PicView::delRectangle(UiRectangle* rectangle)
{
	rectangle->LeftUpRect()->hide();
	delete rectangle->LeftUpRect();
	rectangle->LeftUpRect() = NULL;

	rectangle->RightDownRect()->hide();
	delete rectangle->RightDownRect();
	rectangle->RightDownRect() = NULL;

	rectangle->hide();
	delete rectangle;
	rectangle = NULL;
}

void PicView::delRect()
{
}




void PicView::addBezier()
{
	if(bezierSelected)
	{
		return;
	}
	bezierSelected = true;
	paraSelected = false;
	rectSelected = false;
	cout<<"selectBezier"<<endl;
}

void PicView::addPara()
{
	if(paraSelected)
	{
		return;
	}
	paraSelected = true;
	bezierSelected = false;
	rectSelected = false;
	cout<<"selectPara"<<endl;
}

void PicView::addRect()
{
	if(rectSelected)
	{
		return;
	}
	rectSelected = true;
	paraSelected = false;
	bezierSelected = false;
	cout<<"selectRect"<<endl;
}

void PicView::delBezier()
{
}

void PicView::delPara()
{
}

int PicView::doCompute(QWidget *pWidget, char *fileName)
{
	if(fileName == NULL)
	{
		cout<<"fileName is a null string"<<endl;
		return 0;
	}
	FILE *out;
	out = fopen(fileName, "w");
	if(out == NULL)
	{
		cout<<"open file error"<<endl;
		exit(0);
	}

	QPixmap ellipse = QPixmap::grabWidget(rectangle, rectangle->rect());
	QImage image = ellipse.toImage();

	for(int i = 0; i < image.height(); i++)
	{
		int fj = 0;
		int bj = image.width() - 1;
		for(int j = 0; j < image.width(); j++)
		{
			QRgb rgb = image.pixel(j, i);
			if(qBlue(rgb) == 0 && qRed(rgb) == 0 && qGreen(rgb) >= 250)
			{
				fj = j;
				break;
			}
		}
		
		for(int k = image.width() - 1; k >= 0; k--)
		{
			QRgb rgb = image.pixel(k, i);
			if(qBlue(rgb) == 0 && qRed(rgb) == 0 && qGreen(rgb) >= 250)
			{
				bj = k;
				//care
				fprintf(out, "%d,%d,%d\n", i, fj, bj);
				break;
			}
		}
	}
	fclose(out);
}

void PicView::computeArc()
{
	/*
	for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
	{
		if(doCompute(*it, name) == 0)
		{
			exit(0);
		}
	}

	for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
	{
		if(doCompute(*it, name) == 0)
		{
			exit(0);
		}
	}
	*/
}
/*
void PicView::computeArc()
{
	if(leftArc != NULL)
	{
		delete [] leftArc;
	}
	if(rightArc != NULL)
	{
		delete [] rightArc;
	}
	FILE *out;
	out = fopen("output.txt", "at");
	if(out == NULL)
	{
		cout<<"open file error"<<endl;
		exit(0);
	}
	arcLength = leftRightDownPos.y() - leftLeftUpPos.y() + 2;
	leftArc = new QPointF[arcLength];
	rightArc = new QPointF[arcLength];

	QPixmap ellipse = QPixmap::grabWidget(rectangle, rectangle->rect());
	QImage image = ellipse.toImage();
	arcLength = 0;

	//存储图片编号
	fprintf(out, "%d,%d,%d,%d\n", -1, -1, -1, 0);

	for(int fj = leftLeftUpPos.y(); fj <= leftRightDownPos.y(); fj++, arcLength++)
	{
		for(int fi = leftLeftUpPos.x(), bi = leftRightDownPos.x(); fi <= leftRightDownPos.x(), bi >= leftLeftUpPos.x(); fi++, bi--)
		{
			QRgb rgb = image.pixel(fi, fj);
			int blue = qBlue(rgb);
			if(qBlue(rgb) > 250 && qRed(rgb) == 0 && qGreen(rgb) == 0)
			{
				leftArc[arcLength] = QPoint(fi, fj);
				rightArc[arcLength] = QPoint(bi, fj);
				fprintf(out, "%d,%d,%d,%d\n", fi, fj, bi, fj);
				break;
			}
		}
	}
	fclose(out);
	int a,b,c,d;
	FILE *in;
	in = fopen("output.txt", "r");
	if(in == NULL)
	{
		cout<<"open file error"<<endl;
		exit(0);
	}
	int i = 0;
	while(fscanf(in, "%d,%d,%d,%d", &a, &b, &c, &d) == 4)
	{
		if(i > 0)
		{
			cout<<"left: "<<leftArc[i - 1].x()<<", "<<leftArc[i - 1].y()<<"  right: "<<rightArc[i - 1].x()<<", "<<rightArc[i - 1].y()<<"left: "<<a<<", "<<b<<"  right: "<<c<<", "<<d<<endl;
		}
		i++;
	}
	
	
	fclose(in);
	if(leftArc != NULL)
	{
		delete [] leftArc;
	}
	if(rightArc != NULL)
	{
		delete [] rightArc;
	}
	leftArc = NULL;
	rightArc = NULL;
}
*/
void PicView::keyPressEvent(QKeyEvent *event)
{
	int key = event->key();
	bool move = true;
	QPointF tempLeftUp;
	QPointF tempRightDown ;
	switch(key)
	{
		case Qt::Key_Up:
			tempLeftUp = leftLeftUpPos;
			tempRightDown = leftRightDownPos;
			if(edgeFocus == 0 || edgeFocus == 2)
			{
				leftLeftUpPos.ry() -= 1;
			}
			if(edgeFocus == 0 || edgeFocus == 4)
			{
				leftRightDownPos.ry() -= 1;
			}
			break;
		case Qt::Key_Down:
			tempLeftUp = leftLeftUpPos;
			tempRightDown = leftRightDownPos;
			if(edgeFocus == 0 || edgeFocus == 2)
			{
				leftLeftUpPos.ry() += 1;
			}
			if(edgeFocus == 0 || edgeFocus == 4)
			{
				leftRightDownPos.ry() += 1;
			}
			break;
		case Qt::Key_Left:
			tempLeftUp = leftLeftUpPos;
			tempRightDown = leftRightDownPos;
			if(edgeFocus == 0 || edgeFocus == 1)
			{
				leftLeftUpPos.rx() -= 1;
			}
			if(edgeFocus == 0 || edgeFocus == 3)
			{
				leftRightDownPos.rx() -= 1;
			}
			break;
		case Qt::Key_Right:
			tempLeftUp = leftLeftUpPos;
			tempRightDown = leftRightDownPos;
			if(edgeFocus == 0 || edgeFocus == 1)
			{
				leftLeftUpPos.rx() += 1;
			}
			if(edgeFocus == 0 || edgeFocus == 3)
			{
				leftRightDownPos.rx() += 1;
			}
			break;
		default:
			move = false;
			break;
	}
	if(move)
	{
		if(leftLeftUpPos.x() >= 0.0 && leftLeftUpPos.y() >= 0 && leftRightDownPos.x() <= this->width() && leftRightDownPos.y() <= this->height())
		{
			rectangle->change(leftLeftUpPos, leftRightDownPos);
		}
		else
		{
			leftLeftUpPos = tempLeftUp;
			leftRightDownPos = tempRightDown;
		}
	}
}

void PicView::paintEvent(QPaintEvent *) {
	QPainter painter(this);
	painter.drawImage(QPoint(0,0), img);
}

void PicView::mousePressEvent(QMouseEvent *event)
{
	if(ignoreInput)
	{
		return;
	}
	leftMouseDown = true;

	if(event->button() == Qt::LeftButton)
	{
		if(bezierSelected)
		{
			cleared = false;
			curve = addCurve();

			leftCurPos = event->pos();
			(curve->Points())[0]->change(QPointF(leftCurPos.x() - 3, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3, leftCurPos.y() + 3));
			(curve->Points())[0]->show();
			int xdist = 100;
			(curve->Points())[1]->change(QPointF(leftCurPos.x() - 3 + xdist, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3 + xdist, leftCurPos.y() + 3));
			(curve->Points())[1]->show();

			QPointF beginCenter = (curve->Points())[0]->centre();
			QPointF endCenter = (curve->Points())[1]->centre();
			QPointF ctrlPoint1(beginCenter.x() + (endCenter.x() - beginCenter.x()) / 3.0, beginCenter.y() + (endCenter.y() - beginCenter.y()) / 3.0);
			QPointF ctrlPoint2(beginCenter.x() + (endCenter.x() - beginCenter.x()) / 3.0 * 2.0, beginCenter.y() + (endCenter.y() - beginCenter.y()) / 3.0 * 2.0);
			(curve->Points())[2]->change(QPointF(ctrlPoint1.x() - 3.0, ctrlPoint1.y() - 3.0), QPointF(ctrlPoint1.x() + 3.0, ctrlPoint1.y() + 3.0));
			(curve->Points())[2]->show();
			(curve->Points())[3]->change(QPointF(ctrlPoint2.x() - 3.0, ctrlPoint2.y() - 3.0), QPointF(ctrlPoint2.x() + 3.0, ctrlPoint2.y() + 3.0));
			(curve->Points())[3]->show();

			curve->change();
			curve->show();

			for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
			{
				(*it)->change();
			}

			for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
			{
				(*it)->change();
			}

			curveVector.push_back(curve);

			bezierSelected = false;
		}
		if(paraSelected)
		{
			cleared = false;
			bezierSelected = false;
		}
		if(rectSelected)
		{
			cleared = false;
			rectangle = addRectangle();
			leftCurPos = event->pos();
			rectangle->setFocus(1);
			rectangle->setFocusPoint(leftCurPos);
			int xdist = 100;
			int ydist = 100;
			rectangle->setFocus(2);
			rectangle->setFocusPoint(QPointF(leftCurPos.x() + xdist, leftCurPos.y() + ydist));

			rectangle->LeftUpRect()->show();
			rectangle->RightDownRect()->show();
			rectangle->change();
			rectangle->show();

			for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
			{
				(*it)->change();
			}

			for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
			{
				(*it)->change();
			}

			rectangleVector.push_back(rectangle);
			rectSelected = false;
		}
	}
	else
	{
	}
}

void PicView::mouseMoveEvent(QMouseEvent *event)
{

	cout<<"========="<<endl;
	if(ignoreInput || cleared)
	{
		cout<<"ignore-------"<<endl;
		return;
	}
	leftCurPos = event->pos();

	if(leftMouseDown == true)
	{
		if(pElement == NULL)
		{
			return;
		}
		else
		{

			for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
			{
				(*it)->change();
			}

			for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
			{
				(*it)->change();
			}

			pElement->setFocusPoint(leftCurPos);
			pElement->change();
		}
	}
	else
	{
		for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
		{
			curve = *it;
			pElement = curve;
			if((curve->Points())[0]->withinRect(leftCurPos))
			{
				pElement->setFocus(1);
			}
			else if((curve->Points())[1]->withinRect(leftCurPos))
			{
				pElement->setFocus(2);
			}
			else if((curve->Points())[2]->withinRect(leftCurPos))
			{
				pElement->setFocus(3);
			}
			else if((curve->Points())[3]->withinRect(leftCurPos))
			{
				pElement->setFocus(4);
			}
			else
			{
				pElement = NULL;
			}
			if(pElement != NULL)
			{
				return;
			}
		}
		for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
		{
			rectangle = *it;
			pElement = rectangle;
			if(rectangle->LeftUpRect()->withinRect(leftCurPos))
			{
				pElement->setFocus(1);
			}
			else if(rectangle->RightDownRect()->withinRect(leftCurPos))
			{
				pElement->setFocus(2);
			}
			else
			{
				pElement = NULL;
			}
			if(pElement != NULL)
			{
				return;
			}
		}
	}
}

static inline float MyAbs(float a)
{
	return (a > 0 ? a : (0 - a));
}
void PicView::mouseReleaseEvent(QMouseEvent *event)
{
	if(ignoreInput)
	{
		return;
	}
	leftMouseDown = false;
	if(paraSelected)
	{
	}
	if(bezierSelected)
	{
		if(event->button() == Qt::LeftButton)
		{
			leftMouseDown = false;
			cout<<"release"<<endl;
			setMouseTracking(false);
			setMouseTracking(true);
		}
	}
	if(rectSelected)
	{
		cout<<"view TopLeft: "<<(rectangle->rect()).topLeft().x()<<", "<<(rectangle->rect()).topLeft().y()<<endl;
		cout<<"view BottomRight: "<<(rectangle->rect()).bottomRight().x()<<", "<<(rectangle->rect()).bottomRight().y()<<endl;
		if(event->button() == Qt::LeftButton)
		{
			QPointF point = event->pos();
			if(MyAbs(point.x() - leftLeftUpPos.x()) < 1.0 && MyAbs(point.y() - leftLeftUpPos.y()) < 1.0)
			{
			}
			else
			{
			}
			leftMouseDown = false;
			emit PicFound();
		}
	}
}
bool PicView::loadImage(const QString s)
{
	fileName = QFileInfo(s).baseName();
	if(img.load(s))
	{
		if(img.format() != QImage::Format_Indexed8)
		{
			return false;
		}
		resize(img.rect().width(), img.rect().height());
		if(!img.isNull())
		{
			ignoreInput = false;
		}
		update();
		emit imageUnwrapped(&img);
		coordinate->show();
	}
}
void PicView::resizeEvent(QResizeEvent *e)
{
	emit hasBeenResized(e->size());
}

void PicView::cleanUp()
{
	cleared = true;
	for(std::vector<UiRectangle*>::iterator it = rectangleVector.begin(); it != rectangleVector.end(); it++)
	{
		rectangle = *it;
		delRectangle(rectangle);
		cout<<"----"<<endl;
	}
	rectangleVector.clear();
	for(std::vector<UiCurve*>::iterator it = curveVector.begin(); it != curveVector.end(); it++)
	{
		curve = *it;
		delCurve(curve);
		cout<<"+++"<<endl;
	}
	curveVector.clear();
	cout<<"out1"<<endl;
	if(!img.isNull())
	{
		ignoreInput = false;
	}
	//emit cleanedUp();
	cout<<"out2"<<endl;
	cleared = false;
}
