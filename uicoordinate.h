#ifndef UICOORDINATE_H
#define UICOORDINATE_H
#include "uielement.h"
class UiCoordinate : public UiElement
{
    Q_OBJECT
	public:
		UiCoordinate(QWidget *parent, const QPointF& leftUp, const QPointF& rightDown);
		UiCoordinate(QWidget *parent, const QRectF& rect);
		void change(const QPointF& leftUp, const QPointF& rightDown, const QString& content);
		void change(const QRectF& rect, const QString& content);
		void changeColour(bool i);
	protected:
		void paintEvent(QPaintEvent *);
	private:
		QString _content;
		QPointF _leftUp;
		QPointF _rightDown;
		QRectF _rect;
		bool activeColour;
};
#endif
