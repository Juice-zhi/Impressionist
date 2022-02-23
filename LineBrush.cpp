//
// LineBrush.cpp
//
// The implementation of Line Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//
#include <iostream>
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
		
		if (pDoc->get_Direction_Choice() == SLIDER_OR_RIGHT_MOUSE) {
			
			glVertex2d(target.x - ((size / 2) * cos(angle * M_PI / 180)), target.y - (size / 2) * sin(angle * M_PI / 180));
			glVertex2d(target.x + ((size / 2) * cos(angle * M_PI / 180)), target.y + (size / 2) * sin(angle * M_PI / 180));
			EndX = target.x;
			EndY = target.y;
		}
		else if (pDoc->get_Direction_Choice() == GRADIENT) {
			GLubyte sourceColor[3];
			double X_Gradient = 0.0;
			double Y_Gradient = 0.0;
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x-1,source.y+1), 3); //left up
			//X_Gradient += 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//Y_Gradient += 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y + 1), 3);//middle up
			//X_Gradient += 2*(0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255));
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x+1, source.y + 1), 3);//right up
			//X_Gradient += 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//Y_Gradient -= 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x-1, source.y), 3);//left middle
			//Y_Gradient += 2*(0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255));
			// do nothing for middle one
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x+1, source.y), 3);//right middle
			//Y_Gradient -= 2 * (0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255));
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x-1, source.y-1), 3);//left down
			//X_Gradient -= 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//Y_Gradient += 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y -1), 3);//middle down
			//X_Gradient -= 2*(0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255));
			//memcpy(sourceColor, pDoc->GetOriginalPixel(source.x+1, source.y - 1), 3);//right down
			//X_Gradient -= 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			//Y_Gradient -= 0.299 * float(sourceColor[0] / 255) + 0.587 * float(sourceColor[1] / 255) + 0.144 * float(sourceColor[2] / 255);
			memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y), 3);
			X_Gradient = X_Gradient - (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
			Y_Gradient = Y_Gradient - (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
			memcpy(sourceColor, pDoc->GetOriginalPixel(source.x+1, source.y), 3);
			X_Gradient = X_Gradient + (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
			memcpy(sourceColor, pDoc->GetOriginalPixel(source.x, source.y+1), 3);
			Y_Gradient = Y_Gradient + (0.299 * float(sourceColor[0]) + 0.587 * float(sourceColor[1]) + 0.144 * float(sourceColor[2]));
			double absolute_change;
			absolute_change = sqrt(X_Gradient * X_Gradient + Y_Gradient * Y_Gradient);
			glVertex2d(target.x + ((size / 2) * Y_Gradient/absolute_change), target.y - (size / 2) * X_Gradient/absolute_change);
			glVertex2d(target.x - ((size / 2) * Y_Gradient/absolute_change), target.y + (size / 2) * X_Gradient/absolute_change);
			EndX = target.x;
			EndY = target.y;
			
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