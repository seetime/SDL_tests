// color.c
// Color mapping functions

#include <math.h>
#include "color.h"

// *** HUE ***
// Red Orange Yellow Green LBlue DBlue Purple Red
//  0    50     60    120   180   240   300   360
#define STARTCOL 240.0
#define ENDCOL 60.0
// Direction (circular):
//     1 is ---->
//     0 is <----
#define DIR 1
// *** BRIGHTNESS (value) ***
// STARTBRIGHT must be lower than ENDBRIGHT
// Black=0.0, through to full brightness=1.0:
#define STARTBRIGHT 0.1
#define ENDBRIGHT 1.0
// *** SATURATION ***
// 0.0=white, through to 1.0=full color
#define SAT 1.0


static float span;
static float hcoef;
static float bcoef;

// calculate the span in advance
void
init_hsv(void)
{
	float bspan;
	
	// calculate hue span
	span=0;
	if (STARTCOL==ENDCOL)
	{
		span=360;
	}
	else
	{
		if (DIR)
		{
			if (ENDCOL>STARTCOL)
				span=ENDCOL-STARTCOL;
			else
				span=ENDCOL+(360-STARTCOL);
		}
		else
		{
			if (ENDCOL<STARTCOL)
				span=STARTCOL-ENDCOL;
			else
				span=STARTCOL+(360-ENDCOL);
		}
	}
	hcoef=span/65535;
	
	// calculate brightness span
	bspan=ENDBRIGHT-STARTBRIGHT;
	bcoef=bspan/65535;
	
}
	
// convert from 0..65535 to HSV
void single2hsv (float v, hsv_t* hsv)
{
	float h;
	float b;
	float s;
	// calculate hue
	h=hcoef*v;
	if (DIR)
		h=h+STARTCOL;
	else
		h=h-STARTCOL;
	
	if (h>360)
		h=h-360;
	if (h<0)
		h=h+360;
	
	// calculate brightness (value)
	b=bcoef*v;
	b=b+STARTBRIGHT;
	
	// set the saturation
	s=SAT;
	
	hsv->h=h;
	hsv->s=s;
	hsv->v=b;
}

void
single2rgb24 (float v, rgb_t* rgb)
{
	float r,g,b;
	hsv_t hsv;
	// convert to HSV first
	single2hsv (v, &hsv);
	// now convert to RGB
	HSVtoRGB( &r, &g, &b, hsv.h, hsv.s, hsv.v );
	// now scale the RGB values to 8-bit each
	r=r*255; g=g*255; b=b*255;
	rgb->r=(unsigned char)r;
	rgb->g=(unsigned char)g;
	rgb->b=(unsigned char)b;
	
}

void
single2rgb16 (float v, unsigned int* pixval)
{
	rgb_t rgb;
	single2rgb24(v, &rgb);
	*pixval=col565(&rgb);
}

unsigned int
col24to16(unsigned int m)
{
	unsigned int r,g,b;
	r=(m & 0xff0000)>>16;
	g=(m & 0x00ff00)>>8;
	b=(m & 0x0000ff);
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

unsigned int
col565(rgb_t* rgb)
{
	unsigned int r,g,b;
	r=(unsigned int) rgb->r;
	g=(unsigned int) rgb->g;
	b=(unsigned int) rgb->b;
  return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}


/*
 * Taken from http://www.cs.rit.edu/~ncs/color/t_convert.html#RGB%20to%20HSV%20&%20HSV%20to%20RGB
 */
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v )
{
	int i;
	float f, p, q, t;

	if( s == 0 ) {
		// achromatic (grey)
		*r = *g = *b = v;
		return;
	}

	h /= 60;			// sector 0 to 5
	i = floor( h );
	f = h - i;			// factorial part of h
	p = v * ( 1 - s );
	q = v * ( 1 - s * f );
	t = v * ( 1 - s * ( 1 - f ) );

	switch( i ) {
		case 0:
			*r = v;
			*g = t;
			*b = p;
			break;
		case 1:
			*r = q;
			*g = v;
			*b = p;
			break;
		case 2:
			*r = p;
			*g = v;
			*b = t;
			break;
		case 3:
			*r = p;
			*g = q;
			*b = v;
			break;
		case 4:
			*r = t;
			*g = p;
			*b = v;
			break;
		default:		// case 5:
			*r = v;
			*g = p;
			*b = q;
			break;
	}

}
