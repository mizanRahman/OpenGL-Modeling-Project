#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include<GL/glut.h>

#include "vector3D.h"
#include<iostream>
using namespace std;

#define BLACK 0, 0, 0

class Camera {
		public:
		
		vector3d Position;
		
		vector3d Along;   // x
		vector3d Forward;  // y 
		vector3d Up;      // z

		double DEG2RAD;
		
		Camera() {

			DEG2RAD= 3.1416/180;

			Position = vector3d(0, 150, 100);  // initial starting position 

			Along =  vector3d (1, 0, 0);  // x axis
			Forward =  vector3d (0, -1, 0);  // !! -1 in Y axis 
			Up =  vector3d (0, 0, 1);     // z axis 
		}
		vector3d Camera::GetPosition() {
			return Position;
		}
		void Update() {
			//GLfloat x = DotProduct(Along, Position);
			float x = dot(Along, Position);
			float y = dot(Forward, Position);
			float z = dot(Up, Position);

	/*	double ViewMatrix[4][4];
		ViewMatrix[0][0] = Along.e[0];   // Along.x
		ViewMatrix[0][1] = Up.e[0];
		ViewMatrix[0][2] = -Forward.e[0];
		ViewMatrix[0][3] = 0.0;

		ViewMatrix[1][0] = Along.e[1];   // Along.y
		ViewMatrix[1][1] = Up.e[1];
		ViewMatrix[1][2] = -Forward.e[1];
		ViewMatrix[1][3] = 0.0;
		
		ViewMatrix[2][0] = Along.e[2];  // Along.z
		ViewMatrix[2][1] = Up.e[2];
		ViewMatrix[2][2] = -Forward.e[2];
		ViewMatrix[2][3] = 0.0;

		ViewMatrix[3][0] = -x;
		ViewMatrix[3][1] = -y;
		ViewMatrix[3][2] = z;
		ViewMatrix[3][3] = 1.0; */
	
		}

		
		void Yaw(float theta)
		{
			  Along = Along * cos(theta * DEG2RAD) + Forward * sin(theta * DEG2RAD);
			  //Along.Normalize();
			 Forward = cross(Along, Up) * -1.0;
			 Update();
		}
		
		void Pitch(float theta)
		{
		
			Forward = Forward * cos(theta * DEG2RAD) + Up * sin(theta * DEG2RAD);
			//Forward.Normalize();
			Up = cross(Forward, Along) * -1.0;
			Update();

		
		}
		
		void Roll(float theta)
		{
			Up = Up * cos(theta * DEG2RAD) - Along * sin(theta * DEG2RAD);
			//Up.Normalize();
			Along = cross(Forward, Up);
			Update();

		}

		void Walk(float length)
		{
			Position -= Forward * length; // Air camera
	 	  Update();

		}

		void Strafe( float length)
		{
			Position += Along * length; // Air camera
			Update();

		}
		void GoUp( float length)
		{
			Position += Up * length; // Air camera
			Update();
		}


};


//make a global variable -- for tracking the anglular position of camera

Camera cam;

vector3d look_at;



double rectAngle;	//in degree

bool canDrawGrid;

