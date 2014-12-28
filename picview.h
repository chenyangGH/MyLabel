#ifndef PICVIEW_H
#define PICVIEW_H
#include <QWidget>

//class UiCircle;
class UiRectangle;
class UiCoordinate;
class UiCurve;
class UiElement;
class PicView : public QWidget
{
	Q_OBJECT
	public:
		PicView(QWidget *parent);
		bool loadImage(const QString filename);
		void cleanUp();
		QPointF getLeftTopLeft(){return leftLeftUpPos;}
		QPointF getLeftBottomRight(){return leftRightDownPos;}
		void setLeftArc(QPointF * pointer){leftArc = pointer; }
		void setRightArc(QPointF * pointer){rightArc = pointer; }
		void computeArc();

		void addBezier();
		void addPara();
		void addRect();
		void delBezier();
		void delPara();
		void delRect();

		UiCurve* addCurve();
		void delCurve(UiCurve* curve);
		UiRectangle* addRectangle();
	protected:
		void keyPressEvent(QKeyEvent  *event);
		void paintEvent(QPaintEvent *);
		void mousePressEvent(QMouseEvent *);
		void mouseMoveEvent(QMouseEvent *);
		void mouseReleaseEvent(QMouseEvent *);
		void resizeEvent(QResizeEvent *);
signals:
		void hasBeenResized(QSize size);
		void cleanedUp();
		void PicFound();
		void imageUnwrapped(QImage*);
	private:
		int edgeFocus;
		bool ignoreInput;
		bool leftMouseDown;
		bool cleared;
		bool bezierSelected;
		bool paraSelected;
		bool rectSelected;
		QPointF* leftArc;
		QPointF* rightArc;
		int arcLength;
		QPointF leftLeftUpPos;
		QPointF leftCurPos;
		QPointF leftRightDownPos;
		UiRectangle *rectangle;

		UiCurve *curve;

		int endpointNum;

		UiCoordinate *coordinate;
		QString fileName;
		QImage img;

		UiElement* pElement;
		std::vector<UiCurve*> curveVector;
		std::vector<UiRectangle*> rectangleVector;
};
#endif
