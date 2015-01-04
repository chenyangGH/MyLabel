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
#include "picview.h"
#include "mainview.h"

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;
MainView::MainView(QWidget *parent) : QWidget(parent) {

    //set up boxes for layout
    leftWidget = new QWidget(this);
    PicBox = new QFrame(leftWidget);
    PicBox->setFrameShape(QFrame::Panel);
    PicBox->setFrameShadow(QFrame::Raised);
    PicBox->setFixedSize(330,290);

    // Tabs on the bottom:
    bottomBox = new QTabWidget(leftWidget);
    bottomBox->setFixedSize(328, 108);
    bottomBox->setVisible(false);


    altimgBox = new QLabel();
    altimgBox->setMargin(2);

    heatimgBox = new QLabel();
    heatimgBox->setMargin(2);
    sideBox = new QWidget(this);


    view = new PicView(PicBox);
    view->setGeometry(4,4,320,280);
    connect(view, SIGNAL(hasBeenResized(QSize)), this, SLOT(resizePicBox(QSize)));
	makeSureButton = new QPushButton("&Save and next", sideBox);
	makeSureButton->setEnabled(false);

	addBezButton = new QPushButton("&add bezier", sideBox);
	addRecButton = new QPushButton("&add rect", sideBox);
	addParaButton = new QPushButton("&add para", sideBox);
	clearAllButton = new QPushButton("&clearAll", sideBox);
	
    notes = new QLabel("Use the File menu to load an iris image.", sideBox);
    notes->setWordWrap(true);
    notes->setFixedWidth(120);
    notes->setFrameShape(QFrame::Panel);
    notes->setFrameShadow(QFrame::Raised);

    //create a progress bar for the processing and then hide it until relevant
	

    sideLayout = new QVBoxLayout(sideBox);
    sideLayout->addWidget(notes);
    sideLayout->addStretch();
    sideLayout->addWidget(makeSureButton);
    sideLayout->addWidget(addBezButton);
    sideLayout->addWidget(addRecButton);
    sideLayout->addWidget(addParaButton);
	sideLayout->addWidget(clearAllButton);
    leftLayout = new QVBoxLayout(leftWidget);
    leftLayout->addWidget(PicBox);
    leftLayout->addStretch();
    leftLayout->addWidget(bottomBox);
    mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(leftWidget);
    mainLayout->addStretch();
    mainLayout->addWidget(sideBox);

    // Add tabs:
    bottomBox->addTab(altimgBox, "&Unwrapped");
    bottomBox->addTab(heatimgBox, "H&eatmap");

    connect(view, SIGNAL(imageUnwrapped(QImage*)), this, SLOT(imageUnwrapped(QImage*)));
    connect(view, SIGNAL(PicFound()), this, SLOT(enableButtons()));
    connect(view, SIGNAL(cleanedUp()), this, SLOT(cleanedUp()));
    connect(makeSureButton, SIGNAL(clicked()), this, SLOT(on_makeSureButton_clicked()));

    connect(addBezButton, SIGNAL(clicked()), this, SLOT(on_addBezButton_clicked()));
    connect(addRecButton, SIGNAL(clicked()), this, SLOT(on_addRecButton_clicked()));
    connect(addParaButton, SIGNAL(clicked()), this, SLOT(on_addParaButton_clicked()));
    connect(clearAllButton, SIGNAL(clicked()), this, SLOT(on_clearAllButton_clicked()));

    setLayout(mainLayout);
	resize(sizeHint().width(), sizeHint().height() + 150);
	parent->resize(size());
}
void MainView::on_addBezButton_clicked()
{
	view->addBezier();
}
void MainView::on_addRecButton_clicked()
{
	view->addRect();
}
void MainView::on_addParaButton_clicked()
{
	view->addPara();
}
void MainView::on_clearAllButton_clicked()
{
	view->cleanUp();
}
void MainView::on_makeSureButton_clicked()
{
	/*
	QPointF leftUp = view->getLeftTopLeft();
	QPointF rightDown = view->getLeftBottomRight();
	cout<<"leftup_X: "<<leftUp.x()<<"   leftUp_Y: "<<leftUp.y()<<endl;
	cout<<"rightDown_X: "<<rightDown.x()<<"   rightDown_Y: "<<rightDown.y()<<endl;
	*/
	view->computeArc();
	if(fileList.empty())
	{
		std::cout<<"last image in this directory"<<endl;
		makeSureButton->setEnabled(false);
	}
	else
	{
		std::string fileName = fileList.back();
		fileList.pop_back();
		view->loadImage((char*)fileName.c_str());
	}
}
void MainView::changeNotes(const QString &string) {
    notes->setText(string);
}

void MainView::imageUnwrapped(QImage* image) {
    altimgBox->setPixmap(altImg->fromImage(*image));
	// Adjust box's size accordingly
    altimgBox->setFixedSize(image->width() + 9,image->height() + 9);
    //heatimgBox->setFixedSize(heat->width() + 9,heat->height() + 9);
	resize(sizeHint());
	//parent->resize(size());
}

// on irisview's cleanUp(), clear the unwrapped image
// and disable the buttons again.
void MainView::cleanedUp() {
    altimgBox->setPixmap(QPixmap());
    changeNotes("Click on three points on the outer edge of the pupil.");
	makeSureButton->setEnabled(false);
}

void MainView::resizePicBox(QSize newSize) {
	printf("you are resizing PicBox\n");
    PicBox->setFixedSize(newSize.width() + 9, newSize.height() + 9);
}

void MainView::enableButtons() {
	makeSureButton->setEnabled(true);
}

bool MainView::loadImageList(QString directoryName) {
	bool result = false;
	////////////////////////////////
	loadImage();
	////////////////////////////////
	if(fileList.empty())
	{
		std::cout<<"there is no image in this directory"<<endl;
		return false;
	}
	fullFileName = fileList.back();
	fileList.pop_back();
	curFile = QFileInfo(fullFileName).fileName();
	result = view->loadImage(fullFileName);
	return result;
}
