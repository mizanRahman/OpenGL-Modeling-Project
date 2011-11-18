
/*lighting params*/

// Vectors for colours and properties of materials.
const GLfloat red[] = { 0.8f, 0.0, 0.0, 1.0 };
const GLfloat blue[] = { 0.0, 0.2f, 1.0, 1.0 };
const GLfloat white[] = { 1.0, 1.0, 1.0, 1.0 };
const GLfloat black[] = { 0.0, 0.0, 0.0, 1.0 };
const GLfloat polished[] = { 100.0 };
const GLfloat dull[] = { 0.0 };

// Position the light at the origin.
const GLfloat light_pos[] = { 0.0, 0.0, 0.0, 1.0 };

// Translation values for light.
GLfloat move_y = 0.0;
GLfloat move_z = 0.0;

// Attenuation factors for light.
GLfloat const_att = 1.0;


void lightUnset()
{
	glDisable(GL_LIGHTING);
}

void lightSetup()
{

	
	// Initialize the light.
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white);


	// Move model into view
	
	// Position the light and show where it is
	glPushMatrix();
		glTranslatef(500.0, 500.0, 200.0);
		//glTranslatef(0.0, move_y, move_z);
		glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, const_att);
		glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
		glDisable(GL_LIGHTING);
		glColor3d(0.9, 0.9, 0.5);
		glutSolidSphere(0.1, 10, 10);
		glEnable(GL_LIGHTING);
	glPopMatrix();

}