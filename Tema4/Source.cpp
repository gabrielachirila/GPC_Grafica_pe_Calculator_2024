#include <GL/glut.h>


#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <cmath>
#include <vector>

# define M_PI           3.14159265358979323846


#include "GL/glut.h"


unsigned char prevKey;


class Grid
{
private:
    double epsilon;
    double distanceColumns, distanceRows;
    int originx, originy;
public:
    int rows, columns;
    Grid(int n, int m)
    {
        this->rows = n;
        this->columns = m;
        epsilon = 0.1;
        init(0, 0);
    }
    void init(int x = 0, int y = 0)
    { 
        distanceColumns = (2 - 2 * epsilon) / (columns - 1);
        distanceRows = (2 - 2 * epsilon) / (rows - 1);

        originx = x;
        originy= y;

       printf("OG:(%i,%i)\n",originx,originy);
    }
    void writePixels(int i, int j)
    {
        double x = -1 + epsilon + i * distanceColumns;
        double y = -1 + epsilon + j * distanceRows; 

        const int sides = 100; 
        const double radius = 0.03; 

        glColor3d(0, 0, 0);

        glBegin(GL_TRIANGLE_FAN);
        for (int k = 0; k < sides; ++k)
        {
            double angle = 2 * M_PI * k / sides;
            glVertex2d(x + radius * cos(angle), y + radius * sin(angle));
        }
        glEnd();
    }
    int checkInsideGrid(int i, int j)
    {
        if (i < 0 || i >= columns )
            return 0;
        if (j < 0 || j >= rows)
            return 0;
        return 1;

    }

    void AfisareSegmentDreapta1(int x0, int y0, int xn, int yn) {
       
        glColor3d(1.0, 0.1, 0.1);

        glLineWidth(5);
        glBegin(GL_LINES);
            glVertex2d(-1 + epsilon + x0 * distanceRows, -1 + epsilon + y0 * distanceColumns);
            glVertex2d(-1 + epsilon + xn * distanceRows, -1 + epsilon + yn * distanceColumns);
        glEnd();
        glLineWidth(2);
        int dx = xn - x0;
        int dy = yn - y0;
        double m = static_cast<double>(dy) / dx;
        printf("%f", m);
        for (int x = 0; x <= xn + 5 ; x++) { ///punem mai mult ca sa iasa din grid in caz ca mai sunt puncte de desenat
            double y = m * x;
            if (checkInsideGrid(x0 + x, y0 + static_cast<int>(y)) ==1) {
                writePixels(x0 + x, y0 + static_cast<int>(y));
            }
            if (myFunction(dx, dy, x0, y0, x0 + x, y0+ y) == 0) {
                for (int i = 1; i <= 4; i++) // 4 ca desenez cate 4 
                {
                    if (checkInsideGrid(x0 + x - i, y0 + static_cast<int>(y)) == 1) {
                        writePixels(x0 + x - i, y0 + static_cast<int>(y));
                    }
                    if (checkInsideGrid(x0 + x + i, y0 + static_cast<int>(y)) == 1) {
                        writePixels(x0 + x + i, y0 + static_cast<int>(y));
                    }
                }
            }
        }
      
   
    }
    int myFunction(int dx, int dy, int x_0, int y_0, int x, int y) {
        int a = dy;
        int b =  - dx;
        int c = dx * y_0 - dy * x_0;
            return a * x + b * y + c;
        
    }

    void AfisareDreapta3(int x_0, int y_0, int xn, int yn, int nrPixelsOneSide)
    {
        int dx = abs(xn - x_0);
        int dy = abs(yn - y_0);
        double m = static_cast<double>(dy) / dx;
        if (abs(m) <= 1)
        {
            AfisareSegmentDreapta3_dupax(x_0, y_0,  xn,  yn,  nrPixelsOneSide);

        }
        else
        {
            AfisareSegmentDreapta3_dupay(x_0, y_0, xn, yn, nrPixelsOneSide);
        }
    }
  

