#include <QtGui>
#include <QDebug>
#include <cmath>
#include <iostream>
#include <stdio.h>
#include "picview.h"
#include "uirectangle.h"
#include "uicoordinate.h"
#include "uicurve.h"
//#include "uicircle.h"
//#include "sinwavelet.h"
//#include "median.h"
//#include "gaussian.h"
//#include "uiparabola.h"
using std::cout;
using std::endl;
PicView::PicView(QWidget *parent) : QWidget(parent)
{
	bezierSelected = true;
	paraSelected = false;
	rectSelected = false;
	endpointNum = 0;
	selectedBZPoint = 0;

	ignoreInput = true;
	focus = 0;
	edgeFocus = 0;
	arcLength = 0;
	leftArc = NULL;
	rightArc = NULL;
	firstDownMove = true;
	leftMouseDown = false;
	adjustRectangle = false;
	cleared = true;
	//circle = new UiCircle(this, QPointF(0.0,0.0), 1.0);
	rectangle = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0,0.0));
	rectangle->hide();
	leftUpRect = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	leftUpRect->hide();
	rightDownRect = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	rightDownRect->hide();
	coordinate = new UiCoordinate(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
	connect(this, SIGNAL(hasBeenResized(QSize)), rectangle, SLOT(callToResize(QSize)));
	connect(this, SIGNAL(hasBeenResized(QSize)), leftUpRect, SLOT(callToResize(QSize)));
	connect(this, SIGNAL(hasBeenResized(QSize)), rightDownRect, SLOT(callToResize(QSize)));
	connect(this, SIGNAL(hasBeenResized(QSize)), coordinate, SLOT(callToResize(QSize)));

	for(int i = 0; i < 4; i++)
	{
		bezierPoint[i] = new UiRectangle(this, QPointF(0.0, 0.0), QPointF(0.0, 0.0));
		bezierPoint[i]->hide();
		connect(this, SIGNAL(hasBeenResized(QSize)), bezierPoint[i], SLOT(callToResize(QSize)));
	}
	curve = new UiCurve(this);
	curve->hide();
	connect(this, SIGNAL(hasBeenResized(QSize)), curve, SLOT(callToResize(QSize)));

	this->setFocusPolicy(Qt::StrongFocus);
	setMouseTracking(true);
}
void PicView::selectBezier()
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

void PicView::selectPara()
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

