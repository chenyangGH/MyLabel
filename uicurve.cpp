#include <QtGui>
#include <QPainterPath>
#include "uicurve.h"
#include "uirectangle.h"
UiCurve::UiCurve(QWidget *parent):UiElement(parent)
{
	resize(parent->size());
	activeColour = false;
	setMouseTracking(true);
}

void UiCurve::change()
{
	update();
}
void UiCurve::change(UiRectangle* p1, UiRectangle* p2, UiRectangle* p3, UiRectangle* p4)
{
	points[0] = p1->centre();
	points[1] = p2->centre();
	points[2] = p3->centre();
	points[3] = p4->centre();
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
	curvePath.moveTo(points[0]);
	curvePath.cubicTo(points[2], points[3], points[1]);
	painter.drawPath(curvePath);
}
