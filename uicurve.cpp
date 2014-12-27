#include <QtGui>
#include <QPainterPath>
#include "uicurve.h"
#include "uirectangle.h"
typedef UiRectangle*  pUiRectangle;
UiCurve::UiCurve(QWidget *parent):UiElement(parent)
{
	resize(parent->size());
	activeColour = false;
	points = new pUiRectangle[4];
	
	setMouseTracking(true);
}

void UiCurve::change()
{
	update();
}
void UiCurve::change(UiRectangle* p1, UiRectangle* p2, UiRectangle* p3, UiRectangle* p4)
{
	/*
	*points[0] = *p1;
	*points[1] = *p2;
	*points[2] = *p3;
	*points[3] = *p4;
	*/
	//fitCurve(points);
	update();
}

void UiCurve::paintEvent(QPaintEvent *)
{
	QPainter painter(this);
	if(activeColour)
		painter.setPen(Qt::blue);
	else 
		painter.setPen(Qt::green);
	QPainterPath curvePath;
	curvePath.moveTo(points[0]->centre());
	curvePath.cubicTo(points[2]->centre(), points[3]->centre(), points[1]->centre());
	painter.drawPath(curvePath);
}
