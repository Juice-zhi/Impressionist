// 
// impressionistDoc.cpp
//
// It basically maintain the bitmap for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//

#include <FL/fl_ask.H>

#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "ImpBrush.h"

// Include individual brush headers here.
#include "PointBrush.h"
#include "CircleBrush.h"
#include "LineBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredPointBrush.h"
#include "StarBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() 
{
	// Set NULL image name as init. 
	m_imageName[0]	='\0';	

	m_nWidth		= -1;
	m_ucBitmap		= NULL;
	m_ucPainting	= NULL;


	// create one instance of each brush
	ImpBrush::c_nBrushCount	= NUM_BRUSH_TYPE;
	ImpBrush::c_pBrushes	= new ImpBrush* [ImpBrush::c_nBrushCount];

	ImpBrush::c_pBrushes[BRUSH_POINTS]	= new PointBrush( this, "Points" );

	// Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
	ImpBrush::c_pBrushes[BRUSH_LINES]				
		= new LineBrush( this, "Lines" );
	ImpBrush::c_pBrushes[BRUSH_CIRCLES]				
		= new CircleBrush( this, "Circles" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]	
		= new ScatteredPointBrush( this, "Scattered Points" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]		
		= new ScatteredLineBrush( this, "Scattered Lines" );
	ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]	
		= new ScatteredCircleBrush( this, "Scattered Circles" );
	ImpBrush::c_pBrushes[BRUSH_STAR]
		= new StarBrush(this, "Star");

	// make one of the brushes current
	m_pCurrentBrush	= ImpBrush::c_pBrushes[0];

}


//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) 
{
	m_pUI	= ui;
	m_pUI->deactivate_thickness_slider();
	m_pUI->deactivate_angle_slider();
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() 
{
	return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type)
{
	m_pCurrentBrush	= ImpBrush::c_pBrushes[type];
	if (type != 1 && type !=4) {
		m_pUI->deactivate_thickness_slider();
		m_pUI->deactivate_angle_slider();
	}
	else {
		m_pUI->activate_thickness_slider();
		m_pUI->activate_angle_slider();
	}
}

void ImpressionistDoc::change_Direction(int direction)
{
	direction_choice = static_cast<Direction>(direction);
}

//
//return the direction choice
//
int ImpressionistDoc::get_Direction_Choice()
{
	return direction_choice;
}

//---------------------------------------------------------
// Returns the size of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getSize()
{
	return m_pUI->getSize();
}

//---------------------------------------------------------
// Set the size of the brush.
//---------------------------------------------------------
void ImpressionistDoc::setSize(int size) {
	m_pUI->setSize(size);
}

//---------------------------------------------------------
// Return the thickness of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getThickness() {
	return m_pUI->getThickness();
}

//---------------------------------------------------------
//Return the Angle of the brush.
//---------------------------------------------------------
int ImpressionistDoc::getAngle() {
	return m_pUI->getAngle();
}

//---------------------------------------------------------
//Return the Angle of the brush.
//---------------------------------------------------------
void ImpressionistDoc::setAngle(int line_angle) {
	m_pUI->setAngle(line_angle);
}

//---------------------------------------------------------
//Return the Alpha value of the brush.
//---------------------------------------------------------
float ImpressionistDoc::getAlpha() {
	return m_pUI->getAlpha();
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(char *iname) 
{
	// try to open the image to read
	unsigned char*	data;
	int				width, 
					height;

	if ( (data=readBMP(iname, width, height))==NULL ) 
	{
		fl_alert("Can't load bitmap file");
		return 0;
	}

	// reflect the fact of loading the new image
	m_nWidth		= width;
	m_nPaintWidth	= width;
	m_nHeight		= height;
	m_nPaintHeight	= height;

	// release old storage
	if ( m_ucBitmap ) delete [] m_ucBitmap;
	if ( m_ucPainting ) delete [] m_ucPainting;

	m_ucBitmap		= data;

	// allocate space for draw view
	m_ucPainting	= new unsigned char [width*height*3];
	memset(m_ucPainting, 0, width*height*3);

	m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(), 
								m_pUI->m_mainWindow->y(), 
								width*2, 
								height+25);

	// display it on origView
	m_pUI->m_origView->resizeWindow(width, height);	
	m_pUI->m_origView->refresh();

	// refresh paint view as well
	m_pUI->m_paintView->resizeWindow(width, height);	
	m_pUI->m_paintView->refresh();


	return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(char *iname) 
{

	writeBMP(iname, m_nPaintWidth, m_nPaintHeight, m_ucPainting);

	return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() 
{

	// Release old storage
	if ( m_ucPainting ) 
	{
		delete [] m_ucPainting;

		//// allocate space for draw view
		m_ucPainting	= new unsigned char [m_nPaintWidth*m_nPaintHeight*3];
		memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight*3);

		// refresh paint view as well	
		m_pUI->m_paintView->refresh();
	}
	
	return 0;
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( int x, int y )
{
	if ( x < 0 ) 
		x = 0;
	else if ( x >= m_nWidth ) 
		x = m_nWidth-1;

	if ( y < 0 ) 
		y = 0;
	else if ( y >= m_nHeight ) 
		y = m_nHeight-1;

	return (GLubyte*)(m_ucBitmap + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetOriginalPixel( const Point p )
{
	return GetOriginalPixel( p.x, p.y );
}

//------------------------------------------------------------------
// Get the color of the pixel in the paint image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintPixel(int x, int y)
{
	if (x < 0)
		x = 0;
	else if (x >= m_nPaintWidth)
		x = m_nPaintWidth - 1;

	if (y < 0)
		y = 0;
	else if (y >= m_nPaintHeight)
		y = m_nPaintHeight - 1;

	return (GLubyte*)(m_ucPainting + 3 * (y * m_nPaintWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the paint image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::GetPaintPixel(const Point p)
{
	return GetPaintPixel(p.x, p.y);
}

//deactivate thickness slider
void ImpressionistDoc::deactivate_thickness_slider() {
	m_pUI->deactivate_thickness_slider();
}
//deactivate angle slider
void ImpressionistDoc::deactivate_angle_slider() {
	m_pUI->deactivate_angle_slider();
}
//activate thickness slider
void ImpressionistDoc::activate_thickness_slider() {
	m_pUI->activate_thickness_slider();
}
//activate angle slider
void ImpressionistDoc::activate_angle_slider() {
	m_pUI->activate_angle_slider();
}