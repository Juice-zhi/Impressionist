//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include<iostream>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include <cmath>

extern float frand();

LineBrush::LineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int thickness = pDoc->getThickness();
	int angle = pDoc->getAngle();

	//StartX = target.x;
	//StartY = target.y;
	glLineWidth((float)thickness);
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int size = pDoc->getSize();
	int thickness = pDoc->getThickness();
	int angle = pDoc->getAngle();

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	glBegin(GL_LINES);
		SetColor(source, target);
		StartX = target.x;
		StartY = target.y;
		
		if (pDoc->get_Direction_Choice() == 0) {
			
			glVertex2d(target.x - ((size / 2) * cos(angle * M_PI / 180)), target.y - (size / 2) * sin(angle * M_PI / 180));
			glVertex2d(target.x + ((size / 2) * cos(angle * M_PI / 180)), target.y + (size / 2) * sin(angle * M_PI / 180));
			EndX = target.x;
			EndY = target.y;
		}
		else if (pDoc->get_Direction_Choice() == 1) {

		}
		else {
			
			double distance = sqrt((EndX-StartX)*(EndX-StartX)+(EndY-StartY)*(EndY-StartY));
			glVertex2d(target.x - ((size / 2) *(EndX-StartX)/distance ), target.y - (size / 2) * (EndY-StartY)/distance);
			glVertex2d(target.x + ((size / 2) *(EndX-StartX)/distance ), target.y + (size / 2) * (EndY-StartY)/distance);
			EndX = target.x;
			EndY = target.y;
			
		}
	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	EndX = target.x;
	EndY = target.y;
}