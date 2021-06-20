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
#include <omp.h>

// Constantes
#define WIDTH 512 // Largura da imagem em pixels
#define HEIGHT 512 // Altura da imagem em pixels
#define THREADS 2 // Número de threads (MAX 12)

const double minX = -2.0; // Origem eixo x
const double maxX = 2.0;  // Máximo x positivo
const double minY = -2.0; // Origem eixo y
const double maxY = 2.0;  // Máximo y positivo

double scale_real, scale_imag, color;

int x, y;

complex z;

int main(int argc, char *argv[])
{    
    clock_t t;

    scale_real = (maxX - minX) / WIDTH;
    scale_imag = (maxY - minY) / HEIGHT;

    // Buffer de armazenamento dos valores de cor calculados para todos os pixels da imagem
    double *buffer = (double *) malloc(WIDTH * HEIGHT * sizeof(double));

    t = clock(); // Tempo inicial

    // Inicia o paralelismo para o loop for
    #pragma omp parallel for default(shared)\
                            private(z, y, color)\
                            num_threads(THREADS)\
                            schedule(static,1)\

        for (x = 0; x < WIDTH; x++) {
            // Mapeia a parte real de z para a escala da imagem
            z.real = minX + ((double)x * scale_real);

            for (y = 0; y < HEIGHT; y++) {
                
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
    int png = writeImage(argv[1], WIDTH, HEIGHT, buffer, "mandelbrot");

    // Liberação da memória
	free(buffer);

	return png;
}



