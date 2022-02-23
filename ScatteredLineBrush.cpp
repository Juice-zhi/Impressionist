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
#include <cmath>


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
	int angle = pDoc->getAngle();

	srand((unsigned)time(NULL) + source.x * source.y);
	int num = (rand() % (maxNum - minNum + 1)) + minNum;

	int currentY = size;
	//size = int(size * 1.5);
	glBegin(GL_LINES);
		StartX = target.x;
		StartY = target.y;
		for (int i = 0; i < num; ++i) {
			int pos1 = rand() % (min(size / 3, 5));
			int pos2 = rand() % (size - pos1 - size * 2 / 3) + pos1 + size * 2 / 3;
			currentY -= rand() % (currentY - num + i) + 1;
			SetColor(Point(source.x + (pos1 + pos2) / 2 - size / 2, source.y + currentY), Point(target.x + (pos1 + pos2) / 2 - size / 2, target.y + currentY));
			if (pDoc->get_Direction_Choice() == SLIDER_OR_RIGHT_MOUSE) {
				glVertex2d(target.x - (size / 2) * cos(angle * M_PI / 180) + pos1, target.y - (size / 2) * sin(angle * M_PI / 180) + currentY);
				glVertex2d(target.x + (size / 2) * cos(angle * M_PI / 180) + pos2, target.y + (size / 2) * sin(angle * M_PI / 180) + currentY);
				EndX = target.x;
				EndY = target.y;
			}
			else if (pDoc->get_Direction_Choice() == GRADIENT) {
				GLubyte sourceColor[3];
				double X_Gradient = 0.0;
				double Y_Gradient = 0.0;
				memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y), 3);
				X_Gradient = X_Gradient - (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
				Y_Gradient = Y_Gradient - (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
				memcpy(sourceColor, pDoc->GetOriginalPixel(source.x + 1, source.y), 3);
				X_Gradient = X_Gradient + (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
				memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y + 1), 3);
				Y_Gradient = Y_Gradient + (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
				double absolute_change;
				absolute_change = sqrt(X_Gradient * X_Gradient + Y_Gradient * Y_Gradient);
				glVertex2d(target.x + ((size / 2) * Y_Gradient / absolute_change), target.y - (size / 2) * X_Gradient / absolute_change);
				glVertex2d(target.x - ((size / 2) * Y_Gradient / absolute_change), target.y + (size / 2) * X_Gradient / absolute_change);
				EndX = target.x;
				EndY = target.y;
			}
			else {
				double distance = sqrt((EndX - StartX) * (EndX - StartX) + (EndY - StartY) * (EndY - StartY));
				glVertex2d(target.x - (size / 2) * (EndX - StartX) / distance + pos2, target.y - (size / 2) * (EndY - StartY) / distance + currentY);
				glVertex2d(target.x + (size / 2) * (EndX - StartX) / distance + pos2, target.y + (size / 2) * (EndY - StartY) / distance + currentY);
				EndX = target.x;
				EndY = target.y;
			}
		}
	glEnd();
}

void ScatteredLineBrush::BrushEnd(const Point source, const Point target)
{
	EndX = target.x;
	EndY = target.y;
}