void PicView::selectRect()
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
	if(paraSelected)
	{
	}
	if(bezierSelected)
	{
		if(event->button() == Qt::LeftButton)
		{
			leftMouseDown = true;
			if(endpointNum >= 2)
			{
				return;
			}
			selectedBZPoint = 0;
			leftCurPos = event->pos();
			bezierPoint[endpointNum]->change(QPointF(leftCurPos.x() - 5, leftCurPos.y() - 5), QPointF(leftCurPos.x() + 5, leftCurPos.y() + 5));
			bezierPoint[endpointNum]->show();
			endpointNum++;
			if(endpointNum == 2)
			{
				QPointF beginCenter = bezierPoint[0]->centre();
				QPointF endCenter = bezierPoint[1]->centre();
				QPointF ctrlPoint1(beginCenter.x() + (endCenter.x() - beginCenter.x()) / 3.0, beginCenter.y() + (endCenter.y() - beginCenter.y()) / 3.0);
				QPointF ctrlPoint2(beginCenter.x() + (endCenter.x() - beginCenter.x()) / 3.0 * 2.0, beginCenter.y() + (endCenter.y() - beginCenter.y()) / 3.0 * 2.0);
				bezierPoint[2]->change(QPointF(ctrlPoint1.x() - 5.0, ctrlPoint1.y() - 5.0), QPointF(ctrlPoint1.x() + 5.0, ctrlPoint1.y() + 5.0));
				bezierPoint[2]->show();
				bezierPoint[3]->change(QPointF(ctrlPoint2.x() - 5.0, ctrlPoint2.y() - 5.0), QPointF(ctrlPoint2.x() + 5.0, ctrlPoint2.y() + 5.0));
				bezierPoint[3]->show();

				cout<<"beginCenter: "<<beginCenter.x()<<"   "<<beginCenter.y()<<endl;
				cout<<"endCenter: "<<endCenter.x()<<"   "<<endCenter.y()<<endl;
				cout<<"ctrlPoint1: "<<ctrlPoint1.x()<<"   "<<ctrlPoint1.y()<<endl;
				cout<<"ctrlPoint2: "<<ctrlPoint2.x()<<"   "<<ctrlPoint2.y()<<endl;
				cout<<"bezierPoint[2]: "<<"leftUp: "<<bezierPoint[2]->leftUp().x()<<"  "<<bezierPoint[2]->leftUp().y()<<"rightDown: "<<bezierPoint[2]->rightDown().x()<<"  "<<bezierPoint[2]->rightDown().y()<<endl;

				cout<<"bezierPoint[3]: "<<"leftUp: "<<bezierPoint[3]->leftUp().x()<<"  "<<bezierPoint[3]->leftUp().y()<<"rightDown: "<<bezierPoint[3]->rightDown().x()<<"  "<<bezierPoint[3]->rightDown().y()<<endl;
			}
		}
	}
	if(rectSelected)
	{
		if(event->button() == Qt::LeftButton)
		{
			leftMouseDown = true;
			edgeFocus = 0;
			if(adjustRectangle)
			{
				leftCurPos = event->pos();
				switch(focus)
				{
					case 0:
						//leftLeftUpPos = event->pos();
						//adjustRectangle = false;
						break;
					case 1:
						leftUpRect->change(QPointF(leftCurPos.x() - 5, leftCurPos.y() - 5), QPointF(leftCurPos.x() + 5, leftCurPos.y() + 5));
						leftUpRect->show();
						break;
					case 2:
						rightDownRect->change(QPointF(leftCurPos.x() - 5, leftCurPos.y() - 5), QPointF(leftCurPos.x() + 5, leftCurPos.y() + 5));
						rightDownRect->show();
						break;
					case 3:
						edgeFocus = 1;
						break;
					case 4:
						edgeFocus = 2;
						break;
					case 5:
						edgeFocus = 3;
						break;
					case 6:
						edgeFocus = 4;
						break;
					default:
						break;
				}

			}
			else
			{
				leftUpRect->change(QPointF(0.0, 0.0), QPointF(0.0, 0.0));
				leftUpRect->show();
				rightDownRect->change(QPointF(0.0, 0.0), QPointF(0.0, 0.0));
				rightDownRect->show();
				//leftLeftUpPos = event->pos();
			}
		}
		else if(event->button() == Qt::RightButton)
		{
			cleanUp();
			adjustRectangle = false;
		}
		else
		{
		}
	}

	//mouseMoveEvent(event);
}

