/****************************************************************************************
 * Copyright (c) 2010                                                                   *
 * Michael Boyd <mb109@doc.ic.ac.uk>, Dragos Carmaciu <dc2309@doc.ic.ac.uk>,            *
 * Francis Giannaros <kg109@doc.ic.ac.uk>, Thomas Payne <tp1809@doc.ic.ac.uk> and       *
 * William Snell <ws1309@doc.ic.ac.uk>.                                                 *
 *   Students at Imperial College London <http://imperial.ac.uk/computing>              *
 *                                                                                      *
 * This program is free software; you can redistribute it and/or modify it under        *
 * the terms of the GNU General Public License as published by the Free Software        *
 * Foundation; either version 2 of the License, or (at your option) any later           *
 * version.                                                                             *
 *                                                                                      *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY      *
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A      *
 * PARTICULAR PURPOSE. See the GNU General Public License for more details.             *
 * You should have received a copy of the GNU General Public License along with         *
 * this program.  If not, see <http://www.gnu.org/licenses/>.                           *
 ****************************************************************************************/

#include <QtGui>
#include "uirectangle.h"
using std::cout;
using std::endl;
static const float THRESHOLD = 3.0;
static inline float MyAbs(float a)
{
	return (a > 0 ? a : (0 - a));
}
static inline float MaxValue(float a, float b)
{
	return (a > b ? a : b);
}
static inline float MinValue(float a, float b)
{
	return (a < b ? a : b);
}
static inline bool between(float mid, float low, float high)
{
	if(mid < high && mid > low)
	{
		return true;
	}
	return false;
}
UiRectangle::UiRectangle(QWidget *parent) : UiElement(parent){
    resize(parent->size());
	activeColour = false;
	setRecColor(Qt::blue);
	setCirColor(Qt::green);
	setMouseTracking(true);
}
UiRectangle::UiRectangle(QWidget *parent, QPointF leftUp, QPointF rightDown) : UiElement(parent), _leftUp(leftUp), _rightDown(rightDown) {
    resize(parent->size());
	activeColour = false;
	setRecColor(Qt::blue);
	setCirColor(Qt::green);
	setMouseTracking(true);
}
/*
UiRectangle::~UiRectangle()
{
}
*/

void UiRectangle::paintEvent(QPaintEvent *) {
    QPainter painter(this);
	/*
	if(activeColour)
		painter.setPen(Qt::blue);
	else 
		painter.setPen(Qt::green);
		*/
	painter.setPen(recColor);
	painter.drawRect(QRectF(_leftUp, _rightDown));
	activeColour = !activeColour;
	/*
	if(activeColour)
		painter.setPen(Qt::blue);
	else 
		painter.setPen(Qt::green);
		*/
	painter.setPen(cirColor);
	painter.drawEllipse(QRectF(_leftUp, _rightDown));
	activeColour = !activeColour;
}
void UiRectangle::change()
{
	_centre = QPointF(_leftUp.x() + (_rightDown.x() - _leftUp.x())/2.0,_leftUp.y() + (_rightDown.y() - _leftUp.y())/2.0);
	_leftUp = leftUpRect->centre();
	_rightDown = rightDownRect->centre();
    update();
}
void UiRectangle::change(QPointF leftUp, QPointF rightDown) {
	_leftUp = leftUp;
	_rightDown = rightDown;
	_centre = QPointF(_leftUp.x() + (_rightDown.x() - _leftUp.x())/2.0,_leftUp.y() + (_rightDown.y() - _leftUp.y())/2.0);
    update();
}

qreal UiRectangle::width()
{
	return (_rightDown.x() - _leftUp.x());
}
qreal UiRectangle::height()
{
	return (_rightDown.y() - _leftUp.y());
}
void UiRectangle::changeColour(bool i) {
	if(!i)
		activeColour = false;
	else
		activeColour = true;
	update();
}

bool UiRectangle::withinRect(const QPointF &point)
{
//	if(point.x() >= _leftUp.x() && point.y() >= _leftUp.y() && point.x() <= _rightDown.x() && point.y() <= _rightDown.y())
	if(point.x() > _leftUp.x() && point.x() < _rightDown.x() && point.y() > _leftUp.y() && point.y() < _rightDown.y())
	{
		cout<<"mouse move in uirectangle"<<endl;
		return true;
	}
	else
	{
		return false;
	}
}
bool UiRectangle::isCentre(const QPointF &point)
{
	if(MyAbs(centre().x() - point.x()) < THRESHOLD && MyAbs(centre().y() - point.y()) < THRESHOLD)
	{
		cout<<"is centrl"<<endl;
		return true;
	}
}

int UiRectangle::isAngle(const QPointF &point)
{
	if(MyAbs(_leftUp.x() - point.x()) < THRESHOLD && MyAbs(_leftUp.y() - point.y()) < THRESHOLD)
	{
		return 1;
	}
	else if(MyAbs(_rightDown.x() - point.x()) < THRESHOLD && MyAbs(_rightDown.y() - point.y()) < THRESHOLD)
	{
		return 2;
	}
	else if(false)
	{
		return 3;
	}
	else if(false)
	{
		return 4;
	}
	else
	{
		return 0;
	}
}
int UiRectangle::belongToEdge(const QPointF &point)
{
	//be careful, this is compare of two float type value
	if(MyAbs(_leftUp.x() - point.x()) < THRESHOLD)
	{
		if(between(point.y(), MinValue(_leftUp.y(), _rightDown.y()), MaxValue(_leftUp.y(), _rightDown.y())))
		{
			return 1;
		}
		return 0;
	}
	else if(MyAbs(_leftUp.y() - point.y()) < THRESHOLD)
	{
		if(between(point.x(), MinValue(_leftUp.x(), _rightDown.x()), MaxValue(_leftUp.x(), _rightDown.x())))
		{
			return 2;
		}
		return 0;
	}
	else if(MyAbs(_rightDown.x() - point.x()) < THRESHOLD)
	{
		if(between(point.y(), MinValue(_leftUp.y(), _rightDown.y()), MaxValue(_leftUp.y(), _rightDown.y())))
		{
			return 3;
		}
		return 0;
	}
	else if(MyAbs(_rightDown.y() - point.y()) < THRESHOLD)
	{
		if(between(point.x(), MinValue(_leftUp.x(), _rightDown.x()), MaxValue(_leftUp.x(), _rightDown.x())))
		{
			return 4;
		}
		return 0;
	}
	else
	{
		return 0;
	}
}
