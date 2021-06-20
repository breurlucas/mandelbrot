/*
Lucas Breur
06-2021
Senac - Arquiteturas Paralelas e Distribuídas
*/

// Importações
#include "mandelbrot.h" // Importa a função calc_pixel do script mandelbrot.c
#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

// Constantes
int WIDTH = 512;  // Largura da imagem em pixels
int HEIGHT = 512; // Altura da imagem em pixels

double minX = -2.0; // Origem eixo x
double maxX = 2.0;  // Máximo x positivo
double minY = -2.0; // Origem eixo y
double maxY = 2.0;  // Máximo y positivo

int x, y, color;
double scale_real, scale_imag;

complex z;

int main(int argc, char *argv[])
{    
    if (argc != 2) {
		fprintf(stderr, "Output file name was not specified\n");
		return 1;
	}

    z.real = x * (maxX - minX) / WIDTH  + minX; 
    z.imag = y * (maxY - minY) / HEIGHT  + minY;

    scale_real = (maxX - minX) / WIDTH;
    scale_imag = (maxY - minY) / HEIGHT;

    float *buffer = (float *) malloc(WIDTH * HEIGHT * sizeof(float));

    for (x = 0; x < WIDTH; x++) {
        for (y = 0; y < HEIGHT; y++) {
            z.real = minX + ((double)x * scale_real);
            z.imag = minY + ((double)y * scale_imag);
            color = calc_pixel(z);
            buffer[y * WIDTH + x] = color;
        }
    }
    
    int png = writeImage(argv[1], WIDTH, HEIGHT, buffer, "mandelbrot");

	free(buffer);

	return png;
}



