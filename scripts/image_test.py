"""Testing image loading and display to compare with our own C++ implementation."""
import pygame

pygame.init()
pygame.display.set_caption("Image Test")

scale = 4.0
image = pygame.image.load("test.png")
window = pygame.display.set_mode((320 * scale, 200 * scale))

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            exit()
    greenscreen = (0, 255, 0)
    window.fill(greenscreen)
    window.blit(image, (0, 0))
    pygame.display.flip()
