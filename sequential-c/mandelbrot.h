/*
Lucas Breur
06-2021
Senac - Arquiteturas Paralelas e Distribuídas
*/

// Importações
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

#define MAX_I 256 // Número máximo de interações

// Estrutura para definição de número complexo
typedef struct {
    float real;
    float imag;
} complex;

// Função que retorna valor de cor para um pixel do conjunto de Mandelbrot
int calc_pixel(complex c) {

    int count;
    complex z;

    float temp, lengthsq;

    z.real = 0; 
	z.imag = 0;
    count = 0;

	// Iterações continuam até que a magnitude de z seja maior que 2 ou o número de iterações alcance um limite arbitrário definido por MAX_I
    do {
        temp = z.real * z.real - z.imag * z.imag + c.real;
        z.imag = 2 * z.real * z.imag + c.imag;
        z.real = temp;
        lengthsq = z.real * z.real + z.imag * z.imag;
        count++;
    } while ((lengthsq < 4.0) && (count < MAX_I));
    
    return count;
}

/* The code below is from:

	LibPNG example
	A.Greensted
	http://www.labbookpages.co.uk
*/

void setRGB(png_byte *ptr, double val)
{
	int v = (int)(val * 767);
	int offset = v % 256 * 2;

	if (v < 256) {
		ptr[0] = offset; ptr[1] = offset; ptr[2] = offset;
	}
	else if (v < 512) {
		ptr[0] = offset; ptr[1] = offset; ptr[2] = offset;
	}
	else {
		ptr[0] = 255-offset; ptr[1] = 255-offset; ptr[2] = 255-offset;
	}
}


int writeImage(char* filename, int width, int height, double *buffer, char* title)
{
	int code = 0;
	FILE *fp = NULL;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;
	
	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}

	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}

	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}

	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
			8, PNG_COLOR_TYPE_RGB, PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	row = (png_bytep) malloc(3 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y=0 ; y<height ; y++) {
		for (x=0 ; x<width ; x++) {
			setRGB(&(row[x*3]), buffer[y*width + x]);
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);

	finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}