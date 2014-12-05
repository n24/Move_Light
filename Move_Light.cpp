# include <stdlib.h>
# include <glut.h>
# include <stdio.h>

// Enumeration Constants used to select object and create the menu.

enum {TORUS = 1,TEAPOT,SPHERE,CUBE,DOD,TET,ISO,RESET,WIRE,SOLID,QUIT,
	  STOP,X,Y,Z,ENABLE,DISABLE,IX,IY,IZ,DX,DY,DZ,DS,IS,
	  BG1,BG2,BG3,BG4,BG5,BG6,BG7,BG8,LC1,LC2,LC3,LC4,LC5,LC6,LC7};

// Global Declarations.

int pflag = 0;							// Used to display developer name.
int spin = 0;							// Rotation angle for moving the light.
int obj = TORUS;						// Current object.
int begin;								// Used to hold x-axis value during mouse movement.
int screen = 0;							// Indicates the current screen.
int width, height;						// Width and height of the screen.
int mode = 0;							// Indicates the mode. 0 = solid. 1 = wire.
int light = 1;							// Indicates the state of light. 1 = enable. 0 = disable.
int bg_col = 0;							// Background color [0 = {0,0,0,0},1 = {0,0,1,0},....7 = (1,1,1,0}].
int x_axis = 0, y_axis = 0, z_axis = 0;	// Rotation axis.
float p = 0.0, q = 47.0, v = 0.0;		// Used to display moving college name, welcome message and developer name.
float speed_value = 1.0;				// Rotation speed.
int lg_col = 0;							// Index value for the diffuse array in display function.
int menu_state = 1;						// State of menu. 1 = not in use. 0 = in use.
void *font;								// Font of bitmap character.
GLfloat rotate[] = {0.0,0.0,0.0};		// Rotation values.
GLfloat viewer[] = {0.0,0.0,0.1};		// Camera position values.

// Function Definitions
// NOTE: We are using the glutPostRedisplay() in Idle function. So, no need to call that in evry function.

