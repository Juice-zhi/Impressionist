//
// ScatteredPointBrush.cpp
//
// The implementation of ScatteredPointBrush Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ScatteredPointBrush.h"
#include <math.h>
#include <time.h>


extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize((float)1);

	BrushMove(source, target);
}

void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("ScatteredPointBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	int minNum = (int)floor(size * size / 7);
	int maxNum = (int)ceil(size * size / 5);

	srand((unsigned)time(NULL) + source.x * source.y);
	int num = (rand() % (maxNum - minNum + 1)) + minNum;

	glBegin(GL_POINTS);
		for (int i = 0; i < num; ++i) {
			int pos = rand() % (size * size);
			SetColor(Point(source.x + pos % size - 2, source.y - pos / size + 2), Point(target.x + pos % size - 2, target.y - pos / size + 2));
			glVertex2d(target.x + pos % size - 2, target.y - pos / size + 2);
		}
	glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

