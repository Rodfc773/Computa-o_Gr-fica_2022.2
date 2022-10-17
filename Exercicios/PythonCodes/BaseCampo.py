from cmath import cos, sin
from contextlib import nullcontext
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

import glm
import pygame

# tamanho da tela
WINDOW_WIDHT = 1000
WINDOW_HEIGHT = 1000

# camera
cameraPos = glm.vec3(0, 3.5, 30)
cameraFront = glm.vec3(0, 0, -1)
cameraUp = glm.vec3(0, 1, 0)
angle = 0

# mouse
old_mouse_x = 0
old_mouse_y = 0
angle_x = -1.57
angle_y = 1.57
mouse_speed = 0.1
mouse_sensitivity = 0.001


half_width = WINDOW_WIDHT / 2
half_height = WINDOW_HEIGHT / 2


def draw_wall(x0, y0, z0, x1, y1, z1):
    glBegin(GL_QUADS)
    glVertex3f(x0, y0, z0)
    glVertex3f(x1, y0, z1)
    glVertex3f(x1, y1, z1)
    glVertex3f(x0, y1, z0)
    glEnd()


def draw_floor(x, y, z, width, length): # x, y, z, largura, comprimento
    glBegin(GL_QUADS)
    glVertex3f(x, y, z)
    glVertex3f(x, y, z + length)
    glVertex3f(x + width, y, z + length)
    glVertex3f(x + width, y, z)
    glEnd()


def draw_block(x, y, z, width, length, height): # largura, comprimento, altura
    draw_wall(x, y, z, x, y + height, z+length) # plano zy, parte esquerda
    draw_wall(x, y, z, x+width, y + height, z) # plano xy, parte traseira
    draw_wall(x+width, y, z, x + width, y + height, z + length) # plano zy, parte direita
    draw_wall(x, y, z+length, x + width, y + height, z + length) # plano xy, parte dianteira
    draw_floor(x, y, z, width, length) # parte de baixo
    draw_floor(x, y+height, z, width, length) # parte de cima

def Bresenham(xo ,zo, xf,zf, y):
    dz = zf - zo
    dx = xf - xo
    
    E = 2 * dz
    Ne = 2 * (dz - dx)
    
    d = 2 * dz - dx
    glColor3f(1.0, 1.0, 1.0)
    glBegin(GL_LINE)
    while xo != xf and zo != zf:
        glVertex3f(xo, y, zo)
        
        if d <= 0:
            xo += 1
            d = d + E
        else:
            xo += 1
            zo += 1
            d = d + Ne
        glEnd()
def display():
    # limpa cor e buffers de profundidade
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    # reseta transformações
    glLoadIdentity()

    # define camera
    # camx camy camz centerx centery centerz upx upy upz
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z,
              cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y, cameraPos.z + cameraFront.z,
              cameraUp.x, cameraUp.y, cameraUp.z)

############################################################################################################
############################################################################################################

    glPushMatrix() # push

    # campo
    glColor3f(0.0, 1.0, 0.0)
    draw_floor(0, 0, 0, 35, 50)
    Bresenham(0, 0, 35.0, 50.0 ,0.0)

    # bloco 1
    """
    glColor3f(1.0, 1.0, 0.0)
    draw_block(0, 0, 0, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(1, 0, 0, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(-1, 0, 0, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(0, 1, 0, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(0, -1, 0, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(0, 0, 1, 0.1, 0.1, 0) # largura, comprimento, altura

    glColor3f(1.0, 1.0, 0.0)
    draw_block(0, 0, -1, 0.1, 0.1, 0) # largura, comprimento, altura

    # bloco 2
    glColor3f(0.0, 1.0, 0.0)
    draw_block(2, 0, 0, 1, 1, 1) # largura, comprimento, altura
    """


    glPopMatrix()  # pop

############################################################################################################
############################################################################################################

    glutSwapBuffers()


