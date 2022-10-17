from cmath import cos, sin
from contextlib import nullcontext
from OpenGL.GL import *
from OpenGL.GLUT import *
from OpenGL.GLU import *

WINDOW_WIDHT = 1280
WINDOW_HEIGHT = 720

def bresenham(xo, yo, xf, yf):
    dy = yf - yo
    dx = xf - xo
    
    E = 2 * dy
    Ne = 2 * (dy - dx)
    
    d = 2 * dy - dx
    glColor3f(1.0, 1.0, 1.0)
    
    glBegin(GL_POINTS)
    glVertex3f(xo, yo, 0)
    glEnd()
    while xo != xf:
        if d <= 0:
            xo += 1
            d = d + E
        else:
            xo += 1
            yo += 1
            d = d + Ne
        glBegin(GL_POINTS)
        glVertex3f(xo, yo, 0)
        glEnd()
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
def display():
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT)
    # reseta transformações
    glLoadIdentity()
    glColor(0, 0, 0, 0)
    
    glPushMatrix()

    
    bresenham(1, 1, 4, 2)
    glPopMatrix()
    
    glutSwapBuffers()
    

def main():
    # inicialização
    glutInit()  # inicia glut
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA)
    glutInitWindowPosition(0, 0)
    glutInitWindowSize(WINDOW_WIDHT, WINDOW_HEIGHT)
    window = glutCreateWindow("Base do campo")

    #iluminação
    #setup_lighting()

    #callbacks
    glutDisplayFunc(display)
    glutReshapeFunc(change_side)
    """
    
    glutKeyboardFunc(keyboard)
    glutMouseFunc(mouse_click)
    glutMotionFunc(mouse_camera)
    """
    glutMainLoop()


main()