    void AfisareSegmentDreapta3_dupax(int x_0, int y_0, int xn, int yn, int nrPixelsOneSide) {
        if (x_0 > xn)
        {
            int temp = x_0;
            x_0 = xn;
            xn = temp;
            temp = y_0;
            y_0 = yn;
            yn = temp;
        }
        if(x_0 < xn && y_0 < yn)
        { 
        glColor3d(1.0, 0.1, 0.1);
        glLineWidth(5);
        glBegin(GL_LINES);
            glVertex2d(-1 + epsilon + x_0 * distanceRows, -1 + epsilon + y_0 * distanceColumns);
            glVertex2d(-1 + epsilon + xn * distanceRows, -1 + epsilon + yn * distanceColumns);
        glEnd();
        glLineWidth(2);
        
    
        int dx = abs(xn - x_0);
        int dy = abs(yn - y_0);
        int d = 2 * dy - dx;
        int dE = 2 * dy;
        int dNE = 2 * (dy - dx);
        int x = x_0, y = y_0;
        double m = static_cast<double>(dy) / dx;
        printf("here %f", m);
        if (checkInsideGrid(x, y) == 1) writePixels(x, y);
        for (int i = 1; i <= nrPixelsOneSide; i++) {
            if (checkInsideGrid(x, y - i) == 1) writePixels(x, y - i);
            if (checkInsideGrid(x, y + i) == 1) writePixels(x, y + i);
        }
        while (x < xn)
        {
            if (d <= 0)
            {
                
                d += dE;
                x++;
            }
            else
            {
                d += dNE;
                x++;
                y++;
            }
            if (checkInsideGrid(x, y) == 1) writePixels(x, y);
            for (int i = 1; i <= nrPixelsOneSide; i++) {
                if (checkInsideGrid(x, y - i) == 1) writePixels(x, y - i);
                if (checkInsideGrid(x, y + i) == 1) writePixels(x, y + i);
            }
        }
    }
        if (x_0 < xn and y_0 > yn) {
            int dx = abs(xn - x_0);
            int dy = abs(yn - y_0);

            glColor3d(1.0, 0.1, 0.1);
            glLineWidth(5);
            glBegin(GL_LINES);
            glVertex2d(-1 + epsilon + x_0 * distanceRows, -1 + epsilon + y_0 * distanceColumns);
            glVertex2d(-1 + epsilon + xn * distanceRows, -1 + epsilon + yn * distanceColumns);
            glEnd();
            glLineWidth(2);
            int d = 2 * dy - dx;
            int dE = 2 * dy;
            int dSe = 2 * (dy - dx);
            int x = x_0, y = y_0;
            double m = static_cast<double>(dy) / dx;
            printf("this is my m  %f", m);
           
            if ( checkInsideGrid(x, y) == 1) writePixels(x, y);
            for (int i = 1; i <= nrPixelsOneSide; i++) {
                if (checkInsideGrid(x, y - i) == 1) writePixels(x, y - i);
                if (checkInsideGrid(x, y + i) == 1) writePixels(x, y + i);
            }
          
           
            while (x < xn) {
                if (d <= 0) {
                    d += dE;
                    x++;
                }
                else {
                    d += dSe;
                    x++;
                    y--;
                }
                if (checkInsideGrid(x, y) == 1) writePixels(x, y);
                for (int i = 1; i <= nrPixelsOneSide; i++) {
                    if (checkInsideGrid(x, y - i) == 1) writePixels(x, y - i);
                    if (checkInsideGrid(x, y + i) == 1) writePixels(x, y + i);
                }
            }
        }
    }



