#include <GL/gl.h>
#include <GL/glut.h>
#include "Squares/squares.cpp"
#include <iostream>
// Função callback chamada para fazer o desenho

void Desenha(void)
{
     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     // Limpa a janela de visualização com a cor de fundo especificada
     glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
     glClear(GL_COLOR_BUFFER_BIT);

     // Especifica que a cor corrente é vermelha
     //         R     G    B

     // Desenha um quadrado preenchido com a cor corrente
     // Executa os comandos OpenGL
     glFlush();
}

// Inicializa parâmetros de rendering
int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Quadrado");
    glutDisplayFunc(Desenha);
    //glutKeyboardFunc(keyboard_square);
    glutMainLoop();

     return 0;
}