/************************   
 * bilinear.c 
 *
 * Code here is from http://pulsar.webshaker.net/2011/05/25/bilinear-enlarge-with-neon/
 *
 ************************/

#include <stdio.h>


unsigned int src[]={
   0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
   0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
   0x000000, 0x0000FF, 0x0000FF, 0x000000, 0x000000,
   0x000000, 0x000000, 0x000000, 0x0000FF, 0x0000FF,
   0x0000FF, 0x0000FF, 0x000000, 0x000000, 0x000000,
   0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF,
   0x0000FF, 0x000000, 0x000000, 0x0000FF, 0x0000FF,
   0x0000FF, 0x0000FF, 0x0000FF, 0x0000FF, 0x000000,
   0x000000, 0x000000, 0x0000FF, 0x0000FF, 0x0000FF,
   0x0000FF, 0x000000, 0x000000, 0x000000, 0x000000,
   0x000000, 0x0000FF, 0x0000FF, 0x000000, 0x000000,
   0x000000, 0x000000, 0x000000, 0x000000, 0x000000,
   0x000000, 0x000000, 0x000000, 0x000000};   
   
   
   
   
#ifdef _MSC_VER
__declspec(align(16))
#else
__attribute__((aligned (16)))
#endif

unsigned int dst[256];


 
void stretch(unsigned int *bSrc, unsigned int *bDst, int wSrc, int hSrc, int wDst, int hDst)
{
   unsigned int wStepFixed16b, hStepFixed16b, wCoef, hCoef, x, y;
   unsigned int pixel1, pixel2, pixel3, pixel4;
   unsigned int hc1, hc2, wc1, wc2, offsetX, offsetY;
   unsigned int r, g, b, a;

   wStepFixed16b = ((wSrc - 1) << 16) / (wDst - 1);
   hStepFixed16b = ((hSrc - 1) << 16) / (hDst - 1);

   hCoef = 0;

   for (y = 0 ; y < hDst ; y++)
   {
      offsetY = (hCoef >> 16);
      hc2 = (hCoef >> 9) & 127;
      hc1 = 128 - hc2;

      wCoef = 0;
      for (x = 0 ; x < wDst ; x++)
      {
         offsetX = (wCoef >> 16);
         wc2 = (wCoef >> 9) & 127;
         wc1 = 128 - wc2;

         pixel1 = *(bSrc + offsetY * wSrc + offsetX);
         pixel2 = *(bSrc + (offsetY + 1) * wSrc + offsetX);
         pixel3 = *(bSrc + offsetY * wSrc + offsetX + 1);
         pixel4 = *(bSrc + (offsetY + 1) * wSrc + offsetX + 1);

         r = ((((pixel1 >> 24) & 255) * hc1 + ((pixel2 >> 24) & 255) * hc2) * wc1 +
            (((pixel3 >> 24) & 255) * hc1 + ((pixel4 >> 24) & 255) * hc2) * wc2) >> 14;
         g = ((((pixel1 >> 16) & 255) * hc1 + ((pixel2 >> 16) & 255) * hc2) * wc1 +
            (((pixel3 >> 16) & 255) * hc1 + ((pixel4 >> 16) & 255) * hc2) * wc2) >> 14;
         b = ((((pixel1 >> 8) & 255) * hc1 + ((pixel2 >> 8) & 255) * hc2) * wc1 +
            (((pixel3 >> 8) & 255) * hc1 + ((pixel4 >> 8) & 255) * hc2) * wc2) >> 14;
         a = ((((pixel1 >> 0) & 255) * hc1 + ((pixel2 >> 0) & 255) * hc2) * wc1 +
            (((pixel3 >> 0) & 255) * hc1 + ((pixel4 >> 0) & 255) * hc2) * wc2) >> 14;

         *bDst++ = (r << 24) + (g << 16) + (b << 8) + (a);

         wCoef += wStepFixed16b;
      }
      hCoef += hStepFixed16b;
   }
}

#ifdef JUNK2
int
main(void)
{
	int i;
	int ml1=0xaa;
	
	int ml2=0xbb;
	
	for (i=0; i<256; i++)
	{
		dst[i]=0x55;
	}
	
  stretch((unsigned int*)src, dst, 8,8,16,16);

  for (i=0; i<256; i++)
  {
  	dst[i]=dst[i]&0x00ffffff;
  	printf("%06x ", dst[i]);
  }
  //while(1);
  printf("\nml1=%d", ml1);
  printf("\nml2=%d\n", ml2);
  return(0);
}

#endif

