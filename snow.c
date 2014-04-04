/* londo_hw1.c
 *
 * Laura Londo
 * 9 February 2014
 * HW#1
 *
 * This program recursively draws a fractal begining with one square. Every
 * square has two smaller squares branching from the bottom of the parent at
 * rotated by 45-degree angles
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>

float WINDOW_SIZE = 700;

void squares(float topLeftx,  float topLefty,   //top left corner
			 float topRightx, float topRighty,  //top right corner
			 float n)							//
{
	//1st point						top left corner
	float Q1x = topLeftx;
	float Q1y = topLefty;

	//2nd point						top right corner
	float Q2x = topRightx;
	float Q2y = topRighty;

	//3rd point						bottom right corner
	float Q3x = Q2x - (Q1y - Q2y);
	float Q3y = Q2y + (Q1x - Q2x);

	//4th point						bottom left corner
	float Q4x = (Q1x-Q2x) + Q3x;
	float Q4y = (Q1y-Q2y) + Q3y;

	//display filled square
	glBegin(GL_POLYGON);
	glColor3f(n*n*n*n*n-0.3, n*n*n*n-0.3, n*n*n-0.3);
	glVertex3f(Q1x, Q1y, 0.0);
	glVertex3f(Q2x, Q2y, 0.0);
	glVertex3f(Q3x, Q3y, 0.0);
	glVertex3f(Q4x, Q4y, 0.0);
	glEnd();

	//display square outline
	glColor3f(n, n, n);
	glBegin(GL_LINES);
	glVertex3f(Q1x, Q1y, 0.0);
	glVertex3f(Q2x, Q2y, 0.0);
	glVertex3f(Q2x, Q2y, 0.0);
	glVertex3f(Q3x, Q3y, 0.0);
	glVertex3f(Q3x, Q3y, 0.0);
	glVertex3f(Q4x, Q4y, 0.0);
	glVertex3f(Q4x, Q4y, 0.0);
	glVertex3f(Q1x, Q1y, 0.0);
	glEnd();


	//calculate begining of next square
	float ACx = (Q3x - Q1x)/2;	//half of the diagonal
	float ACy = (Q3y - Q1y)/2;
	float newx = ACx + Q4x;		// point of iscoceles right triangle
	float newy = ACy + Q4y;		// off of the bottom of the square


	//length of a side of the square
	float dist = sqrt(((Q1x-Q2x)*(Q1x-Q2x)) + ((Q1y-Q2y)*(Q1y-Q2y)));

				// 1/700 = x/20
				//20/700 = 1 px?
	if( dist > (20.0/WINDOW_SIZE)) { //if the square is larger than 1 pixel
		squares(Q4x, Q4y, newx, newy, n-0.1); //left recursion
		squares(newx, newy, Q3x, Q3y, n-0.1); //right recursion
	}


}




void display(void)
{
  glClear( GL_COLOR_BUFFER_BIT);

  squares(-1.6, 5.0, 1.6, 5.0, 1.0); //call he recursive function

  printf("DONE\n");
  glFlush();
}




int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode ( GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WINDOW_SIZE, WINDOW_SIZE);
  glutCreateWindow ("fractal");

  glClearColor(0.0, 0.0, 0.0, 0.0);         // black background
  glMatrixMode(GL_PROJECTION);              // setup viewing projection
  glLoadIdentity();                         // start with identity matrix
  gluOrtho2D(-10.0, 10.0, -10.0, 10.0);

  glutDisplayFunc(display);
  glutMainLoop();
  return 0;
}
