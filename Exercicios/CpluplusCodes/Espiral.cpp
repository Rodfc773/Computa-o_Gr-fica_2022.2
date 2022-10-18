/* Pra compilar gcc opengl.c -o gl -Ifreeglut/include -Lfreeglut/lib -lGL -lglut */
#include <GL/gl.h>
#include <GL/glut.h> //Bliblioteca responsavel por iniciar o glut
#include <iostream>
#include <math.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define GL_PI 3.1415f


void display();
void ChangeSize(GLsizei w, GLsizei h);
void setupRC();

int main(int argc, char ** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);   
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT); //tamanho da janela criada
    glutInitWindowPosition(100,100); //posição que vai iniciar a janela
    glutCreateWindow("openGL with glut");

    setupRC();
    glutDisplayFunc(display);
    glutReshapeFunc(ChangeSize);
    glutMainLoop(); //faz com que a janela seja redesenhada o tempo inteiro em um loop;
    return 0; 
}
void ChangeSize(GLsizei w, GLsizei h){

    GLfloat nRange = 100.0f;

    //previne a divisão por 0

    if(h == 0) h = 1;

    //Configura a viewport para a janela de dimensões

    glViewport(0, 0, w, h);

    //Reseta a pilha da matriz de projeções
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    //Separa um parte da  viewport(left, rigth, bottom, top, near, far)

    if(w <= h) glOrtho(-nRange, nRange, -nRange*h/w, nRange*h/w, -nRange, nRange);

    else glOrtho(-nRange*w/h, nRange*w/h, -nRange, nRange, -nRange, nRange);

    //Resetando a pilha de modelo de vizualição

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}
void display(){

    GLfloat x,y,z,angle; //criando as coordenadas para os eixos e o ângulo
    //limpa a janela com a cor atual
    glClear(GL_COLOR_BUFFER_BIT);

    //salva o estado da matiz e realiza a rotação
    glPushMatrix();
    glRotatef(60.0f, 1.0f, 0.0f, 0.0f);
    glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
    glBegin(GL_POINTS);
    z = -50.0f;

    for (angle = 0.0f; angle <= (2.0f * GL_PI) * 3.0f; angle += 0.1f)
    {
        x = 50.0f * sin(angle);
        y = 50.0f * cos(angle);

        //Especifica o ponto e move o valor de Z um pouco pra cima
        glVertex3f(x,y,z);
        z += 0.5f;
    }
    glEnd();

    //Restoura as transformações

    glPopMatrix();
    glutSwapBuffers();
    

}

void setupRC(){

    //blackground color

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    //Deixando a cor do desenho no verde
    glColor3f(0.0f, 1.0f, 0.0f);
}