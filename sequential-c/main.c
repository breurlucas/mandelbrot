/*
Lucas Breur
06-2021
Senac - Arquiteturas Paralelas e Distribuídas
*/

// Importações
#include "mandelbrot.h"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <malloc.h>
#include <png.h>

// Constantes
#define WIDTH 4096 // Largura da imagem em pixels
#define HEIGHT 4096 // Altura da imagem em pixels

double minX = -2.0; // Origem eixo x
double maxX = 2.0;  // Máximo x positivo
double minY = -2.0; // Origem eixo y
double maxY = 2.0;  // Máximo y positivo

double scale_real, scale_imag, color;

complex z;

int main(int argc, char *argv[])
{    
    clock_t t;

    scale_real = (maxX - minX) / WIDTH;
    scale_imag = (maxY - minY) / HEIGHT;

    // Buffer de armazenamento dos valores de cor calculados para todos os pixels da imagem
    double *buffer = (double *) malloc(WIDTH * HEIGHT * sizeof(double));

    t = clock(); // Tempo inicial

    for (int x = 0; x < WIDTH; x++) {
            
            // Mapeia a parte real de z para a escala da imagem
            z.real = minX + ((double)x * scale_real);

        for (int y = 0; y < HEIGHT; y++) {

            // Mapeia a parte imaginária de z para a escala da imagem
            z.imag = minY + ((double)y * scale_imag);

            color = calc_pixel(z);

            // Armazena os valores de cor concatenando as colunas em sequência
            buffer[y * WIDTH + x] = ((double)MAX_I - color) / (double)MAX_I;
        }
    }

    t = clock() - t; // Tempo final
    double time = ((double)t)/CLOCKS_PER_SEC; // Dividir pelo clock por segundo
    printf("Execution time [s]: %f \n", time);
    
    // A função writeImage recebe o buffer e mapeia as cores em um arquivo png
    // int png = writeImage(argv[1], WIDTH, HEIGHT, buffer, "mandelbrot");

    // Liberação da memória
	free(buffer);

	// return png;

    return 1;
}