void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(BLACK, 0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera is looking?
	//3. Which direction is the camera's UP direction?

	//instead of CONSTANT information, we will define a circular path.
//	gluLookAt(-30,-30,50,	0,0,0,	0,0,1);

	
	//NOTE: the camera still CONSTANTLY looks at the center
	// cameraAngle is in RADIAN, since you are using inside COS and SIN


	// my edit
	//gluLookAt( 150, 150, 100,		0,0,0,		0,0,1);

	//vector3d 
	look_at = cam.Position + cam.Forward;

	gluLookAt( cam.Position.e[0], cam.Position.e[1], cam.Position.e[2], 	
		look_at.e[0], look_at.e[1], look_at.e[2],	0,0,1);
	
	
	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects
	//rotate this rectangle around the Z axis

	glPushMatrix();{	//STORE the state
		glRotatef(rectAngle,	0,0,1);	// in DEGREE
		//a simple rectangles
		glColor3f(0.3, 0.4, 0.8);
		glBegin(GL_QUADS);{
			glVertex3f(0,0,30);
			glVertex3f(10,0,30);
			glVertex3f(10,20,30);
			glVertex3f(0,20,30);
		}glEnd();

		///lets draw another one in the XY plane --- i.e. Z = 0
		glColor3f(0.15, 0.2, 0.4);
		glBegin(GL_QUADS);{
			glVertex3f(0,0,0);
			glVertex3f(10,0,0);
			glVertex3f(10,20,0);
			glVertex3f(0,20,0);
		}glEnd();
	}glPopMatrix();		//the effect of rotation is not there now.

/*	//FORGET THE FIELD
	//an square field
	glColor3f(0.4, 1, 0.4);
	glBegin(GL_QUADS);{
		glVertex3f(-100,-100,0);
		glVertex3f(100,-100,0);
		glVertex3f(100,100,0);
		glVertex3f(-100,100,0);
	}glEnd();
*/

	//some gridlines along the field
	int i;

	//WILL draw grid IF the "canDrawGrid" is true:

	if(canDrawGrid == true){
		glColor3f(0.3, 0.3, 0.3);	//grey
		glBegin(GL_LINES);{
			for(i=-10;i<=10;i++){

				if(i==0)
					continue;	//SKIP the MAIN axes

				//lines parallel to Y-axis
				glVertex3f(i*10, -100, 0);
				glVertex3f(i*10,  100, 0);

				//lines parallel to X-axis
				glVertex3f(-100, i*10, 0);
				glVertex3f( 100, i*10, 0);
			}
		}glEnd();
	}

	// draw the two AXES
	glColor3f(1, 1, 1);	//100% white
	glBegin(GL_LINES);{
		//Y axis
		glVertex3f(0, -150, 0);	// intentionally extended to -150 to 150, no big deal
		glVertex3f(0,  150, 0);

		//X axis
		glVertex3f(-150, 0, 0);
		glVertex3f( 150, 0, 0);
	}glEnd();


	//FOUR spheres

	//draw first two : as half spheres: bottom half.
	/// the cutting plane equation: z = 30
	/// we will keep the points with
	//		z <= 30
	//OR	0.x + 0.y + 1.z - 30 <= 0
	//OR	0.x + 0.y - 1.z + 30 >= 0	//// standard format:: ax + by + cz + d >= 0
	
	double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = 0;	//0.y
	equ[2] = -1;//-1.z
	equ[3] = 30;//30

	glClipPlane(GL_CLIP_PLANE0,equ);

	//now we enable the clip plane

	glEnable(GL_CLIP_PLANE0);{
		glColor3f(0,0.3,0.8);	//blue

		glPushMatrix();{
			glTranslatef(50,50,30);
			glutWireSphere(20, 20, 20);	//radius, slices(XY), stacks(Z) -- like earth
		}glPopMatrix();

		glPushMatrix();{
			glTranslatef(50,-50,30);
			glutWireSphere(20, 20, 20);
		}glPopMatrix();
	}glDisable(GL_CLIP_PLANE0);


	glColor3f(0.8,0.3,0);
	glPushMatrix();{
		glTranslatef(-50,-50,30);
		glScalef(2, 2, 0.5);
		glutWireSphere(10, 20, 20);
	}glPopMatrix();

	glColor3f(0.7,0.8,0);
	glPushMatrix();{
		glScalef(2, 2, 0.5);
		glTranslatef(-50,-50,30);
		glutWireSphere(10, 20, 20);
	}glPopMatrix();

	//////// ------ NOTE ---- ORDER matters. compare last two spheres!

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}

void animate(){
	//codes for any changes in Camera

	//cameraAngle += cameraAngleDelta;	// camera will rotate at 0.002 radians per frame.	// keep the camera steady NOW!!
	
	//codes for any changes in Models
	
	rectAngle -= 1;

	//MISSING SOMETHING? -- YES: add the following
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

	
	rectAngle = 0;
	canDrawGrid = true;



	//clear the screen
	glClearColor(BLACK, 0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);
	
	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(70,	1,	0.1,	10000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view in the X direction (horizontally)
	//near distance
	//far distance
}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//ADD keyboard listeners:
	glutKeyboardFunc(keyboardListener);
	glutSpecialFunc(specialKeyListener);

	//ADD mouse listeners:
	glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
