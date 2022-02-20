//
// PointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointbrush.h"
#include <iostream>

extern float frand();

PointBrush::PointBrush( ImpressionistDoc* pDoc, char* name ) :
	ImpBrush(pDoc,name)
{
}

void PointBrush::BrushBegin( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	int size = pDoc->getSize();


	glPointSize( (float)size );

	BrushMove( source, target );
}

void PointBrush::BrushMove( const Point source, const Point target )
{
	ImpressionistDoc* pDoc = GetDocument();
	ImpressionistUI* dlg=pDoc->m_pUI;

	if ( pDoc == NULL ) {
		printf( "PointBrush::BrushMove  document is NULL\n" );
		return;
	}

	float alpha = dlg->getAlpha();

	glBegin( GL_POINTS );
		GLubyte sourceColor[3], targetColor[3];
		float sColor[3],tColor[3],color[3];

		memcpy(sourceColor, pDoc->GetOriginalPixel(source), 3);
		memcpy(targetColor, pDoc->GetOriginalPixel(target), 3);

		sColor[0] = float(sourceColor[0]) / 255;
		sColor[1] = float(sourceColor[1]) / 255;
		sColor[2] = float(sourceColor[2]) / 255;
		tColor[0] = float(targetColor[0]) / 255;
		tColor[1] = float(targetColor[1]) / 255;
		tColor[2] = float(targetColor[2]) / 255;

		color[0] = sColor[0] * alpha + tColor[0] * (1 - alpha);
		color[1] = sColor[1] * alpha + tColor[1] * (1 - alpha);
		color[2] = sColor[2] * alpha + tColor[2] * (1 - alpha);
		std::cout << sColor[0] << " " << tColor[0] << " " << color[0] << std::endl;
		std::cout << source.x << " " << source.y << " " << target.x << " " << target.y << std::endl;
		glColor3f(color[0], color[1], color[2]);

		glVertex2d( target.x, target.y );
	glEnd();
}

void PointBrush::BrushEnd( const Point source, const Point target )
{
	// do nothing so far
}

