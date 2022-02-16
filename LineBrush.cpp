//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

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

	int size = pDoc->getSize();
	int thickness = pDoc->getThickness();
	int angle = pDoc->getAngle();


	glPointSize((float)size);
	glLineWidth(thickness);
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
		SetColor(source);
		glVertex2d(target.x - ((size / 2)*cos(angle*M_PI/180)), target.y-(size/2)*sin(angle*M_PI/180));
		glVertex2d(target.x + ((size / 2)*cos(angle*M_PI/180)), target.y+(size/2)*sin(angle*M_PI/180));
	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}