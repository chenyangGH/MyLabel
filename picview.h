#ifndef PICVIEW_H
#define PICVIEW_H
#include <QWidget>

//class UiCircle;
class UiRectangle;
class UiCoordinate;
class UiCurve;
class PicView : public QWidget
{
	Q_OBJECT
	public:
		PicView(QWidget *parent);
		bool loadImage(const QString filename);
		void cleanUp();
		void drawCircle();
		void drawRectangle();
		int getArcLength(){return arcLength; }
		void getArcLength(int length){arcLength = length; }
		QPointF getLeftTopLeft(){return leftLeftUpPos;}
		QPointF getLeftBottomRight(){return leftRightDownPos;}
		QPointF* getLeftArc(){return leftArc; }
		QPointF* getRightArc(){return rightArc; }
		void setLeftArc(QPointF * pointer){leftArc = pointer; }
		void setRightArc(QPointF * pointer){rightArc = pointer; }
		void computeArc();

		void selectBezier();
		void selectPara();
		void selectRect();
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
		bool firstDownMove;
		bool ignoreInput;
		bool leftMouseDown;
		bool cleared;
		bool adjustRectangle;
		bool bezierSelected;
		bool paraSelected;
		bool rectSelected;
		int selectedBZPoint;
		QPointF* leftArc;
		QPointF* rightArc;
		int arcLength;
		int focus;
		QPointF leftLeftUpPos;
		QPointF leftCurPos;
		QPointF leftRightDownPos;
		//UiCircle* circle;
		UiRectangle *rectangle;
		UiRectangle *leftUpRect;
		UiRectangle *rightDownRect;

		UiCurve *curve;

		UiRectangle *bezierPoint[4];
		int endpointNum;

		UiCoordinate *coordinate;
		QString fileName;
		QPointF calcCircCentre(QPointF leftUp, QPointF rightDown);
		qreal calcLongDiameter(QPointF leftUp, QPointF rightDown);
		qreal calcShortDiameter(QPointF leftUp, QPointF rightDown);
		QImage img;
		qreal shortDiameter;
		qreal longDiameter;

};
#endif
