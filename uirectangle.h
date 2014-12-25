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

#ifndef UICIRCLE_H
#define UICIRCLE_H

#include "uielement.h"

class UiRectangle : public UiElement {
    Q_OBJECT
public:
    UiRectangle(QWidget *parent, QPointF leftUp, QPointF rightDown);
	UiRectangle(QWidget *parent);

    void change(QPointF leftUp, QPointF rightDown);
	void change();

    qreal width();
	qreal height();
	// If true, changes colour to non-default colour
	void changeColour(bool i);
	int isAngle(const QPointF &point);
	bool isCentre(const QPointF &point);
	bool withinRect(const QPointF &point);
	int belongToEdge(const QPointF &point);

    QPointF centre(){return _centre;}
	QPointF leftUp(){return _leftUp;}
	QPointF rightDown(){return _rightDown;}
	QPointF &rCentre(){return _centre;}
	QPointF &rLeftUp(){return _leftUp;}
	QPointF &RightDown(){return _rightDown;}

protected:
	void paintEvent(QPaintEvent *);
private:
    QPointF _centre;

	QPointF _leftUp;
	QPointF _rightDown;
	// Whether the active colour (as opposed to the inactive colour
	// should be set)
	bool activeColour;
};

#endif // UICIRCLE_H
