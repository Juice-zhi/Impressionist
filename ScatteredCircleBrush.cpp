//
// ScatteredCircleBrush.cpp
//
// The implementation of ScatteredCircleBrush Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredCircleBrush.h"
#include <math.h>
#include <time.h>


extern float frand();

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredCircleBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	BrushMove(source, target);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredCircleBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	srand((unsigned)time(NULL) + source.x * source.y);
	int num = rand() % 4 + 1;

	glBegin(GL_LINES);
	for (int i = 0; i < num; ++i) {
		int radius = rand() % (size / 2) + 1;
		int x = rand() % size - size / 2;
		int y = (int)sqrt(radius * radius - x * x);
		if ((source.x + source.y) % 2 == 0) {
			y *= -1;
		}

		SetColor(Point(source.x + x, source.y + y));

		for (int i = 0; i < 1000; i++) {
			glVertex2d(target.x + x + (size / 2) * cos(2 * M_PI * i / 1000.0), target.y + y + (size / 2) * sin(2 * M_PI * i / 1000.0));
			glVertex2d(target.x + x - (size / 2) * cos(2 * M_PI * i / 1000.0), target.y + y - (size / 2) * sin(2 * M_PI * i / 1000.0));
		}
	}
	glEnd();
}

void ScatteredCircleBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

