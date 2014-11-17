// gcc test.c -o test -lGL -lGLU -lglut -L/usr/X11R6/lib -lXi -lXmu -lm

#include <stdio.h>
#include <math.h>
#include <time.h>
#include <GL/glut.h>

typedef struct bubble{
	double x, y, z,
	       vx, vy, vz,
		   fx, fy, fz;
	int lifetime;
	struct bubble* next;
} bubble;

// global
GLboolean anim = 0;
GLint     width = 800, height = 800, e_time, timeN = 0, info=0, 
  iterations = 500, quality = 100;
GLfloat  d = 40, v_angle_x = 0, v_angle_y = 180, anim_t = 0, anim_t_step = 0.4,
  w0 = 0.2, eps = 0.01, filling = 0,
  foam0 = 0, foam1 = 0, foam2 = 0,
  c_glass[] = {0.498, 0.78, 1, 0.1}, one[] = {0.8, 0.8,  0.8, 1},  zero[] = {0, 0, 0, 1},
  red[] = {1, 0, 0, 1}, green[] = {0, 1, 0, 1},  blue[] = {0, 0, 1, 1},
  c_beer[] = {1, 0.843, 0, 0.3},
  la0[] = {1, 1, 1, 1}, ld0[] = {1, 0.5, 1, 0};
  
GLUquadric* q;

GLdouble
  x1 = 2, x2 = 3, y2 = 12, x3 = 4;

bubble* bubble_head = NULL;

// interface
void add_bubble();
void check_bubbles();
void remove_bubble(bubble* prev);

GLdouble radius(GLdouble x) {
	return (sqrt(4*(-3.33333333333333)*x-4*(-3.33333333333333)*(-40.0)+(26.6666666666667*26.6666666666667))-(26.6666666666667))/(2*(-3.33333333333333));
}

void surface(){
//	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, tree1);
    glDepthMask(GL_FALSE);
	GLint i, b_face=1;
	GLdouble dx = y2/(GLdouble)iterations,
	  r1, r2, h=-dx,
	  u = filling;
	r1 = radius(0);
//	r2 = radius(w0);
//	printf("------- dx = %lf---------\n", dx);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c_glass);
//	glMaterialfv(GL_FRONT, GL_DIFFUSE, c_glass);
	glMaterialfv(GL_FRONT, GL_SPECULAR, one);
	glMaterialf(GL_FRONT, GL_SHININESS, 40.0);
    gluDisk(q, 0, x1+w0, quality/2, quality/2);
    gluCylinder(q, r1+w0, r1+w0, w0, quality, 1);
    glTranslatef(0, 0, w0);
    gluDisk(q, 0, r1, quality/2, quality/2);
    
    glTranslatef(0, 0, eps);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c_beer);
    gluDisk(q, 0, r1-eps, quality/2, quality/2);
    glTranslatef(0, 0, -eps);
    
    
	for(i=0;i<iterations-2;i++){
		h+=dx;
		r2 = radius(h);
		// inner board
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c_glass);
		gluCylinder(q, r1, r2, dx, quality, 1);
		// outter board
		gluCylinder(q, r1+w0, r2+w0, dx, quality, 1);
		// beer
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c_beer);
		if(h<u) gluCylinder(q, r1-eps, r2-eps, dx, quality, 1);
		if(h>=u && b_face){
			gluDisk(q, 0, r2-eps, quality/2, quality/2);
			b_face = 0;
		}
		// ...
		glTranslatef(0, 0, dx);
		r1 = r2;
	//	printf("------- r1,2 = %lf, %lf, h = %lf---------\n", r1, r2, h);
	}
	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, c_glass);
	gluDisk(q, r2, r2+w0, 500, 500);
	glDepthMask(GL_TRUE);
}

void Display(void){
  glClearColor(0, 0, 0, 1);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  
  glColor3f(1,0,0);
  glMaterialfv(GL_FRONT, GL_DIFFUSE, zero);
  glMaterialfv(GL_FRONT, GL_EMISSION, red);
  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(10,0,0);
  glEnd();
  glColor3f(0,1,0);
  glMaterialfv(GL_FRONT, GL_EMISSION, green);
  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,10,0);
  glEnd();
  glColor3f(0,0,1);
  glMaterialfv(GL_FRONT, GL_EMISSION, blue);
  glBegin(GL_LINES);
    glVertex3f(0,0,0);
    glVertex3f(0,0,10);
  glEnd();
  glMaterialfv(GL_FRONT, GL_EMISSION, zero);
  glColor4f(1,1,0,0.3);
  
  glRotatef(-90, 1,0,0);
  
 /* gluCylinder(q, 1, 2, 3, 50, 50);

  glTranslatef(0,0,3);
  gluCylinder(q, 2, 1, 3, 50, 50);*/
  
  surface();

  glFinish();
  glutSwapBuffers();
}

