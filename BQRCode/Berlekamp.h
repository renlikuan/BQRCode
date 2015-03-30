#pragma once
/* Error location routines */
int correct_errors_erasures (unsigned char codeword[], int csize,int nerasures, int erasures[]);

/* polynomial arithmetic */
void add_polys(int dst[], int src[]) ;
void scale_poly(int k, int poly[]);
void mult_polys(int dst[], int p1[], int p2[]);

void copy_poly(int dst[], int src[]);
void zero_poly(int poly[]);

