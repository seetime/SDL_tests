// bilinear.h
// Bilinear Enlarge
// Code in the .c file is taken from http://pulsar.webshaker.net/2011/05/25/bilinear-enlarge-with-neon/
//

#ifndef __BILINEAR__H__
#define __BILINEAR__H__

void stretch(unsigned int *bSrc, unsigned int *bDst, int wSrc, int hSrc, int wDst, int hDst);

#endif // __BILINEAR__H__

