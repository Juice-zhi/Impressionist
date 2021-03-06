// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include "impressionist.h"
#include "bitmap.h"



class ImpressionistUI;

class ImpressionistDoc 
{
public:
	ImpressionistDoc();

	void	setUI(ImpressionistUI* ui);		// Assign the UI to use

	int		loadImage(char *iname);			// called by the UI to load image
	int		saveImage(char *iname);			// called by the UI to save image


	int     clearCanvas();                  // called by the UI to clear the drawing canvas
	void	setBrushType(int type);			// called by the UI to set the brushType
	int		getSize();						// get the UI size
	void	setSize(int size);				// set the UI size
	int		getThickness();
	void	setThickness(int line_thickness);
	int		getAngle();
	void	setAngle(int line_angle);
	float	getAlpha();
	void	setAlpha(float alpha_value);
	char*	getImageName();		// get the current image name
	void    change_Direction(int direction);
	int		get_Direction_Choice();

	void deactivate_thickness_slider();
	void deactivate_angle_slider();
	void activate_thickness_slider();
	void activate_angle_slider();

// Attributes
public:
	// Dimensions of original window.
	int				m_nWidth, 
					m_nHeight;
	// Dimensions of the paint window.
	int				m_nPaintWidth, 
					m_nPaintHeight;	
	// Bitmaps for original image and painting.
	unsigned char*	m_ucBitmap;
	unsigned char*	m_ucPainting;


	// The current active brush.
	ImpBrush*			m_pCurrentBrush;	
	// Size of the brush.
	int m_nSize;							
	//direction choice
	Direction direction_choice = SLIDER_OR_RIGHT_MOUSE;
	ImpressionistUI*	m_pUI;

// Operations
public:
	// Get the color of the original picture at the specified coord
	GLubyte* GetOriginalPixel( int x, int y );   
	// Get the color of the original picture at the specified point	
	GLubyte* GetOriginalPixel( const Point p );  
	// Get the color of the paint picture at the specified coord
	GLubyte* GetPaintPixel(int x, int y);
	// Get the color of the paint picture at the specified point	
	GLubyte* GetPaintPixel(const Point p);


private:
	char			m_imageName[256];

};

extern void MessageBox(char *message);

#endif
