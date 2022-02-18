//
// ScatteredLineBrush.cpp
//
// The implementation of ScatteredLineBrush Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredLineBrush.h"
#include <math.h>
#include <time.h>


extern float frand();

ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredLineBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	int thickness = pDoc->getThickness();

	glLineWidth((float)thickness);

	BrushMove(source, target);
}

void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredLineBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();
	int minNum = size > 14 ? 3 : (size > 4 ? 2 : 1); ///1-4:1 5-14:2 15-40:3
	int maxNum = min(size,4);

	srand((unsigned)time(NULL) + source.x * source.y);
	int num = (rand() % (maxNum - minNum + 1)) + minNum;

	int currentY = size;
	size = int(size * 1.5);
	glBegin(GL_LINES);
		for (int i = 0; i < num; ++i) {
			int pos1 = rand() % (min(size / 3 , 5));
			int pos2 = rand() % (size - pos1 - size * 2 / 3) + pos1 + size * 2 / 3;
			currentY -= rand() % (currentY - num + i) + 1;
			SetColor(Point(source.x + (pos1 + pos2) / 2 - size / 2, source.y + currentY));
			glVertex2d(target.x + pos1 - size / 2, target.y + currentY);
			glVertex2d(target.x + pos2 - size / 2, target.y + currentY);
		}
	glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

