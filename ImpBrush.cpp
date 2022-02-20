//
// ImpBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "ImpBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount	= 0;
ImpBrush**	ImpBrush::c_pBrushes	= NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc, 
				   char*				name) :
					m_pDoc(pDoc), 
					m_pBrushName(name)
{
}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::GetDocument(void)
{
	return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::BrushName(void)
{
	return m_pBrushName;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::SetColor (const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();

	/*GLubyte color[3];

	memcpy ( color, pDoc->GetOriginalPixel( source ), 3 );
 
	glColor3ubv( color );*/

	float alpha = pDoc->getAlpha();

	GLubyte sourceColor[3], targetColor[3];
	float sColor[3], tColor[3], color[3];

	memcpy(sourceColor, pDoc->GetOriginalPixel(source), 3);
	memcpy(targetColor, pDoc->GetPaintPixel(target), 3);

	sColor[0] = float(sourceColor[0]) / 255;
	sColor[1] = float(sourceColor[1]) / 255;
	sColor[2] = float(sourceColor[2]) / 255;
	tColor[0] = float(targetColor[0]) / 255;
	tColor[1] = float(targetColor[1]) / 255;
	tColor[2] = float(targetColor[2]) / 255;

	color[0] = sColor[0] * alpha + tColor[0] * (1 - alpha);
	color[1] = sColor[1] * alpha + tColor[1] * (1 - alpha);
	color[2] = sColor[2] * alpha + tColor[2] * (1 - alpha);
	glColor3f(color[0], color[1], color[2]);

}