    void AfisareSegmentDreapta3_dupay(int x_0, int y_0, int xn, int yn, int nrPixelsOneSide) {
        if (y_0 > yn)
        {
            int temp = x_0;
            x_0 = xn;
            xn = temp;
            temp = y_0;
            y_0 = yn;
            yn = temp;
        }
        if (x_0 < xn && y_0 < yn)
        {
            glColor3d(1.0, 0.1, 0.1);
            glLineWidth(5);
            glBegin(GL_LINES);
                glVertex2d(-1 + epsilon + x_0 * distanceRows, -1 + epsilon + y_0 * distanceColumns);
                glVertex2d(-1 + epsilon + xn * distanceRows, -1 + epsilon + yn * distanceColumns);
            glEnd();
            glLineWidth(2);


            int dx = abs(xn - x_0);
            int dy = abs(yn - y_0);
            int d = dy - 2 * dx;
            int dN =  -2 * dx;
            int dNE = 2 * (dy - dx);
            int x = x_0, y = y_0;
            double m = static_cast<double>(dy) / dx;
            printf("here %f", m);
            if (checkInsideGrid(x, y) == 1) writePixels(x, y);
            for (int i = 1; i <= nrPixelsOneSide; i++) {
                if (checkInsideGrid(x -i, y) == 1) writePixels(x-i, y );
                if (checkInsideGrid(x +i, y ) == 1) writePixels(x+i, y );
            }
            while (y < yn)
            {
                if (d >= 0)
                {

                    d += dN;
                    y++;
                }
                else
                {
                    d += dNE;
                    y++;
                    x++;
                }
                if (checkInsideGrid(x, y) == 1) writePixels(x, y);
                for (int i = 1; i <= nrPixelsOneSide; i++) {
                    if (checkInsideGrid(x - i, y) == 1) writePixels(x - i, y);
                    if (checkInsideGrid(x + i, y) == 1) writePixels(x + i, y);
                }
            }
        }
        if (y_0 < yn and x_0 > xn) {
            int dx = abs(xn - x_0);
            int dy = abs(yn - y_0);

            glColor3d(1.0, 0.1, 0.1);
            glLineWidth(5);
            glBegin(GL_LINES);
                glVertex2d(-1 + epsilon + x_0 * distanceRows, -1 + epsilon + y_0 * distanceColumns);
                glVertex2d(-1 + epsilon + xn * distanceRows, -1 + epsilon + yn * distanceColumns);
            glEnd();
            glLineWidth(2);
            int d = dy - 2 * dx;
            int dN = -2 * dx;
            int dNv = 2 * (dy - dx);
            int x = x_0, y = y_0;
            double m = static_cast<double>(dy) / dx;
            printf("this is my m  %f", m);

            if (checkInsideGrid(x, y) == 1) writePixels(x, y);
            for (int i = 1; i <= nrPixelsOneSide; i++) {
                if (checkInsideGrid(x - i, y) == 1) writePixels(x - i, y);
                if (checkInsideGrid(x + i, y) == 1) writePixels(x + i, y);
            }
        


            while (y < yn) {
                if (d >= 0) {
                    d += dN;
                    y++;
                }
                else {
                    d += dNv;
                    y++;
                    x--;
                }
                if (checkInsideGrid(x, y) == 1) writePixels(x, y);
                for (int i = 1; i <= nrPixelsOneSide; i++) {
                    if (checkInsideGrid(x - i, y) == 1) writePixels(x - i, y);
                    if (checkInsideGrid(x + i, y) == 1) writePixels(x + i, y);
                }
            }
        }
    }


    void AfisarePuncteCerc(int x, int y)
    {
        // primul cadram
        writePixels(x, y);
        writePixels(x + 1, y);
        writePixels(x - 1, y);
   
        
        // simetrie
       
        
         /*   writePixels(y, x);
            writePixels(y - 1, x);
            writePixels(y + 1, x);*/
        
        
     
    }
 

    void AfisareCerc(int R, int x0, int y0)
    {
        int numSegments = 360; 
        glColor3d(1.0, 0.0, 0.0); 

        glBegin(GL_LINE_STRIP);
        for (int i = 0; i < numSegments; ++i)
        {
            double theta = 2.0 * M_PI * static_cast<double>(i) / static_cast<double>(numSegments);
            double x = x0 + R* distanceColumns* cos(theta);
            double y = y0 + R * distanceRows * sin(theta);
            glVertex2d(x + -1+ epsilon , -1 +epsilon + y);            
        }
        glEnd();
 
        int x = R, y = 0;
        int d = 1 - R;
        int dN = 3;
        int dNV = -2 * R + 5;

        if (x + 1 < columns) writePixels(x + 1, y);
        writePixels(x, y);
        if (x - 1 >= 0) writePixels(x - 1, y);

        while (x > y)
        {
            if (d < 0)
            {
                d += dN;
                dN += 2; dNV += 2;
            }
            else
            {
                d += dNV;
                dN += 2; dNV += 4;
                x--;
            }
            y++;

            if (x + 1 < columns) writePixels(x + 1, y);
            writePixels(x, y);
            if (x - 1 >= 0) writePixels(x - 1, y);
        }
        
    }

          
    