void MyReshape (int w, int h) {
	width = w, height = h;
	glViewport (0, 0, w, h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluPerspective (50.0, (GLfloat) width / (GLfloat) height, 1.0, 100.0);
	glMatrixMode (GL_MODELVIEW);
}

void Myinit () {
	glEnable (GL_LIGHTING);
	glEnable (GL_LIGHT0);
	glEnable (GL_DEPTH_TEST);
	glEnable (GL_NORMALIZE);
	glEnable (GL_LINE_SMOOTH);
	glDepthFunc (GL_LESS);
}

void Movelight (int button, int state, int x, int y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		begin = x;
}

void Motion (int x, int y) {
	spin = (spin + (x - begin)) % 360;
	begin = x;
}

void Reset () {
	rotate[0] = rotate[1] = rotate[2] = viewer[0] = viewer[1] = 0.0;
	viewer[2] = 0.1;
	x_axis = y_axis = z_axis = mode = spin = bg_col = lg_col = 0;
	speed_value = light = 1;
	if (screen != 2){
		obj = TORUS;
		p = 0;
	}
}

void Output (GLfloat x, GLfloat y, char *string) {
	glRasterPos2f (x, y);
	while (*string)
		glutBitmapCharacter (font, *string++);
}

void Welcome () {
	Output (p, q, "Welcome To Move Light.");
	p += 0.1;
	if (p >= 50.0 && q == 47) {
		p = 0.0;
		q = 1;
	}
	else if (p >= 50.0 && q == 1) {
		p = 0.0;
		q = 47;
	}
}

void College_Name () {
	if (v > 47.0) {
		Output (p, 1, "SaIT, Bangalore.");
		p += 0.1;
		if (p >= 50.0)
			p = 0.0;
	}
}

void Developer () {
	Output (p, 1, "Developed By : Nagananda k.k and Sukhen S.Gogi.");
	if (p >= 34.0) pflag = 1;
	else if (p <= 0.0) pflag = 0;
	if (pflag) p -= 0.2;
	else p+= 0.2;
}

void Main_Menu (int item) {
	switch (item) {
	case RESET: if (screen == 2) Reset (); break;
	case QUIT:exit (0);
	}
}

void Objects_Menu (int item) {
	switch (item) {
	case TORUS:		obj = 1; break;
	case TEAPOT:	obj = 2; break;
	case SPHERE:	obj = 3; break;
	case CUBE:		obj = 4; break;
	case DOD:		obj = 5; break;
	case TET:		obj = 6; break;
	case ISO:		obj = 7; break;
	}
}

void Rotate_Menu (int item) {
	switch (item) {
	case X:
		y_axis = z_axis = 0;
		x_axis = 1; break;
	case Y:
		x_axis = z_axis = 0;
		y_axis = 1; break;
	case Z:
		x_axis = y_axis = 0;
		z_axis = 1; break;
	case STOP: 
		x_axis = y_axis = z_axis = 0; break;
	}
}

void Mode_Menu (int item) {
	switch (item) {
	case WIRE:	mode = 1; break;
	case SOLID:	mode = 0; break;
	}
}

void Speed_Menu (int item) {
	switch (item) {
	case IS:
		if (x_axis || y_axis || z_axis)
			if (speed_value != 50.0)
				speed_value += 1.0; 
		break;
	case DS:
		if (x_axis || y_axis || z_axis)
			if (speed_value != 1.0)
				speed_value -= 1.0; 
		break;
	}
}

void Light_Menu (int item) {
	switch (item) {
	case ENABLE:	light = 1; break;
	case DISABLE:	light = 0; break;
	}
}

void Lightcolor_Menu (int item) {
	switch (item) {
	case LC1: lg_col = 0; break;
	case LC2: lg_col = 1; break;
	case LC3: lg_col = 2; break;
	case LC4: lg_col = 3; break;
	case LC5: lg_col = 4; break;
	case LC6: lg_col = 5; break;
	case LC7: lg_col = 6; break;
	}
}

void Camera_Menu (int item) {
	switch (item) {
	case IX:	viewer[0] += 1.0; break;
	case DX:	viewer[0] -= 1.0; break;
	case IY:	viewer[1] += 1.0; break;
	case DY:	viewer[1] -= 1.0; break;
	case IZ:	viewer[2] += 1.0; break;
	case DZ:	viewer[2] -= 1.0; break;
	}
}

void Background_Menu (int item) {
	switch (item) {
	case BG1: bg_col = 0; break;
	case BG2: bg_col = 1; break;
	case BG3: bg_col = 2; break;
	case BG4: bg_col = 3; break;
	case BG5: bg_col = 4; break;
	case BG6: bg_col = 5; break;
	case BG7: bg_col = 6; break;
	case BG8: bg_col = 7; break;
	}
}

void Menustatus (int state) {
	if (state == GLUT_MENU_NOT_IN_USE)
		menu_state = 1;
	else menu_state = 0;
}

void Menu () {
	int obj_menu, rot_menu, mod_menu, lig_menu, cam_menu, spd_menu, brg_menu, ligclr_menu;

	if (screen == 2) {
		ligclr_menu = glutCreateMenu (Lightcolor_Menu);
		glutAddMenuEntry ("1", LC1);
		glutAddMenuEntry ("2", LC2);
		glutAddMenuEntry ("3", LC3);
		glutAddMenuEntry ("4", LC4);
		glutAddMenuEntry ("5", LC5);
		glutAddMenuEntry ("6", LC6);
		glutAddMenuEntry ("7", LC7);

		obj_menu = glutCreateMenu (Objects_Menu);
		glutAddMenuEntry ("Torus", TORUS);
		glutAddMenuEntry ("Teapot", TEAPOT);
		glutAddMenuEntry ("Sphere", SPHERE);
		glutAddMenuEntry ("Cube", CUBE);
		glutAddMenuEntry ("Dodecahedron", DOD);
		glutAddMenuEntry ("Tetrahedron", TET);
		glutAddMenuEntry ("Icosaheddrons", ISO);
	
		spd_menu = glutCreateMenu (Speed_Menu);
		glutAddMenuEntry ("Increase", IS);
		glutAddMenuEntry ("Decrease", DS);
	
		rot_menu = glutCreateMenu (Rotate_Menu);
		glutAddMenuEntry ("Along X-axis", X);
		glutAddMenuEntry ("Along Y-axis", Y);
		glutAddMenuEntry ("Along Z-axis", Z);
		glutAddMenuEntry ("Stop Rotation", STOP);
		glutAddSubMenu ("Rotation Speed", spd_menu);
	
		mod_menu = glutCreateMenu (Mode_Menu);
		glutAddMenuEntry ("Wire", WIRE);
		glutAddMenuEntry ("Solid", SOLID);
	
		lig_menu = glutCreateMenu (Light_Menu);
		glutAddMenuEntry ("Enable", ENABLE);
		glutAddMenuEntry ("Disable", DISABLE);
		glutAddSubMenu ("Light Color", ligclr_menu);
		
		cam_menu = glutCreateMenu (Camera_Menu);
		glutAddMenuEntry ("Increase X", IX);
		glutAddMenuEntry ("Decrease X", DX);
		glutAddMenuEntry ("Increase Y", IY);
		glutAddMenuEntry ("Decrease Y", DY);
		glutAddMenuEntry ("Increase Z", IZ);
		glutAddMenuEntry ("Decrease Z", DZ);
	
		brg_menu = glutCreateMenu (Background_Menu);
		glutAddMenuEntry ("1", BG1);
		glutAddMenuEntry ("2", BG2);
		glutAddMenuEntry ("3", BG3);
		glutAddMenuEntry ("4", BG4);
		glutAddMenuEntry ("5", BG5);
		glutAddMenuEntry ("6", BG6);
		glutAddMenuEntry ("7", BG7);
		glutAddMenuEntry ("8", BG8);
	}

	glutCreateMenu (Main_Menu);
	
	if (screen == 2) {
		glutAddSubMenu ("Objects", obj_menu);
		glutAddSubMenu ("Rotation", rot_menu);
		glutAddSubMenu ("Mode", mod_menu);
		glutAddSubMenu ("Light", lig_menu);
		glutAddSubMenu ("Camera Position", cam_menu);
		glutAddSubMenu ("Background Color", brg_menu);
		glutAddMenuEntry ("Reset", RESET);
	}
	
	glutAddMenuEntry ("Quit", QUIT);
	glutAttachMenu (GLUT_RIGHT_BUTTON);
}

// Idle Function to rotate the object.
void Idle_Rotation () {
	int i;
	if (x_axis)
		rotate[0] += speed_value;
	else if (y_axis)
		rotate[1] += speed_value;
	else if (z_axis)
		rotate[2] += speed_value;
	for (i = 0; i < 3; i++)
		if (rotate[i] >= 360.0) rotate[i] -= 360.0;
	glutPostRedisplay ();
}

void Background_Color () {
	switch (bg_col) {
	case 0:	glClearColor(0.0,0.0,0.0,0.0);	break;
	case 1:	glClearColor(0.0,0.0,1.0,0.0);	break;
	case 2:	glClearColor(0.0,0.5,0.0,0.0);	break;
	case 3:	glClearColor(0.0,0.5,0.5,0.0);	break;
	case 4:	glClearColor(0.5,0.0,0.0,0.0);	break;
	case 5:	glClearColor(1.0,0.0,1.0,0.0);	break;
	case 6:	glClearColor(0.5,0.5,0.0,0.0);	break;
	case 7:	glClearColor(0.5,0.5,0.5,0.0);	break;
	}
}

// To draw table in instructions screen.
void Line (int x0, int y0, int x1, int y1) {
	glBegin (GL_LINE_LOOP);
		glVertex2i (x0,y0);
		glVertex2i (x0,y1);
		glVertex2i (x1,y1);
		glVertex2i (x1,y0);
	glEnd ();
	glFlush ();
}

void Instructions () {
	glClearColor (1.0,1.0,0.9,0.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity ();
	gluOrtho2D (0.0,50,0.0,50);
	glMatrixMode (GL_MODELVIEW);
	
	glDisable (GL_LIGHTING);
	
	glColor3f (0,0,0);
	Line (1, 46, 49, 48);
	Line (1, 44, 49, 46);
	Line (1, 42, 34, 44);
	Line (1, 40, 34, 42);
	Line (1, 38, 34, 40);
	Line (1, 36, 34, 38);
	Line (1, 34, 34, 36);
	Line (1, 32, 34, 34);
	Line (1, 30, 34, 32);
	Line (1, 28, 34, 30);
	Line (1, 26, 34, 28);
	Line (1, 24, 34, 26);
	Line (1, 22, 34, 24);
	Line (1, 20, 34, 22);
	Line (1, 18, 34, 20);
	Line (1, 16, 34, 18);
	Line (1, 14, 34, 16);
	Line (1, 12, 34, 14);
	Line (1, 10, 34, 12);
	Line (1, 8, 34, 10);
	Line (1, 6, 34, 8);
	Line (1, 4, 34, 6);
	Line (14, 4, 14, 44);
	Line (34, 4, 34, 46);
	Line (34, 30, 49, 46);
	glColor3f (1, 0, 0);
	font = GLUT_BITMAP_HELVETICA_18;
	Output (21, 46.5, "****INSTRUCTIONS****");
	Output (12, 44.5, "KEYBOARD");
	Output (39, 44.5, "MOUSE");
	Output (4, 42.5, "BUTTON");
	Output (16, 42.5, "ACTION");
	glColor3f (0.5, 0.0, 1.0);
	Output (35, 42.5, "1. Press the RIGHT");
	Output (35, 40.5, "mouse button for menu.");
	Output (35, 36.5, "2. Hold down the LEFT");
	Output (35, 34.5, "mouse button and move");
	Output (35, 32.5, "the mouse horizantaly");
	Output (35, 30.5, "to change the light position.");
	Output (5, 40.5, "1");
	Output (5, 38.5, "2");
	Output (5, 36.5, "3");
	Output (5, 34.5, "4");
	Output (5, 32.5, "5");
	Output (5, 30.5, "6");
	Output (5, 28.5, "7");
	Output (5, 26.5, "r");
	Output (4.5, 24.5, "ESC");
	Output (3, 22.5, "UP ARROW");
	Output (3, 20.5, "DOWN ARROW");
	Output (3, 18.5, "LEFT ARROW");
	Output (5, 16.5, "w");
	Output (5, 14.5, "l");
	Output (3, 12.5, "'X','x','Y','y','Z','z'");
	Output (5, 10.5, "F1");
	Output (5, 8.5, "F2");
	Output (5, 6.5, "F3");
	Output (5, 4.5, "c");
	Output (14.5, 40.5, "Display Torus");
	Output (14.5, 38.5, "Display Teapot");
	Output (14.5, 36.5, "Display Sphere");
	Output (14.5, 34.5, "Display Cube");
	Output (14.5, 32.5, "Display Dodecahedron");
	Output (14.5, 30.5, "Display Tetrahedron");
	Output (14.5, 28.5, "Display Icosahedrons");
	Output (14.5, 26.5, "Reset");
	Output (14.5, 24.5, "Exit Window");
	Output (14.5, 22.5, "Rotate the object along Y-axis");
	Output (14.5, 20.5, "Rotate the object along Z-axis");
	Output (14.5, 18.5, "Rotate the object along X-axis");
	Output (14.5, 16.5, "Toggle between Wired and Solid mode");
	Output (14.5, 14.5, "Toggle between Enable and Disable Light");
	Output (14.5, 12.5, "To change the Camera position");
	Output (14.5, 10.5, "To Increase Rotation Speed");
	Output (14.5, 8.5, "To Decrease Rotation Speed");
	Output (14.5, 6.5, "To change Light color");
	Output (14.5, 4.5, "To change Background Color");
	glColor3f (0.5, 0.0, 1.0);
	Output (37, 6.5, "Press 'b' to go back");
	Output (37, 4.5, "Press ENTER Key To Continue....");
	Developer ();
}

void Display () {
	if (!screen) {
		glClearColor (0.3, 0.0, 0.3, 0.0);
		glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluOrtho2D (0.0, 50.0, 0.0, 50.0);
		glMatrixMode (GL_MODELVIEW);
		
		glDisable (GL_LIGHTING);
		
		glColor3f (1, 1, 1);
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		Output (13.3, v, "VISVESHVARAYA TECHNOLOGICAL UNIVERSITY");
		
		font = GLUT_BITMAP_HELVETICA_18;
		Output (19, v-2, "Belgaum, Karnataka - 590 014");
		Output (19.8, v-6, "A  MINI  PROJECT  ON");
		
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		Output (20.2, v-8, "\"MOVE  LIGHT\"");
		
		font = GLUT_BITMAP_HELVETICA_18;
		Output (20.8, v-11, "SUBMITTED BY:");
		Output (15, v-14, "NAGANANDA K.K");
		Output (15.2, v-16, "(1ST09CS061)");
		Output (26.5, v-14, "SUKHEN S.GOGI");
		Output (26.7, v-16, "(1ST08CS123)");
		Output (19, v-19, "UNDER THE GUIDANCE OF:");
		Output (15, v-22, "Mrs. VANI .B");
		Output (27, v-22,"Mr. IDDALGAVE SANDEEP");
		Output (13.5, v-24,"Asst.Prof, Dept of CSE");
		Output (27.7, v-24,"Lecturer, Dept of CSE");
		Output (14.8, v-26, "SaIT, Bangalore.");
		Output (28.8, v-26, "SaIT, Bangalore.");
		
		font = GLUT_BITMAP_TIMES_ROMAN_24;
		Output (14, v-35, "Department Of Computer Science And Engineering");
		Output (17, v-37, "Sambhram Institute Of Technology");
		Output (20, v-39, "Bangalore - 560 097.");
		Output (35, v-43, "Press ENTER Key To Continue....");

		if (v < 47.0)
			v += 0.2;
		
		College_Name ();
		glutSwapBuffers ();
	}
	else if (screen == 1)	{
		Instructions();
		glutSwapBuffers ();
	}
	else if (screen == 2) {
		GLfloat position[] = {0.0, 0.0, 1.5, 1.0};
		GLfloat diffuse[][3] = {{1,1,1}, {0,1,0}, {0,1,1}, {1,0,0}, {1,0,1}, {1,1,0}, {0,0,1},};
		char camera[100], angle[100], rot_speed[25];
		
		Background_Color ();
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		glMatrixMode (GL_PROJECTION);
		glLoadIdentity ();
		gluPerspective (40.0, (GLfloat) width / (GLfloat) height, 1.0, 20.0);
		glMatrixMode (GL_MODELVIEW);
		
		glPushMatrix ();
			glTranslated (0.0, 0.0, -5.0);
			glPushMatrix ();
				gluLookAt (viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
				glRotated ((GLdouble) spin, 0.0, 1.0, 0.0);
							
				glLightfv (GL_LIGHT0, GL_POSITION, position);
				glLightfv (GL_LIGHT0, GL_DIFFUSE,  diffuse[lg_col]);

				glTranslated (0.0, 0.0, 1.5);
				
				glDisable (GL_LIGHTING);
				
				glColor3f (0, 1, 1);
				glutWireCube (0.1);
			glPopMatrix ();
			gluLookAt (viewer[0], viewer[1], viewer[2], 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
			glRotatef (rotate[0], 1.0, 0.0, 0.0);
			glRotatef (rotate[1], 0.0, 1.0, 0.0);
			glRotatef (rotate[2], 0.0, 0.0, 1.0);
			
			if (light)
				glEnable (GL_LIGHTING);
			
			glColor3f (0.2, 0.2, 0.2);
			switch (obj) {
			case TORUS:
				(!mode) ? glutSolidTorus (0.275, 0.85, 20, 20) : glutWireTorus (0.275,0.85,20,20);
				break;
			case TEAPOT:
				(!mode) ? glutSolidTeapot (0.8) : glutWireTeapot (0.8);
				break;
			case SPHERE:
				(!mode) ? glutSolidSphere (1.0, 200, 200) : glutWireSphere (1.0, 20, 20);
				break;
			case CUBE:
				(!mode) ? glutSolidCube (1.0) : glutWireCube (1.0);
				break;
			case DOD:
				glPushMatrix ();
					glScalef (0.5, 0.5, 0.5);
					(!mode) ? glutSolidDodecahedron () : glutWireDodecahedron ();
				glPopMatrix ();
				break;
			case TET:
				(!mode) ? glutSolidTetrahedron () : glutWireTetrahedron ();
				break;
			case ISO:
				(!mode) ? glutSolidIcosahedron () : glutWireIcosahedron (); 
				break;
			}
		glPopMatrix ();
		
		glPushAttrib (GL_ENABLE_BIT);
			glDisable (GL_DEPTH_TEST);
			glDisable (GL_LIGHTING);
			
			glMatrixMode (GL_PROJECTION);
			glPushMatrix ();
				glLoadIdentity ();
				gluOrtho2D (0.0, 50.0, 0.0, 50.0);
				
				glColor3f (0, 1, 1);
				font = GLUT_BITMAP_HELVETICA_18;
				Output (2, 44, "Press 'i' for instructions");
				Output (2, 42, "Press 'b' to go back");
				Output (2, 40, "Press ESC to exit");
				if (obj == TORUS) Output (34,44, "Object : Torus");
				else if (obj == TEAPOT) Output (34, 44, "Object : Teapot");
				else if (obj == SPHERE) Output (34, 44, "Object : Sphere");
				else if (obj == CUBE) Output (34, 44, "Object : Cube");
				else if (obj == DOD) Output (34, 44, "Object : Dodecahedron");
				else if (obj == TET) Output (34, 44, "Object : Tetrahedron");
				else if (obj == ISO) Output (34, 44, "Object : Icosahedron");
				(mode) ? (Output (34, 42, "Mode  :  Wire")) : (Output (34, 42, "Mode  :  Solid"));
				(light) ? (Output (34, 40, "Light   : Enabled")) : (Output (34, 40, "Light   :  Disabled"));
				sprintf (camera, "X = %.1f, Y = %.1f, Z = %.1f", viewer[0], viewer[1],  viewer[2]);
				sprintf (angle, "X = %.1f, Y = %.1f, Z = %.1f", rotate[0], rotate[1], rotate[2]);
				sprintf (rot_speed, "%s%.1f", "Rotation Speed : ", speed_value);
				Output (34, 38, "Camera Position :");
				Output (34, 36, camera);
				if (x_axis) Output (2, 14, "Rotating along X-axis : ");
				else if (y_axis) Output (2, 14, "Rotating along Y-axis : ");
				else if (z_axis) Output (2, 14, "Rotating along Z-axis : ");
				
				if (x_axis || y_axis || z_axis) {
					Output (2, 12, angle);
					Output (2, 10, rot_speed);
					glColor3f (1, 0, 0);
					Line (1, 9, 16, 16);
				}	
				glColor3f (1, 0, 0);
				Line (1, 39, 13, 46);
				Line (33, 35, 49, 46);
				
				font = GLUT_BITMAP_TIMES_ROMAN_24;
				glColor3f (0, 1, 1);
				Welcome ();
				
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
					glLoadIdentity();
				glPopMatrix();

				glMatrixMode(GL_PROJECTION);
			glPopMatrix();
		glPopAttrib();
		glutSwapBuffers();
	}
}

void Keyboard (unsigned char key, int x, int y) {
	switch (key) {
	case '\r':
		if (!screen && v > 47.0){
			screen = 1;
			Reset ();
			if (menu_state)
				Menu ();
		}
		else if (screen == 1) {
			screen = 2;
			Reset ();
			if (menu_state)
				Menu ();
		}
		break;
	case '1': obj = 1;	break;
	case '2': obj = 2;	break;
	case '3': obj = 3;  break;
	case '4': obj = 4;	break;
	case '5': obj = 5;	break;
	case '6': obj = 6;	break;
	case '7': obj = 7;	break;
	case 'r': if (screen == 2) Reset(); break;
	case 27:  if (v >= 47.0) exit (0);
	case 'b': 
		screen = 0; 	
		if (menu_state)
			Menu ();
		break;
	case 'c': bg_col++; bg_col %= 8; break;
	case 'w': mode = !mode;	break;
	case 'i':
		if (screen == 2) {
			screen = 1;
			Reset ();
			if (menu_state)
				Menu ();
		}
		break;
	case 's': x_axis = y_axis = z_axis = 0;	break;
	case 'l': light = !light;	break;
	case 'X': viewer[0] += 1.0; break;
	case 'Y': viewer[1] += 1.0; break;
	case 'Z': viewer[2] += 1.0; break;
	case 'x': viewer[0] -= 1.0; break;
	case 'y': viewer[1] -= 1.0; break;
	case 'z': viewer[2] -= 1.0; break;
	}
}

void Special (int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_LEFT:
		y_axis = z_axis = 0;
		x_axis = 1;
		break;
	case GLUT_KEY_UP:
		x_axis = z_axis = 0;
		y_axis = 1;
		break;
	case GLUT_KEY_DOWN:
		x_axis = y_axis = 0;
		z_axis = 1;
		break;
	case GLUT_KEY_F1:
		if (x_axis || y_axis || z_axis)
			if (speed_value != 50.0)
				speed_value += 1.0; 
		break;
	case GLUT_KEY_F2:
		if (x_axis || y_axis || z_axis)
			if (speed_value != 1.0)
				speed_value -= 1.0; 
		break;
	case GLUT_KEY_F3:
		if (light) {
			lg_col ++;
			lg_col %= 7;
		}
		break;
	}
}

int main (int argc, char ** argv) {
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
		
	glutCreateWindow ("MOVE LIGHT");
	glutFullScreen ();
	
	glutKeyboardFunc (Keyboard);
	glutMouseFunc (Movelight);
	glutMotionFunc (Motion);
	glutReshapeFunc (MyReshape);
	glutDisplayFunc (Display);
	glutSpecialFunc (Special);
	glutIdleFunc (Idle_Rotation);
	glutMenuStateFunc (Menustatus);
	
	Myinit ();
	Menu ();
	
	glutMainLoop ();
}