void Reshape(int w, int h)
{
  width = w;
  height = h;

  glViewport(0, 0, w, h);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(75, (GLfloat)w/h, 1, 500);

    glTranslatef(0, 0, -d); 
    glRotatef(v_angle_x, 1, 0, 0);
    glRotatef(-180, 0, 1, 0);
    glRotatef(v_angle_y, 0, 1, 0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y){
  switch (key)
  {
    case '\033':
      exit(0);
      break;
    case 'e':
      printf("v_angle_y = %f\nv_angle_x = %f\n", v_angle_y, v_angle_x);
      break;
    case 'i':
      info = 1;
      break;
    case 'a':
      v_angle_y -= 5;
      if (v_angle_y<0) v_angle_y += 360;
      Reshape(width, height);
      break;
    case 'r':
      d -= 4;
      if (d<10) d += 4;
      Reshape(width, height);
      break;
    case 'f':
      d += 4;
      if (d>60) d -= 4;
      Reshape(width, height);
      break;
    case 'd':
      v_angle_y += 5;
      if (v_angle_y>360) v_angle_y -= 360;
      Reshape(width, height);
      break;
    case 'w':
      v_angle_x -= 5;
      if (v_angle_x<0) v_angle_x += 360;
      Reshape(width, height);
      break;
    case 's':
      v_angle_x += 5;
      if (v_angle_x>360) v_angle_x -= 360;
      Reshape(width, height);
      break;
    case ' ':
      if (!anim) anim_t_step = 1.5;
      anim ^= 1;
    //  anim =^_^= 1;
      break;
    case '+':
      anim_t_step += 0.05;
      break;
    case '-':
      anim_t_step -= anim_t_step > 0.1 ? 0.05 : 0;
      break;
	case 'u':
      filling-=5;
      break;
  }
}

void add_bubble(double x0, double y0, double z0){
	bubble* bub = malloc(sizeof(bubble));
	bub->x = x0;
	bub->y = y0;
	bub->z = z0;
	bub->vx = 0;
	bub->vy = 0;
	bub->vz = 0;
	bub->fx = 0;
	bub->fy = 0;
	bub->fz = 0;
	
	bub->lifetime = 10000;
	bub->next = bubble_head;
	
	bubble_head = bub;
}

void remove_bubble(bubble* prev){
	bubble* this;
	if(prev == NULL){
		this = bubble_head;
		bubble_head = bubble_head->next;
	}
	else {
		this = prev->next;
		prev->next = this->next;
	}
	free(this);
}

void check_bub(bubble* bub) {
	bubble *curr;
	for(curr = bubble_head; curr!=NULL; curr = curr->next){
		if (bub == curr) continue;
		
		// PHYX
		
		
	}
}

void check_bubbles(){
	bubble *curr, *prev=NULL;
	for(curr = bubble_head; curr!=NULL; curr = curr->next){
		curr->lifetime--;
		if(curr->lifetime<=0) {
			remove_bubble(prev);
			curr = prev;
			continue;
		}
		
		check_bub(curr);
		
		curr->x += curr->vx;
		curr->y += curr->vy;
		curr->z += curr->vz;
		curr->vx += curr->fx;
		curr->vy += curr->fy;
		curr->vz += curr->fz;
		
		prev = curr;
	}
}

/*
typedef struct bubble{
	double x, y, z,
	       vx, vy, vz,
		   fx, fy, fz;
	int lifetime;
	struct bubble* next;
} bubble; */



void tick() {
	if (anim) {
		// PROFIT
		filling+=0.1;
		if(filling>(y2-2)) filling = y2 - 2;
	}
	glutPostRedisplay();
	glutTimerFunc(40, tick, 0);
}

void first() {
	tick();
	glutIdleFunc(NULL);
}

int main(int argc, char *argv[]){
  /*
  GLdouble
    a = -y2/(2*x2*x3-2*x1*x3-x2*x2+x1*x1),
    b = (2*x3*y2)/(2*x2*x3-2*x1*x3-x2*x2+x1*x1),
    c = (x1*x1*y2-2*x1*x3*y2)/(2*x2*x3-2*x1*x3-x2*x2+x1*x1),
    dx = 1/(GLdouble)iterations/y2;
  */
  
  if(argc>1 && atoi(*(argv+1))) iterations = atoi(*(argv+1));
  if(argc>2 && atoi(*(argv+2))) quality    = atoi(*(argv+2));
  
    
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
  glutInitWindowSize(width, height);
  glutCreateWindow("Beer");
  q = gluNewQuadric();

  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_ALPHA_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
/*  glEnable(GL_LIGHT1);
  glEnable(GL_LIGHT2);
*/
  glLightfv(GL_LIGHT0, GL_DIFFUSE, la0);
  glLightfv(GL_LIGHT0, GL_POSITION, ld0);
  glLightfv(GL_LIGHT0, GL_SPECULAR, la0);
  
  add_bubble(1,0,1);
  add_bubble(-1,0,1);
  add_bubble(1,0,-1);
  add_bubble(-1,0,-1);
  
  check_bubbles();
  bubble* curr;
  for(curr = bubble_head; curr!=NULL; curr = curr->next) printf("%lf %lf %lf\n", curr->x, curr->y, curr->z);
  remove_bubble(bubble_head->next);
  printf("\n");
  for(curr = bubble_head; curr!=NULL; curr = curr->next) printf("%lf %lf %lf\n", curr->x, curr->y, curr->z);
  
  
  
  


  glutDisplayFunc(Display);
  glutReshapeFunc(Reshape);
  glutKeyboardFunc(Keyboard);
  glutIdleFunc(first);

  glutMainLoop();

  return 0;
}
