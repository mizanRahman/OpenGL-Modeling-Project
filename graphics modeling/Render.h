#include "tga.h"
#include "light.h"

#define BLACK 0, 0, 0
#define SKY .9, 0.8, 0.5



int baseWidth=1000;
int baseBreadth=1000;
float pillarXlength=102.5;
float pillarYlength=61.8;
float pillarZlength=980.2;
double lobbyCoord[][2]={{1393.5,0},{1393.5,1890},{1191,1890+1451},{893,1890+1451+954},{558.5,1890+1451+954+578}};
double  lobbyHeight=960;
GLUquadric*	 quad=gluNewQuadric();





/* texture parameters */
GLuint LoadTexture(char *TexName);


GLuint TexID[10];






void rectCube(double length,double width, double height){
	glPushMatrix();{
			//foot1			
			glTranslated(0,-width/2,height/2);			
			glScalef(length,width,height);
			glutSolidCube(1);				
			 



	}glPopMatrix();
		

}



void drawHalfBase()
{
	glPushMatrix();{
		
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBegin(GL_POLYGON);
			
			glTexCoord2f(0.0f,0.0f);	glVertex3f(0,0,0);
			glTexCoord2f(1.0f,0.0f);	glVertex3f(1393.5,0,0);
			glTexCoord2f(1.0f,1890.0f/4873);	glVertex3f(1393.5,1890,0);
			glTexCoord2f(1191.0f/1393,3341.0f/4873);	glVertex3f(1191,1890+1451,0);		
			glTexCoord2f(893.0f/1393,4295.0f/4873);	glVertex3f(893,1890+1451+954,0);		
			glTexCoord2f(558.5f/1393,1.0f);	glVertex3f(558.5,1890+1451+954+578,0);		
			glTexCoord2f(0.0f,1.0f);	glVertex3f(0,1890+1451+954+578,0);

		glEnd();

	}glPopMatrix();

}

void drawFullBase()
{
	glPushMatrix();{
	

		drawHalfBase();
		glScalef(-1,1,1);
		drawHalfBase();
		
	}glPopMatrix();
}


void drawLobbySide()
{
	glPushMatrix();{
			/*overlap fixing*/
			//glScalef(1.2,1,1);
			
		
			glColor3f(SKY);

			glBegin(GL_QUADS);{
				glTexCoord2f(1.0f,1.0f); glVertex3f(lobbyCoord[0][0],lobbyCoord[0][1],0);
				
				glTexCoord2f(1.0f,0.0f); glVertex3f(lobbyCoord[1][0],lobbyCoord[1][1],0);
				
				glTexCoord2f(0.0f,0.0f); glVertex3f(lobbyCoord[1][0],lobbyCoord[1][1],lobbyHeight);
				
				glTexCoord2f(0.0f,1.0f); glVertex3f(lobbyCoord[0][0],lobbyCoord[0][1],lobbyHeight);
			}glEnd();

			glBegin(GL_QUADS);{
				glTexCoord2f(1.0f,1.0f); glVertex3f(lobbyCoord[1][0],lobbyCoord[1][1],0);
				
				glTexCoord2f(1.0f,0.0f); glVertex3f(lobbyCoord[2][0],lobbyCoord[2][1],0);
				
				glTexCoord2f(0.0f,0.0f); glVertex3f(lobbyCoord[2][0],lobbyCoord[2][1],lobbyHeight);
				
				glTexCoord2f(0.0f,1.0f); glVertex3f(lobbyCoord[1][0],lobbyCoord[1][1],lobbyHeight);
			}glEnd();

			
			glBegin(GL_QUADS);{
				glTexCoord2f(1.0f,1.0f); glVertex3f(lobbyCoord[2][0],lobbyCoord[2][1],0);
				glTexCoord2f(1.0f,0.0f); glVertex3f(lobbyCoord[3][0],lobbyCoord[3][1],0);
				
				glTexCoord2f(0.0f,0.0f); glVertex3f(lobbyCoord[3][0],lobbyCoord[3][1],lobbyHeight);
				
				glTexCoord2f(0.0f,1.0f); glVertex3f(lobbyCoord[2][0],lobbyCoord[2][1],lobbyHeight);
				
			}glEnd();

			
			glBegin(GL_QUADS);{
				glTexCoord2f(1.0f,1.0f); glVertex3f(lobbyCoord[3][0],lobbyCoord[3][1],0);
				glTexCoord2f(1.0f,0.0f); glVertex3f(lobbyCoord[4][0],lobbyCoord[4][1],0);
				
				glTexCoord2f(0.0f,0.0f); glVertex3f(lobbyCoord[4][0],lobbyCoord[4][1],lobbyHeight);
				
				glTexCoord2f(0.0f,1.0f); glVertex3f(lobbyCoord[3][0],lobbyCoord[3][1],lobbyHeight);
				
				
			}glEnd();

		
		}glPopMatrix();
		
}


