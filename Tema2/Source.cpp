#include <GL/glut.h>
#include <cmath>
#include <limits>

// Define constants for positive and negative infinity
const double POSITIVE_INFINITY = std::numeric_limits<double>::infinity();
const double NEGATIVE_INFINITY = -std::numeric_limits<double>::infinity();

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
/**********************************

  The reader of this program should not limit
  himself/herself to the comments of this
  program.

  If one wants to read more about the syntax and
  the semantics of OpenGL functions used in this
  program, one should read the beginning of the
  paragraph 2.6 "Begin/End Paradigm", the
  paragraph 2.6.1 "Begin and End Objects" from the
  file glspec15.pdf at page 25/333 and the index
  from the end of that file. One could also
  read the references to the GLUT functions from
  the file glut-3.spec.pdf.



  H O W  T O  R E A D  T H I S  P R O G R A M ?

  Start from the function "main" and follow the
  instruction flow, paying attention to the fact that
  this program belongs to the event-driven programming
  paradigm. So pay attention to what happens when
  the user presses a key, moves the mouse or presses a
  mouse button. There are also some special events: the
  redrawing of the application window, etc.
  Identify what happens in the program when one of these
  events occurs.

  **********************************/


  /**********************************
    With respect to the include-file directives, see the
    example program from homework 1; in the following it
    was made the assumption that you are using GLUT locally,
    in your project and you didn't install it as an
    Administrator
    **********************************/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>


    // the size of the window measured in pixels
#define dim 300

unsigned char prevKey;

// the graph of the Conchoid of Nicomedes
void Display1() {
    double xmax, ymax, xmin, ymin;
    double a = 1, b = 2;
    double pi = 4 * atan(1.0);
    double ratia = 0.05;
    double t;

    /**********************************
       Maximum/minimum values of x and y are computed.
       These values will be further used in scaling the
       original graph of the curve.
       These values are stored in the variables
       xmax, ymax, xmin, ymin: e.g., xmax is initialized
       with a value smaller than any of possible values
       of x; if in doubt or you cannot estimate it, use
       DBL_MIN instead (or DBL_MAX for minimum values).
       These DBL_* constants are found in <float.h> which
       need to be included.
       E.g., xmax is initialized with a - b - 1 because
       x(t) = a +/- b * cos(t) and for t in (-pi/2, pi/2),
       cos(t) is in (0, 1), so b * cos(t) is in (0, b),
       so +/- b * cos(t) is in (-b, b), so x(t) is in
       (a-b, a+b) and one can safely choose a-b-1 because
       a-b-1 < a-b.
       For y(t) we see that in its expression appears
       tan(t) which varies in (-inf,+inf) when t
       varies in (-pi/2, pi/2).
      **********************************/
    xmax = a - b - 1;
    xmin = a + b + 1;
    ymax = ymin = 0;
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = a + b * cos(t);
        xmax = (xmax < x1) ? x1 : xmax;
        xmin = (xmin > x1) ? x1 : xmin;

        x2 = a - b * cos(t);
        xmax = (xmax < x2) ? x2 : xmax;
        xmin = (xmin > x2) ? x2 : xmin;

        y1 = a * tan(t) + b * sin(t);
        ymax = (ymax < y1) ? y1 : ymax;
        ymin = (ymin > y1) ? y1 : ymin;

        y2 = a * tan(t) - b * sin(t);
        ymax = (ymax < y2) ? y2 : ymax;
        ymin = (ymin > y2) ? y2 : ymin;
    }

    /**********************************
       At this line, we have found that the graph of the Conchoid
       is included in the rectangle having the edges x = xmin,
       x = xmax, y = ymin and y = ymax.
       We would like that the rectangle should be symmetric with
       respect to the Ox and Oy axes.
       We store in xmax and ymax the maximum of absolute values
       max(|xmax|,|xmin|) and max(|ymax|,|ymin|).
       Now we know that the graph of the Conchoid is included in
       the rectangle [-xmax, xmax] x [-ymax, ymax].
      **********************************/

    xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
    ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

    /**********************************
       At this line, we can perform the scaling. All the points
       scaled are visible (i.e., in the rectangle [-1,1]x[-1,1]).
       Because we have -xmax <= x <= xmax we get
       -1 <= x / xmax <= 1. Idem for y.
       In order to correctly display the graph of the Conchoid,
       one should use the exact same points that were used in
       the computation of the scaling factor.
      **********************************/

    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x2, y2);
    }
    glEnd();
}

