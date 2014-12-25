#ifndef UICURVE_H
#define UICURVE_H
#include "uielement.h"
class QPainterPath;
class UiRectangle;
class UiCurve : public UiElement
{
	Q_OBJECT
	public:
		UiCurve(QWidget *parent);
		void change(UiRectangle* p1, UiRectangle* p2, UiRectangle* p3, UiRectangle* p4);
		void change();
		QPointF* Points(){return points;}
	protected:
		void paintEvent(QPaintEvent *);
	private:
		std::vector<QPointF>pointArray;
		QPointF points[4];
		bool activeColour;
};
#endif