void PicView::mouseMoveEvent(QMouseEvent *event)
{
	cout<<"========="<<endl;
	if(ignoreInput)
	{
		cout<<"ignore-------"<<endl;
		return;
	}
	leftCurPos = event->pos();
	if(paraSelected)
	{
	}
	if(bezierSelected)
	{
		if(leftMouseDown == true)
		{
			if(selectedBZPoint == 1)
			{
				bezierPoint[2]->change(QPointF(leftCurPos.x() - 5, leftCurPos.y() - 5), QPointF(leftCurPos.x() + 5, leftCurPos.y() + 5));
				bezierPoint[2]->show();
				curve->change(bezierPoint[0],bezierPoint[2],bezierPoint[3],bezierPoint[1]);
				curve->show();
				cout<<"bezierPoint[2]: "<<"leftUp: "<<bezierPoint[2]->leftUp().x()<<"  "<<bezierPoint[2]->leftUp().y()<<"rightDown: "<<bezierPoint[2]->rightDown().x()<<"  "<<bezierPoint[2]->rightDown().y()<<endl;
			}
			else if(selectedBZPoint == 2)
			{
				bezierPoint[3]->change(QPointF(leftCurPos.x() - 5, leftCurPos.y() - 5), QPointF(leftCurPos.x() + 5, leftCurPos.y() + 5));
				bezierPoint[3]->show();
				curve->change(bezierPoint[0],bezierPoint[2],bezierPoint[3],bezierPoint[1]);
				curve->show();
				cout<<"bezierPoint[3]: "<<"leftUp: "<<bezierPoint[3]->leftUp().x()<<"  "<<bezierPoint[3]->leftUp().y()<<"rightDown: "<<bezierPoint[3]->rightDown().x()<<"  "<<bezierPoint[3]->rightDown().y()<<endl;
			}
			else
			{
				cout<<"mousedown and selectedBZPoint = 0"<<endl;
				selectedBZPoint = 0;
				if(bezierPoint[2]->withinRect(leftCurPos))
				{
					selectedBZPoint = 1;
					cout<<"selectedBZPoint is :"<<selectedBZPoint<<endl;
					bezierPoint[2]->changeColour(true);
					bezierPoint[2]->show();
				}
				else if(bezierPoint[3]->withinRect(leftCurPos))
				{
					selectedBZPoint = 2;
					cout<<"selectedBZPoint is :"<<selectedBZPoint<<endl;
					bezierPoint[3]->changeColour(true);
					bezierPoint[3]->show();
				}
			}
		}
		else
		{
			selectedBZPoint = 0;
			if(bezierPoint[2]->withinRect(leftCurPos))
			{
				selectedBZPoint = 1;
				cout<<"selectedBZPoint is :"<<selectedBZPoint<<endl;
				bezierPoint[2]->changeColour(true);
				bezierPoint[2]->show();
			}
			else if(bezierPoint[3]->withinRect(leftCurPos))
			{
				selectedBZPoint = 2;
				cout<<"selectedBZPoint is :"<<selectedBZPoint<<endl;
				bezierPoint[3]->changeColour(true);
				bezierPoint[3]->show();
			}
			else
			{
				bezierPoint[2]->changeColour(false);
				bezierPoint[2]->show();
				bezierPoint[3]->changeColour(false);
				bezierPoint[3]->show();
			}
			cout<<"curleftpos :"<<leftCurPos.x()<<"  "<<leftCurPos.y()<<endl;
			cout<<"bezierPoint[2]: "<<"leftUp: "<<bezierPoint[2]->leftUp().x()<<"  "<<bezierPoint[2]->leftUp().y()<<"rightDown: "<<bezierPoint[2]->rightDown().x()<<"  "<<bezierPoint[2]->rightDown().y()<<endl;
			cout<<"bezierPoint[3]: "<<"leftUp: "<<bezierPoint[3]->leftUp().x()<<"  "<<bezierPoint[3]->leftUp().y()<<"rightDown: "<<bezierPoint[3]->rightDown().x()<<"  "<<bezierPoint[3]->rightDown().y()<<endl;
			/*
			if(bezierPoint[0]->withinRect(leftCurPos))
			{
				cout<<"in start"<<endl;
			}
			if(bezierPoint[1]->withinRect(leftCurPos))
			{
				cout<<"in end"<<endl;
			}
			*/
				/*
				bezierPoint[2]->changeColour(false);
				bezierPoint[2]->show();
				bezierPoint[3]->changeColour(false);
				bezierPoint[3]->show();
				*/
		}
		cout<<"curleftpos :-------------"<<leftCurPos.x()<<"  "<<leftCurPos.y()<<endl;
	}
	cout<<"curleftpos :++++++++++--"<<leftCurPos.x()<<"  "<<leftCurPos.y()<<endl;
	if(rectSelected)
	{
		static QPointF leftCurPosLast(0.0,0.0);
		rectangle->changeColour(false);
		//	cout<<"leftCurPos--->"<<leftCurPos.x()<<","<<leftCurPos.y()<<endl;
		char buffer[20];
		sprintf(buffer, "X:%.f, Y:%.f", leftCurPos.x(), leftCurPos.y());
		QString con(buffer);
		coordinate->change(leftCurPos, QPointF(0.0, 0.0), con);
		if(leftMouseDown == true)
		{
			QPointF tempLeftUp = leftLeftUpPos;
			QPointF tempRightDown = leftRightDownPos;
			if(adjustRectangle)
			{
				switch(focus)
				{
					case 1:
						leftLeftUpPos = leftCurPos;
						leftUpRect->change(QPointF(leftCurPos.x() - 3, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3, leftCurPos.y() + 3));
						//leftUpRect->show();
						break;
					case 2:
						leftRightDownPos = leftCurPos;
						rightDownRect->change(QPointF(leftCurPos.x() - 3, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3, leftCurPos.y() + 3));
						//rightDownRect->show();
						break;
					case 3:
						leftLeftUpPos.setX(leftCurPos.x());
						break;
					case 4:
						leftLeftUpPos.setY(leftCurPos.y());
						break;
					case 5:
						leftRightDownPos.setX(leftCurPos.x());
						break;
					case 6:
						leftRightDownPos.setY(leftCurPos.y());
						break;
					default:
						leftLeftUpPos = leftCurPos;
						leftRightDownPos = leftCurPos;
						adjustRectangle = false;
						firstDownMove = false;
						break;
				}
			}
			else
			{
				if(firstDownMove)
				{
					leftLeftUpPos = leftCurPos;
					leftRightDownPos = leftCurPos;
					adjustRectangle = false;
					firstDownMove = false;
				}
				else
				{
					leftRightDownPos = leftCurPos;
				}
			}
			if(leftLeftUpPos.x() <= leftRightDownPos.x() && leftLeftUpPos.y() <= leftRightDownPos.y())
			{
				rectangle->change(leftLeftUpPos, leftRightDownPos);
				rectangle->show();
				//circle->change(leftLeftUpPos, leftRightDownPos);
				//circle->show();
			}
			else
			{
				leftLeftUpPos = tempLeftUp;
				leftRightDownPos = tempRightDown;
			}
			//update
		}
		else
		{
			focus = 0;
			QPointF point1 = rectangle->leftUp();
			QPointF point2 = rectangle->rightDown();
			int angleResult = rectangle->isAngle(leftCurPos);
			int edgeResult = rectangle->belongToEdge(leftCurPos);
			leftUpRect->change(QPointF(0.0,0.0), QPointF(0.0, 0.0));
			rightDownRect->change(QPointF(0.0,0.0), QPointF(0.0, 0.0));
			if(angleResult != 0)
			{
				if(angleResult == 1)
				{
					focus = 1;
					leftUpRect->change(QPointF(leftLeftUpPos.x() - 3, leftLeftUpPos.y() - 3), QPointF(leftLeftUpPos.x() + 3, leftLeftUpPos.y() + 3));
					//leftUpRect->change(QPointF(leftCurPos.x() - 3, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3, leftCurPos.y() + 3));
				}
				else
				{
					focus = 2;
					rightDownRect->change(QPointF(leftRightDownPos.x() - 3, leftRightDownPos.y() - 3), QPointF(leftRightDownPos.x() + 3, leftRightDownPos.y() + 3));
					//rightDownRect->change(QPointF(leftCurPos.x() - 3, leftCurPos.y() - 3), QPointF(leftCurPos.x() + 3, leftCurPos.y() + 3));
				}
			}
			else if(edgeResult != 0)
			{
				//just change color and show
				switch(edgeResult)
				{
					case 1:
						focus = 3;
						break;
					case 2:
						focus = 4;
						break;
					case 3:
						focus = 5;
						break;
					case 4:
						focus = 6;
						break;
					default:
						break;
				}
				rectangle->changeColour(true);
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
	if(paraSelected)
	{
	}
	if(bezierSelected)
	{
		if(event->button() == Qt::LeftButton)
		{
			leftMouseDown = false;
			selectedBZPoint = 0;
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
			focus = 0;
			QPointF point = event->pos();
			if(MyAbs(point.x() - leftLeftUpPos.x()) < 1.0 && MyAbs(point.y() - leftLeftUpPos.y()) < 1.0)
			{
			}
			else
			{
				adjustRectangle = true;
			}
			leftMouseDown = false;
			firstDownMove = true;
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
		cleanUp();
		update();
		emit imageUnwrapped(&img);
		rectangle->show();
		leftUpRect->show();
		rightDownRect->show();
		coordinate->show();
	}
}
void PicView::resizeEvent(QResizeEvent *e)
{
	emit hasBeenResized(e->size());
}
/*
QPointF PicView::calcCircCentre(QPointF leftUp, QPointF rightDown)
{
}

qreal PicView::calcLongDiameter(QPointF leftUp, QPointF rightDown)
{
}
qreal PicView::calcShortDiameter(QPointF leftUp, QPointF rightDown)
{

}
*/
void PicView::cleanUp()
{
	rectangle->hide();
	leftUpRect->hide();
	rightDownRect->hide();
	if(!img.isNull())
	{
		ignoreInput = false;
	}
	emit cleanedUp();
}
