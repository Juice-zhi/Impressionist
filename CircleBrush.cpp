//
// CircleBrush.cpp
//
// The implementation of Circle Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"
#include<cmath>

extern float frand();

CircleBrush::CircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void CircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("CircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	glBegin(GL_LINES);
		SetColor(source, target);

		for (int i = 0;i < 1000;i++) {
			glVertex2d(target.x+(size/2)*cos(2 * M_PI * i / 1000.0), target.y+(size/2)*sin(2 * M_PI * i / 1000.0));
			glVertex2d(target.x - (size/2)*cos(2 * M_PI * i / 1000.0), target.y - (size/2)*sin(2 * M_PI * i / 1000.0));
		}
	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}