void drawLobbySides()
{

	glPushMatrix();{

		drawLobbySide();
		glScalef(-1,1,1);
		drawLobbySide();
	
	}glPopMatrix();

}


void renderModel()
{	
	
	

	TexID[0]=LoadTexture("Logo.tga");	
	TexID[1]=LoadTexture("tiles.tga");
	


	//Render();
	//lobby drawing


	
	glPushMatrix();{



		
		glPushMatrix();{
		//lower pillar drawing
			glColor3f(.2, 0.2, 0.2);
			rectCube(pillarXlength,pillarYlength,pillarZlength);
			glColor3f(0, .5, .8);
		
		}glPopMatrix();
			
	/*********** enable this code for lighting **************
			
		lightSetup();
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
		glMaterialfv(GL_FRONT, GL_SPECULAR, blue);
		glMaterialfv(GL_FRONT, GL_SHININESS, polished);

	/*********************/


	double equ[4];

	equ[0] = 0;	//0.x
	equ[1] = -1;	//0.y
	equ[2] = 0;//-1.z
	equ[3] = -pillarXlength/2;//30

	glClipPlane(GL_CLIP_PLANE0,equ);
	/*Draw torus frame*/

	glEnable(GL_CLIP_PLANE0);{			
		glPushMatrix();{
			glColor3f(0.91, 0.92, 0.92);
			glTranslated(0,600,1233/2);
			glRotated(90, 0.0, 1.0, 0.0);
			//glutSolidCube(200);		
			glutSolidTorus(10,860,50,120);//inner radius,outer radius, nsides, nrings 
		}glPopMatrix();	
	}glDisable(GL_CLIP_PLANE0);
	
		
		glBindTexture(GL_TEXTURE_2D,TexID[1]);
		glScalef(0.1,0.1,0.1);
		glPushMatrix();{
				glColor3f(.8, 0.8, 0.8);
				drawFullBase();
				glTranslated(0,0,906);
				drawFullBase();

						
		
		}glPopMatrix();
		
		
		glBindTexture(GL_TEXTURE_2D,TexID[0]);
		drawLobbySides();

//	lightUnset();
		
	
		
		gluQuadricTexture(quad, GLU_TRUE);
		gluQuadricNormals(quad, GLU_SMOOTH);
		glBindTexture(GL_TEXTURE_2D,TexID[1]);
		
		glTranslated(0,-618/2,9802);//translate pilar width/2 and pillar height
		//big dome
  
		gluCylinder(quad,1960/2,1960/2,811,12,120);
		//gluQuadricTexture(quad, GLU_FALSE);
		glTranslated(0,0,-1);
		gluDisk(quad,0,1960/2,12,1200);
		glTranslated(0,0,812);
		gluDisk(quad,0,1960/2,12,1200);




		//upper pillar
			glPushMatrix();{
			//pillar drawing
				glTranslated(0,(618-161)/2,0);
				glColor3f(.2, 0.2, 0.2);
				rectCube(1025,447,850);
				glColor3f(0, .5, .8);
			
			}glPopMatrix();
		

		glColor3f(.4, 0.6, 0.2);
		//upper small dome

		gluCylinder(quad,1090/2,1090/2,468,10,120);
		glTranslated(0,0,469);
		glColor3f(.5, 1, 0.3);
		gluDisk(quad,0,1090/2,10,1200);
		
	
	




	
		
	}glPopMatrix();






	//basement solid
	glColor3f(0.6, 0.4, 0.2);
	glPushMatrix();{//STORE the state
		glTranslated(-baseWidth/2,-baseBreadth/2,0);
		glBegin(GL_QUADS);{
			/*
			X->Width/2
			Y->Breadth/2
			*/
			glVertex3f(baseWidth,0,0);
			glVertex3f(baseWidth,baseBreadth,0);
			glVertex3f(0,baseBreadth,0);
			glVertex3f(0,0,0);
		}glEnd();
	}glPopMatrix();
	
	glutSwapBuffers();
}



 GLuint LoadTexture(char *TexName)
  {
   TGAImg Img;        // Image loader
   GLuint Texture;

  // Load our Texture
   if(Img.Load(TexName)!=IMG_OK)
    return -1;

   glGenTextures(1,&Texture);            // Allocate space for texture
   glBindTexture(GL_TEXTURE_2D,Texture); // Set our Tex handle as current

   // Create the texture
    if(Img.GetBPP()==24)
     glTexImage2D(GL_TEXTURE_2D,0,3,Img.GetWidth(),Img.GetHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,Img.GetImg());
    else if(Img.GetBPP()==32)
     glTexImage2D(GL_TEXTURE_2D,0,4,Img.GetWidth(),Img.GetHeight(),0,GL_RGBA,GL_UNSIGNED_BYTE,Img.GetImg());
    else
     return -1;

   // Specify filtering and edge actions
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

   return Texture;
  }
