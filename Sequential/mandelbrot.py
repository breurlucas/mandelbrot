# Lucas Breur
# 06-2021
# Senac - Arquiteturas Paralelas e Distribuídas

# Importações
from numpy import complex # Importa estrutura para números complexos da biblioteca Numpy

# Constantes
MAX_I = 256 # Número máximo de interações

# Função que retorna valor de cor para um pixel do conjunto de Mandelbrot
def calc_pixel(real, imag):
    c = complex(real, imag)
    z = 0
    count = 0

    # Iterações continuam até que a magnitude de z seja maior que 2 ou o número de iterações alcance um limite arbitrário definido por MAX_I
    while abs(z) <= 2 and count < MAX_I:
        z = z * z + c   
        count += 1
    return count 

