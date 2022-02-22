//
// StarBrush.cpp
//
// The implementation of Star Brush. It is a kind of ImpBrush.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "StarBrush.h"
#include <math.h>
#include <time.h>

extern float frand();

StarBrush::StarBrush(ImpressionistDoc* pDoc, char* name) :
	ImpBrush(pDoc, name)
{
}

void StarBrush::BrushBegin(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	glPointSize(float(1));

	BrushMove(source, target);
}

void StarBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg = pDoc->m_pUI;

	if (pDoc == NULL) {
		printf("StarBrush::BrushMove  document is NULL\n");
		return;
	}

	int size = pDoc->getSize();

	srand((unsigned)time(NULL) + source.x * source.y);

	glBegin(GL_POINTS);
		for (int i = -size / 2; i <= size / 2; ++i) {
			for (int j = -size / 2; j <= size / 2; ++j) {
				if (sqrt(i * i + j * j) > size / 2) {
					continue;
				}
				int possibility = int(size / 6 / sqrt(j * j + i * i) * 1000);
				if (rand() % 3000 < possibility) {
					SetColor(Point(source.x + j, source.y + i), Point(target.x + i, target.y + j));
					glVertex2d(target.x + i, target.y + j);
				}
			}
		}
	glEnd();
}

void StarBrush::BrushEnd(const Point source, const Point target)
{
	// do nothing so far
}

