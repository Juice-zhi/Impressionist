//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "LineBrush.h"
#include<cmath>

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



	glPointSize((float)size);

	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;
	int size = pDoc->getSize();

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	//glBegin(GL_POINTS);
	//SetColor(source);

	//glVertex2d(target.x, target.y);
	//glEnd();


	glBegin(GL_LINES);
	SetColor(source);

	glVertex2d(target.x - size, target.y);
	glVertex2d(target.x + size, target.y);
	glEnd();

	//glBegin(GL_LINES);
	//SetColor(source);
	//for (int i = 0;i < 1000;i++) {
		//glVertex2d(target.x + (size / 2) * cos(2 * M_PI * i / 1000.0), target.y + (size / 2) * sin(2 * M_PI * i / 1000.0));
		//glVertex2d(target.x - (size / 2) * cos(2 * M_PI * i / 1000.0), target.y - (size / 2) * sin(2 * M_PI * i / 1000.0));
	//}
	//glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}