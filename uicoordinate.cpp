#include <QtGui>
#include "uicoordinate.h"
UiCoordinate::UiCoordinate(QWidget *parent, const QPointF& leftUp, const QPointF& rightDown) : UiElement(parent), _leftUp(leftUp), _rightDown(rightDown), _rect(leftUp, rightDown)
{
	resize(parent->size());
	activeColour = false;
	setMouseTracking(true);
}
UiCoordinate::UiCoordinate(QWidget *parent,const QRectF& rect) : UiElement(parent), _leftUp(rect.topLeft()), _rightDown(rect.bottomRight()), _rect(rect)
{
	resize(parent->size());
	activeColour = false;
	setMouseTracking(true);
}
void UiCoordinate::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
	if(activeColour)
		painter.setPen(Qt::yellow);
	else 
		painter.setPen(Qt::red);
	painter.drawText(_leftUp, _content);
	//painter.drawRect(_leftUp.x(), _leftUp.y(), _rightDown.x() - _leftUp.x(), _rightDown.y() - _leftUp.y());
}

void UiCoordinate::change(const QPointF& leftUp, const QPointF& rightDown, const QString& content)
{
	_leftUp = leftUp;
	_rightDown = rightDown;
	_rect.setTopLeft(_leftUp);
	_rect.setBottomRight(_rightDown);
	_content = content;
	update();
}
void UiCoordinate::change(const QRectF& rect, const QString& content)
{
	_rect = rect;
	_leftUp = _rect.topLeft();
	_rightDown = _rect.bottomRight();
	_content = content;
	update();
}

void UiCoordinate::changeColour(bool i)
{
	if(!i)
		activeColour = false;
	else
		activeColour = true;
	update();
}
