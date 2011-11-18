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