// The graph of the function 
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$, 
void Display2() {
    double pi = 4 * atan(1.0);
    double xmax = 8 * pi;
    double ymax = exp(1.1);
    double ratia = 0.05;


    /**********************************
       For this example, the computation of the scaling factors
       is not needed. Because x is in the interval [0, 8pi]
       the scaling factor for x is 8pi because x/(8pi) is in
       [0,1]. In the case of the exponential function we know
       that if x is [0,8pi] then sin x is in [-1,1] so
       e^(-sin x) is in [1/e, e] and thus it is safe to use
       e^(1.1) as a scaling factor.
      **********************************/
    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_LINE_STRIP);
    for (double x = 0; x < xmax; x += ratia) {
        double x1, y1;
        x1 = x / xmax;
        y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();
}

double d(double x)
{
    return std::abs(x - round(x));
}

double f(double x) {
    if (x == 0) {
        return 1;
    }
    else {
        return d(x) / x;
    }
}

void Display3() {
    const double xmax = 120;
    double ymax = 1 + 0.01;
    const double ratia = 0.1;
    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    for (double x = 0; x <= 100; x += ratia) {
        double x1, y1;
        x1 = x / xmax;
        y1 = f(x) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();
}

void Display4() {
    double a = 0.2;
    double pi = 4 * atan(1.0);
    double ratia = 0.0001;
    double t;
    double x1, y1;

    double xmin = 0;
    double ymax = 0;


    glColor3f(1, 0.1, 0.1); // rosu
    glBegin(GL_TRIANGLES);
    for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
        if ((t != -pi / 6) && (t != pi / 6)) {
            double x, y;
            x = a / (4 * (cos(t) * cos(t)) - 3);
            y = (a * tan(t)) / (4 * (cos(t) * cos(t)) - 3);
            if (x >= -0.95 && y <= 0.95) {
                if (x < xmin) {
                    xmin = x;
                    y1 = y;
                }
                if (y > ymax) {
                    ymax = y;
                    x1 = x;
                }
                double ratio = 0.00005;
                double tx = -0.95 + ratio * (x + 0.95);
                double ty = 0.95 - ratio * (0.95 - y);
                glVertex2f(-0.95, 0.95);
                glVertex2f(x, y);
                glVertex2f(tx, ty);
            }
        }
    }
    glEnd();

    glColor3f(0.1, 0.1, 1); // blue

    glBegin(GL_POINTS);
    for (t = -pi / 2 + ratia; t < -pi / 6; t += ratia) {
        if ((t != -pi / 6) && (t != pi / 6)) {
            double x, y;
            x = a / (4 * (cos(t) * cos(t)) - 3);
            y = (a * tan(t)) / (4 * (cos(t) * cos(t)) - 3);
            if (x >= -0.95 && y <= 0.95) {
                glVertex2f(x, y);
            }
        }
    }

    glEnd();

    glColor3f(0.1, 0.1, 1); // blue
    glBegin(GL_LINES);
    glVertex2f(xmin, ymax);
    glVertex2f(xmin, y1);

    glVertex2f(xmin, ymax);
    glVertex2f(x1, ymax);
    glEnd();

}


void Display5() {
    double a = 0.1, b = 0.2;
    double ratia = 0.05;

    double t_start = -9.5;
    double t_end = 9.5;

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0, 0.0, 0.0);
    for (double t = t_start; t <= t_end; t += ratia) {
        double x = a * t - b * sin(t);
        double y = a - b * cos(t);
        glVertex2f(x, y);
    }
    glEnd();
}

void Display6() {
    double pi = 4 * atan(1.0);
    double xmax = pi / 4;
    double ymax = 0.4 * sqrt(2);
    const double a = 0.4;
    const double ratia = 0.001;
    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);
    for (double t = -pi / 4; t <= pi / 4; t += ratia) {
        double r1 = a * sqrt(2 * cos(2 * t));
        double x1 = r1 * cos(t);
        double y1 = r1 * sin(t);
        glVertex2f(x1, y1);
    }
    glEnd();
    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);
    for (double t = -pi / 4; t <= pi / 4; t += ratia) {
        double r1 = -a * sqrt(2 * cos(2 * t));
        double x1 = r1 * cos(t);
        double y1 = r1 * sin(t);
        glVertex2f(x1, y1);
    }
    glEnd();
}

void Display7() {
    const double a = 0.02;
    const double ratia = 0.001;
    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);
    for (double t = 0; t <= 10; t += ratia) {
        double r1 = a * exp(1 + t);
        double x1 = r1 * cos(t);
        double y1 = r1 * sin(t);
        glVertex2f(x1, y1);
    }
    glEnd();
}


void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1.2);

    glPointSize(1.2);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (prevKey) {
    case '1':
        Display1();
        break;
    case '2':
        Display2();
        break;
    case '3':
        Display3();
        break;
    case '4':
        Display4();
        break;
    case '5':
        Display5();
        break;
    case '6':
        Display6();
        break;
    case '7':
        Display7();
        break;
    default:
        break;
    }

    glFlush();
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}
