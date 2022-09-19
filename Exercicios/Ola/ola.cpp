#include <GL/gl.h>
#include <GL/glut.h>
#include "../Squares/squares.cpp"
#include <iostream>

Square square2{0.0f, 0.0f, 0.10f, 0.15f, 0.8f, 0.2f, 0.5f};
Square square1(0.15f, 0.0f, 0.25f, 0.15f, 0.0f, 1.0f, 0.7f);
Square square3{-0.15f, 0.0f, -0.05f, 0.15f, 0.6f, 0.4f, 1.0f};
Square square4{-0.30f, 0.0f, -0.20f, 0.15f, 0.3f, 0.8f, 0.9f};
Square square5{-0.45f, 0.0f, -0.35f, 0.15f, 0.0f, 1.0f, 1.0f};

void Desenha(){
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    square1.formar_square();
    square2.formar_square();
    square3.formar_square();
    square4.formar_square();
    square5.formar_square();

    glFlush();
}

void keyboard_square(unsigned char key,int x ,int y){


    if(key == 'q'){

        square5.transladar(0.2);
        square1.transladar(-0.2);
        Desenha();
    }
    if(key == 'w'){

        square5.transladar(-0.2);
        square4.transladar(0.2);
        Desenha();

    }
    if(key == 'e'){

        square3.transladar(0.2);
        square4.transladar(-0.2);
        Desenha();
    }
    if(key == 'r'){

        square2.transladar(0.2);
        square3.transladar(-0.2);
        Desenha();
    }
    if(key == 't'){
        square1.transladar(0.2);
        square2.transladar(-0.2);
        Desenha();
    }

}
int main(int argc, char ** argv){

     glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1280,720);
    glutInitWindowPosition(10,10);
    glutCreateWindow("Quadrado");
    glutDisplayFunc(Desenha);
    glutKeyboardFunc(keyboard_square);
    glutMainLoop();
}