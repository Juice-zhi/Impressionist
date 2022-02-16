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
#include <stdlib.h>
#include <map>
#include <stdio.h>

extern float frand();

ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void ScatteredPointBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;


	glPointSize(1);

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

	srand((unsigned)time(NULL));
	int num = (rand() % (maxNum - minNum + 1)) + minNum;
	//OutputDebugStringA("test");

	glBegin(GL_POINT);
		for (int i = 0; i < num; ++i) {
			int pos;
			do {
				pos = rand() % (size * size);
			} while (visited[pos]);
			visited[pos] = true;
			
			/*SetColor(Point(source.x + pos % size - 2, source.y - pos / size + 2));
			glVertex2d(target.x + pos % size - 2, target.y - pos / size + 2);*/
			SetColor(source);
			glVertex2d(target.x, target.y);
		}
	glEnd();
}

void ScatteredPointBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