    void afisare() {
        glColor3d(0, 0, 0);
        glLineWidth(1);

        double x0 = -1 + epsilon; 
        for (int i = 0; i < columns; i++)
        {
            glBegin(GL_LINES);
            glVertex2d(x0, 1 - epsilon);
            glVertex2d(x0, -1 + epsilon);
            glEnd();

            x0 += distanceColumns;
        }

        double y0 = 1 - epsilon; 
        for (int i = 0; i < rows; i++)
        {
            glBegin(GL_LINES);
            glVertex2d(-1 + epsilon, y0);
            glVertex2d(1 - epsilon, y0);
            glEnd();

            y0 -= distanceRows;
        }
        
        AfisareDreapta3(0, 15, 15, 10, 1);
        AfisareDreapta3(0, 0, 15, 7, 0);
    }

    void afisareCerc() {
      
        glColor3d(0, 0, 0);
        glLineWidth(1);

        double x0 = -1 + epsilon;
        for (int i = 0; i < columns; i++)
        {
            glBegin(GL_LINES);
            glVertex2d(x0, 1 - epsilon);
            glVertex2d(x0, -1 + epsilon);
            glEnd();

            x0 += distanceColumns;
        }

        double y0 = 1 - epsilon;
        for (int i = 0; i < rows; i++)
        {
            glBegin(GL_LINES);
            glVertex2d(-1 + epsilon, y0);
            glVertex2d(1 - epsilon, y0);
            glEnd();

            y0 -= distanceRows;
        }

      
        AfisareCerc(13, 0, 0);
  
            
        
    }
};


void Init(void) {

  glClearColor(1.0,1.0,1.0,1.0);

  glLineWidth(3);

  glPointSize(4);

 
  glPolygonMode(GL_FRONT, GL_LINE);
}

void Display1()
{
    int n = 16;
    int m = 16;
    Grid grid(n, m);
    printf(" aiciia %d",grid.checkInsideGrid(16, 10));
    grid.afisare();

}
void Display2()
{
    int n = 16;
    int m = 16;
    Grid grid(n, m);
    grid.afisareCerc();
}

void Display(void) {
  printf("Call Display\n");

  glClear(GL_COLOR_BUFFER_BIT);

  switch(prevKey) {
  case '1':
      Display1();
    break;
  case '2':
      Display2();
  default:
    break;
  }


  glFlush();
}

// dimensions of the application window
void Reshape(int w, int h) {
  printf("Call Reshape : width = %d, height = %d\n", w, h);


  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}


void KeyboardFunc(unsigned char key, int x, int y) {
  printf("You have pressed <%c>. The mouse has the position %d, %d.\n",
          key, x, y);

  prevKey = key;
  if (key == 27) // escape
    exit(0);
  glutPostRedisplay();
}


void MouseFunc(int button, int state, int x, int y) {
  printf("Call MouseFunc : you have %s the %s button in the position %d %d\n",
    (state == GLUT_DOWN) ? "pressed" : "released",
    (button == GLUT_LEFT_BUTTON) ? 
    "left" : 
    ((button == GLUT_RIGHT_BUTTON) ? "right": "middle"),
    x, y);
}

int main(int argc, char** argv) {

  glutInit(&argc, argv);
   

  glutInitWindowSize(300, 300);

  glutInitWindowPosition(100, 100);

 
  glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);

 
  glutCreateWindow (argv[0]);


  Init();

 
 
  glutReshapeFunc(Reshape);
   

  glutKeyboardFunc(KeyboardFunc);
   

  glutMouseFunc(MouseFunc);


  glutDisplayFunc(Display);
   

  glutMainLoop();

  return 0;
}
