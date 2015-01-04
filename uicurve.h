#ifndef UICURVE_H
#define UICURVE_H
#include "uielement.h"
#include "uirectangle.h"
#include <iostream>
class QPainterPath;
class UiRectangle;
class UiCurve : public UiElement
{
	Q_OBJECT
	public:
		UiCurve(QWidget *parent);
		void change(UiRectangle* p1, UiRectangle* p2, UiRectangle* p3, UiRectangle* p4);
		void change();
		UiRectangle** Points(){return points;}
		void setFocusPoint(int i, QPointF point)
		{
			setFocus(i);
			setFocusPoint(point);
		}
		void setFocusPoint(QPointF point)
		{
			points[focusPoint - 1]->change(QPointF(point.x() - 3, point.y() - 3), QPointF(point.x() + 3, point.y() + 3));
		}
		UiRectangle* pFocusPoint(int i)
		{
			if(i > 0 && i < 5)
			{
				return points[i - 1];
			}
			else
			{
				std::cout<<"invalid parameter in UiCurve::pFocusPoint(int i)"<<std::endl;
				return NULL;
			}
		}
		void setFocus(int i)
		{
			focusPoint = i;
		}

		int getFocus()
		{
			return focusPoint;
		}
		UiRectangle* pFocusPoint()
		{
			return pFocusPoint(focusPoint);
		}
	protected:
		void paintEvent(QPaintEvent *);
	
	private:
		std::vector<QPointF>pointArray;
		//std::vector<UiRectangle> points;
		UiRectangle** points;
		bool activeColour;
		int focusPoint;
};
#endif
