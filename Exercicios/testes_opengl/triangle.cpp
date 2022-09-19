#include <GL/gl.h>
#include <GL/glut.h>
#include <stdio.h>

//Definição do tamanho e posição da tela
#define WINDOW_WIDTH 550
#define WINDOW_HEIGHT 480
#define y_position 80
#define x_position 80


typedef struct Vertex
{
	float x, y, z;
	float r, g, b;
} Vertex;

Vertex vertices[] = {
	{-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f}, // vermelho
	{ 0.0f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f}, // verde
	{ 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f}, // azul
};

// float vertices[] = {
// 	-0.5f, -0.5f, 0.0f,
// 	0.0f, 0.5f, 0.0f,
// 	0.5f, -0.5f, 0.0f
// };

void display(){
    int i;
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glBegin(GL_TRIANGLES);
	Vertex v;
	
	for(i = 0;i < sizeof(vertices);i++)
	{
		v = vertices[i];
		glColor3f(v.r, v.g, v.b);
		glVertex3f(v.x, v.y, v.z);
	}
	// for(i = 0;i < sizeof(vertices) / sizeof(float);i += 3)
	// {
	// 	glVertex3f(vertices[i], vertices[i + 1], vertices[i + 2]);
	// }
	glEnd();

	//Faz o desenho acontecer o mais rápido possível 
	glFlush();
	
	//perguntar o swapBuffers
	glutSwapBuffers();
}


// Função responsavel pela interação com o teclado

void keyboard_setting(unsigned char key, int x, int y)
{
	Vertex v;
    switch (key) {
            case 'A': 
            case 'a':// muda a cor corrente para vermelho
					for(int i = 0;i < sizeof(vertices);i++)
					{
						vertices[i].r = 1.0f;
						vertices[i].g = 0.0f;
						vertices[i].b = 0.0f;
						
					}
                    //  glColor3f(1.0f, 0.0f, 0.0f);
                    break;
            case 'S':
            case 's':// muda a cor corrente para verde
                    for(int i = 0;i < sizeof(vertices);i++){
						vertices[i].r = 0.0f;
						vertices[i].g = 1.0f;
						vertices[i].b = 0.0f;
					}
                    break;
            case 'D':
            case 'd':// muda a cor corrente para azul
                    for(int i = 0;i < sizeof(vertices);i++)
					{
						vertices[i].r = 0.0f;
						vertices[i].g = 0.0f;
						vertices[i].b = 1.0f;
					}
					break;
			case 27:
				for(int i = 0; i < sizeof(vertices); i++){
					if(i == 0)
					{
						vertices[i].r = 1.0f;
						vertices[i].g = 0.0f;
						vertices[i].b = 0.0f;
					}
					if(i == 1)
					{
						vertices[i].r = 0.0f;
						vertices[i].g = 1.0f;
						vertices[i].b = 0.0f;
					}
					if(i == 2)
					{
						vertices[i].r = 0.0f;
						vertices[i].g = 0.0f;
						vertices[i].b = 1.0f;
					}	
				}
				break;
	printf("HEYHEY");
    }
    glutPostRedisplay();
}
// ========================================================================
	
int main(int argc, char ** argv){
    glutInit(&argc, argv);

	//GLUT DOUBLE/ GLUT SIMNGLE?
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	//inicialização da posição e tamanho da tela
	glutInitWindowPosition(x_position, y_position);
    glutInitWindowSize(WINDOW_WIDTH , WINDOW_HEIGHT);
	
    glutCreateWindow("My first Triangle");

	glutKeyboardFunc(keyboard_setting);
    glutDisplayFunc(display);
	
    glutMainLoop();
    return 0; 
}