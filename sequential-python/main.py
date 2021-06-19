# Lucas Breur
# 06-2021
# Senac - Arquiteturas Paralelas e Distribuídas

# Importações
from mandelbrot import calc_pixel, MAX_I # Importa a função calc_pixel do script mandelbrot.py
from PIL import Image # Importa a geração de imagens da biblioteca Pillow (PIL)

# Constantes
WIDTH = 512  # Largura da imagem em pixels
HEIGHT = 512 # Altura da imagem em pixels

minX = -2.0 # Origem eixo x
maxX = 2.0  # Máximo x positivo
minY = -2.0 # Origem eixo y
maxY = 2.0  # Máximo y positivo


img = Image.new("RGB", (WIDTH, HEIGHT)) # Gera nova imagem com tamanho WIDTH X HEIGHT

# Laço que percorre todos os pixels da imagem
for y in range(HEIGHT):
    # Mapeia a parte imaginária de z para a escala da imagem
    imag = y * (maxY - minY) / HEIGHT  + minY 
    for x in range(WIDTH):
        # Mapeia a parte real de z para a escala da imagem
        real = x * (maxX - minX) / WIDTH  + minX
        # Calcula a cor do pixel na coordenada z = real + imag * 1j
        color = calc_pixel(real, imag)
        # Colore o pixel
        img.putpixel((x, y), (color % 255 * 16, color % 255 * 16, color % 255 * 16))

img.show() # Abre o fractal em .png
#img.save("mandelbrot.png")