#include <GL/gl.h>
#include <GL/glut.h>
#include <thread>
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

class Square{

    private:

        float x0,y0,x1,y1;
        float R, G, B;

    public:

        Square(float x0, float y0, float x1, float y1, float R, float G, float B)
        {
            this->x0 = x0;
            this->y0 = y0;
            this->x1 = x1;
            this->y1 = y1;
            this->R = R;
            this->B = B;
            this->G = G;
            
        
        }
        void formar_square(){

            glBegin(GL_QUAD_STRIP);

            glColor3f(this->R, this->G, this->B);
            glVertex2f(this->x0, this->y0);
            glVertex2f(this->x0, this->y1);
            glVertex2f(this->x1, this->y0);
            glVertex2f(this->x1, this->y1);

          glEnd();
        }

        void transladar(float y){

            this->y0 += y;
            this->y1 += y;

            if((this->y0 > 0.35  || this->y0 < 0.0) && (this->y1 > 0.45 || this->y1 < 0.15)){

                this->y0 = 0.0;
                this->y1 = 0.15;
            }
        }


};


