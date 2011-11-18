#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

#include "Render.h"
#include"camera.h"
//#include "Vector.h"

//make a global variable -- for tracking the anglular position of camera
/*camera parameters*/
double cameraAngle;			//in radian
double cameraAngleDelta;

double cameraHeight;	
double cameraRadius;

double rectAngle;	//in degree

double focusX,focusY,focusZ;

bool canDrawGrid;


Camera cam;

vector3d look_at;



/*function definitions*/
void display(){
	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);

	glLoadIdentity();

	
	look_at = cam.Position + cam.Forward;

	gluLookAt( cam.Position.e[0], cam.Position.e[1], cam.Position.e[2], 	
		look_at.e[0], look_at.e[1], look_at.e[2],	0,0,1);


	//gluLookAt(cameraRadius*cos(cameraAngle), cameraRadius*sin(cameraAngle), cameraHeight,		focusX,focusY,focusZ,		0,0,1);
	glMatrixMode(GL_MODELVIEW);
	/*texture enable */
     

	

	renderModel();
}

void animate(){

	glutPostRedisplay();	//this will call the display AGAIN
}



void keyboardListener(unsigned char key, int x,int y){
	float ang = 30*3.1416/180;
	switch(key){
		case 'a':
			printf("paiseeeee");
			//printf("%f\n", sin(45*3.1416/180) );
			
			cam.Yaw(30.0);

			//rotation around z axis Yawning 
			//x_pos = x_pos*cos(ang) - y_pos*sin(ang);
			//y_pos = x_pos*sin(ang) + y_pos*cos(ang);

			//x_look = x_look*cos(ang) - y_look*sin(ang);
			//y_look = x_look*sin(ang) + y_look*cos(ang);
			break;

		case 'w':   // pitch - look up 
			cam.Pitch(10.0);
			break;
		case 's':
			cam.Pitch(-10.0);
			break;

	    case 'd':
			printf("paiseeeee");
			cam.Yaw(-30.0);
			//rotation around z axis Yawning 
			//x_pos = x_pos*cos(-45) - y_pos*sin(-45);
			//y_pos = x_pos*sin(-45) + y_pos*cos(-45);
			break;

		case '1':	//reverse the rotation of camera
			//cameraAngleDelta = -cameraAngleDelta;
			break;

		case '2':	//increase rotation of camera by 10%
			//cameraAngleDelta *= 1.1;
			break;

		case '3':	//decrease rotation
			//cameraAngleDelta /= 1.1;
			break;

		case '8':	//toggle grids
			canDrawGrid = 1 - canDrawGrid;
			break;

		case 27:	//ESCAPE KEY -- simply exit
			exit(0);
			break;

		default:
			break;
	}
}

void specialKeyListener(int key, int x,int y){
	switch(key){
		case GLUT_KEY_DOWN:		//down arrow key
			//cameraRadius += 10;
			//y_pos -= 10;
			//y_look -= 10;
			cam.Walk(10);
			break;
		case GLUT_KEY_UP:		// up arrow key
			//if(cameraRadius > 10)
			//	cameraRadius -= 10;
		//	y_pos += 10;
		//	y_look += 10;
			cam.Walk(-10);
			break;

		case GLUT_KEY_RIGHT:
			//x_pos += 10;
			//x_look += 10;
			cam.Strafe(-10);
			break;

		case GLUT_KEY_LEFT:
			//x_pos -= 10;
			//x_look -= 10;
			cam.Strafe(10);
			break;

		case GLUT_KEY_PAGE_UP:
			//cameraHeight += 10;
			//z_pos += 10;
			//z_look += 10;
			cam.GoUp(10);
			break;
		case GLUT_KEY_PAGE_DOWN:
			//cameraHeight -= 10;
			//z_pos -= 10;
			//z_look -= 10;

			cam.GoUp(-10);

			break;

		case GLUT_KEY_INSERT:
			break;

		case GLUT_KEY_HOME:
			break;
		case GLUT_KEY_END:
			break;

		default:
			break;
	}
}

void mouseListener(int button, int state, int x, int y){	//x, y is the x-y of the screen (2D)
	switch(button){
		case GLUT_LEFT_BUTTON:
		
			break;

		case GLUT_RIGHT_BUTTON:
			//........
			break;

		case GLUT_MIDDLE_BUTTON:
			//........
			break;

		default:
			break;
	}
}

void init(){
	//codes for initialization
/*	cameraAngle = 0;	//// init the cameraAngle
	cameraAngleDelta = 0.002;
	rectAngle = 0;
	canDrawGrid = true;
	cameraHeight = 1500;
	cameraRadius = 500;



	focusX=0;
	focusY=0;
    focusZ=0;

*/

	glEnable(GL_TEXTURE_2D);






	glClearColor(BLACK, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(70,	1,	0.1,	10000.0);


}

int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(1366, 768);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("Torre Vasco Da Gama");



	init();
	glEnable(GL_DEPTH_TEST);	//enable Depth Testing
	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
