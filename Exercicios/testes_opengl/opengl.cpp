#include <GL/gl.h>
#include <iostream>

#include <GL/glut.h> //Bliblioteca responsavel por iniciar o glut
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

void display(){ //função que faz o trabalho do desenho 


}

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //tamanho da janela criada
    glutInitWindowPosition(100,100); //posição que vai iniciar a janela
    glutCreateWindow("openGL with glut");

    glutDisplayFunc(display);
    glutMainLoop(); //faz com que a janela seja redesenhada o tempo inteiro em um loop;
    return 0; 
}