def keyboard(key, x, y):
    global angle, cameraFront, cameraUp, cameraPos, light_ambient, light_specular, light_diffuse

    cameraSpeed = 0.5

    if not isinstance(key, int):
        key = key.decode("utf-8")
    #controles da camera
    if key == 'w' or key == 'W':
        cameraPos += cameraSpeed * cameraFront
    elif key == 'a' or key == 'A':
        cameraPos -= glm.normalize(glm.cross(cameraFront, cameraUp)) * cameraSpeed
    elif key == 's' or key == 'S':
        cameraPos -= cameraSpeed * cameraFront
    elif key == 'd' or key == 'D':
        cameraPos += glm.normalize(glm.cross(cameraFront, cameraUp)) * cameraSpeed
    elif key == 'q' or key == 'Q':
        cameraPos.y += cameraSpeed/2
    elif key == 'e' or key == 'E':
        cameraPos.y -= cameraSpeed/2

    #controle da iluminação
    if key == 'r':
        glEnable(GL_LIGHT0)
    if key == 't':
        glDisable(GL_LIGHT0)


    glutPostRedisplay()


def change_side(w, h):
    global half_width, half_height
    if h == 0:
        h = 1
    ratio = w * 1/h

    glMatrixMode(GL_PROJECTION)

    glLoadIdentity()

    glViewport(0, 0, w, h)

    half_width = w / 2
    half_height = h / 2

    gluPerspective(45, ratio, 0.1, 100)

    glMatrixMode(GL_MODELVIEW)


def mouse_click(button, state, x, y):
    global old_mouse_x, old_mouse_y
    old_mouse_x = x
    old_mouse_y = y


def mouse_camera(mouse_x, mouse_y):
    global mouse_sensitivity, mouse_speed, angle_x, angle_y, cameraFront, old_mouse_x, old_mouse_y

    angle_x -= (mouse_x - old_mouse_x) * mouse_sensitivity
    angle_y -= (mouse_y - old_mouse_y) * mouse_sensitivity

    front = glm.vec3()
    front.x = glm.cos(angle_x) * glm.sin(angle_y)
    front.z = glm.sin(angle_x) * glm.sin(angle_y)
    front.y = glm.cos(angle_y)
    cameraFront = front

    old_mouse_x = mouse_x
    old_mouse_y = mouse_y
    glutPostRedisplay()


def setup_lighting():
    glEnable(GL_COLOR_MATERIAL)
    glEnable(GL_LIGHTING)
    glEnable(GL_LIGHT0)
    #glEnable(GL_LIGHT1)
    glEnable(GL_DEPTH_TEST)
    glShadeModel(GL_SMOOTH)
    glEnable(GL_NORMALIZE)

    glMaterialfv(GL_FRONT, GL_SPECULAR, [0.1, 0.1, 0.1, 1])

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [0.8, 0.8, 0.8, 1])
    # glLightModelfv(GL_LIGHT_MODEL_AMBIENT, [0.2, 0.2, 0.2, 1])

    glLightfv(GL_LIGHT0, GL_SPECULAR, [0.7, 0.7, 0.7, 1])
    glLightfv(GL_LIGHT0, GL_DIFFUSE, [0.3, 0.3, 0.3, 1])
    glLightfv(GL_LIGHT0, GL_POSITION, [0, 7, 0, 1])

    # spot light
    glLightfv(GL_LIGHT1, GL_DIFFUSE, [1, 1, 1, 1])
    glLightfv(GL_LIGHT1, GL_SPECULAR, [1, 1, 1, 1])

    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, [0, -1, 0])
    glLightfv(GL_LIGHT1, GL_POSITION, [0, 6, -1])

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 20)
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0)

    # glLightfv(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1)
    # glLightfv(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5)
    # glLightfv(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.2)
    # glLightfv(GL_LIGHT1, GL_SPOT_EXPONENT, 2.0)


def main():
    # inicialização
    glutInit()  # inicia glut
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
    glutInitWindowPosition(0, 0)
    glutInitWindowSize(WINDOW_WIDHT, WINDOW_HEIGHT)
    window = glutCreateWindow("Base do campo")

    #iluminação
    setup_lighting()

    #callbacks
    glutDisplayFunc(display)
    glutReshapeFunc(change_side)
    glutKeyboardFunc(keyboard)
    glutMouseFunc(mouse_click)
    glutMotionFunc(mouse_camera)

    glutMainLoop()


main()