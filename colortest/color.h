// color.h
// Color mapping functions

#ifndef __COLOR__H__
#define __COLOR__H__


typedef struct hsv_s{
	float h;
	float s;
	float v;
} hsv_t;	

typedef struct rgb_s{
	unsigned char r;
	unsigned char g;
	unsigned char b;
} rgb_t;	

void init_hsv(void);

// convert from 0..65535 to HSV
void single2hsv (float v, hsv_t* hsv);

// convert from 0..65535 to RGB 24-bit
void single2rgb24 (float v, rgb_t* rgb);

// convert from 0..65535 to RGB 16-bit
void
single2rgb16 (float v, unsigned int* pixval);

// convert from 24-bit RGB 16-bit
unsigned int col565(rgb_t* rgb);

// convert from 24-bit encoding to 16-bit encoding
unsigned int col24to16(unsigned int m);

// Maps from HSV to RGB
// Outputs to r,g,b in the range 0..1
// Inputs: h=hue(0 to 360 where e.g. 240 is blue, and 360 is red, and 6 is yellow)
// s= saturation(0 to 1) where 0 is no color (white) and 1 is pure color
// v=value(0 to 1) where 0 is black, and 1 is bightest color
// Imagine a cylinder, where the bottom is black and top rim is bright color
// Circling around the cylinder causes a change in color. The center of the
// cylinder is whiter.
// For converting a single value into a color (e.g. for thermal array),
// the scheme will be: from low to high value, circle once around the cylinder
// (or part of the cylinder) while going up the cylinder too, i.e. like a
// screw thread. This will have the effect of making low values look black, 
// and high values be a brighter color, and the color changes as the value gets higher
void HSVtoRGB( float *r, float *g, float *b, float h, float s, float v );



#endif // __COLOR__H__