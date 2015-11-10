/********************************************************/
/*                     cube.cpp                                                 */
/********************************************************/
/*                Affiche a l'ecran un cube en 3D                      */
/********************************************************/

/* inclusion des fichiers d'en-tete freeglut */

#ifdef __APPLE__
#include <GLUT/glut.h> /* Pour Mac OS X */
#else
#include <GL/glut.h>   /* Pour les autres systemes */
#endif 
#include <cstdlib>
#include <math.h>


/*class Point*/
class Point{
    public :
	//coordonnées x, y et z du point
	double x;
	double y;
	double z;
	// couleur r, v et b du point
	float r;
	float g;
	float b;
};
  
//N étant le nb de faces
const int n = 20;
double PI = 3.141592;
char presse;
int anglex,angley,x,y,xold,yold;
Point pCylindre[n * 2];
Point sommetCylindre[n * 2][3];
/* Prototype des fonctions */
void afficheCylindre();
void affichage();
void clavier(unsigned char touche,int x,int y);
void reshape(int x,int y);
void idle();
void mouse(int bouton,int etat,int x,int y);
void mousemotion(int x,int y);
void Tete();
void Corps();
void BrasG();
void BrasD();
void pointCylindre(float r, float h);
int main(int argc,char **argv)
{

	
  /* initialisation de glut et creation
     de la fenetre */
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(200,200);
  glutInitWindowSize(500,500);
  glutCreateWindow("cube");

  /* Initialisation d'OpenGL */
  glClearColor(0.0,0.0,0.0,0.0);
  glColor3f(1.0,1.0,1.0);
  glPointSize(2.0);
  glEnable(GL_DEPTH_TEST);

  /* enregistrement des fonctions de rappel */
  glutDisplayFunc(affichage);
  glutKeyboardFunc(clavier);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutMotionFunc(mousemotion);

  /* Entree dans la boucle principale glut */
  glutMainLoop();
  return 0;
}


void affichage()
{
  int i,j;
  /* effacement de l'image avec la couleur de fond */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
glShadeModel(GL_SMOOTH);
  
  glLoadIdentity();

  glRotatef(angley,1.0,0.0,0.0);
  glRotatef(anglex,0.0,1.0,0.0);
  Tete();
  Corps();
  BrasG();
  BrasD();
    
    //Repère
    //axe x en rouge
    glBegin(GL_LINES);
        glColor3f(1.0,0.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(1, 0,0.0);
    glEnd();
    //axe des y en vert
    glBegin(GL_LINES);
    	glColor3f(0.0,1.0,0.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 1,0.0);
    glEnd();
    //axe des z en bleu
    glBegin(GL_LINES);
    	glColor3f(0.0,0.0,1.0);
    	glVertex3f(0, 0,0.0);
    	glVertex3f(0, 0,1.0);
    glEnd();

  glFlush();
  
  //On echange les buffers 
  glutSwapBuffers();
}

void clavier(unsigned char touche,int x,int y)
{
  switch (touche)
    {
    case 'p': /* affichage du carre plein */
      glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
      glutPostRedisplay();
      break;
    case 'f': /* affichage en mode fil de fer */
      glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
      glutPostRedisplay();
      break;
    case 's' : /* Affichage en mode sommets seuls */
      glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
      glutPostRedisplay();
      break;
    case 'd':
      glEnable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'D':
      glDisable(GL_DEPTH_TEST);
      glutPostRedisplay();
      break;
    case 'q' : /*la touche 'q' permet de quitter le programme */
      exit(0);
    }
}

void reshape(int x,int y)
{
  if (x<y)
    glViewport(0,(y-x)/2,x,x);
  else 
    glViewport((x-y)/2,0,y,y);
}
//Dessin Tête Mog
void Tete()
{
	glPushMatrix();
	glTranslatef(0, 0.9, 0);
	glScalef(0.1, 0.1, 0.1);
	glColor3f(1, 1, 1);
	glutSolidSphere(1.5, 50, 50);
	glPopMatrix();
}
//Dessin corps Mog
void Corps()
{
	glPushMatrix();
	glTranslatef(0, 0.5, 0);
	glScalef(0.2, .3, .2);
	glColor3f(1, 0, 0);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}
//Dessin Bras Gauche
void BrasG()
{
	glPushMatrix();
	glTranslatef(0.2, 0.6, 0);
	glRotatef(45, 0, 0, 1);
	glColor3f(1, 1, 1);
	glScalef(0.075, 0.15, 0.075);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}
//Dessin Bras Droit
void BrasD()
{
	glPushMatrix();
	glTranslatef(-0.2, 0.6, 0);
	glRotatef(-45, 0, 0, 1);
	glColor3f(1, 1, 1);
	glScalef(0.075, 0.15, 0.075);
	glutSolidSphere(1, 50, 50);
	glPopMatrix();
}

/* Affichage du cylindre facettisé */
/*void afficheCylindre()
{
	for (int i = 0; i < n; i++)
	{

		glBegin(GL_POLYGON);
		for (int j = 0; j < 3; j++)
		{
			glColor3f(1, 1, 1);
			glVertex3f(sommetCylindre[i][j].x, sommetCylindre[i][j].y, sommetCylindre[i][j].z);
		}
		glEnd();


		glBegin(GL_POLYGON);
		glTexCoord2f((double)(i + 1) * (1 / (double)n), 1);
		for (int j = 0; j < 3; j++)
		{
			glVertex3f(sommetCylindre[i + n][j].x, sommetCylindre[i + n][j].y, sommetCylindre[i + n][j].z);
		}

		glEnd();



		glBegin(GL_POLYGON);
		glTexCoord2f((double)i*(1 / (double)n), 1);
		glVertex3f(pCylindre[i].x, pCylindre[i].y, pCylindre[i].z);

		glTexCoord2f((double)(i + 1) * (1 / (double)n), 1);
		glVertex3f(pCylindre[(i + 1) % n].x, pCylindre[(i + 1) % n].y, pCylindre[(i + 1) % n].z);

		glTexCoord2f((double)(i + 1) * (1 / (double)n), 0);
		glVertex3f(pCylindre[((i + 1) % n) + n].x, pCylindre[((i + 1) % n) + n].y, pCylindre[((i + 1) % n) + n].z);

		glTexCoord2f((double)i*(1 / (double)n), 0);
		glVertex3f(pCylindre[i + n].x, pCylindre[i + n].y, pCylindre[i + n].z);
		glEnd();
	}
}*/
void pointCylindre(float r, float h)
{
	for (int i = 0; i < n; i++)
	{
		pCylindre[i] = { r*cos((i * 2 * PI) / n), r*sin((i * 2 * PI) / n), h / 2 };
		pCylindre[i + n] = { r*cos((i * 2 * PI) / n), r*sin((i * 2 * PI) / n), -(h / 2) };
	}
	for (int i = 0; i < n; i++)
	{
		sommetCylindre[i][0] = pCylindre[i];
		sommetCylindre[i + n][0] = pCylindre[i + n];
		sommetCylindre[i][1] = pCylindre[(i + 1) % n];
		sommetCylindre[i + n][1] = pCylindre[((i + 1) % n) + n];
		sommetCylindre[i][2] = { 0, 0, h / 2 };
		sommetCylindre[i + n][2] = { 0, 0, -(h / 2) };
	}
}
void mouse(int button, int state,int x,int y)
{
  /* si on appuie sur le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) 
  {
    presse = 1; /* le booleen presse passe a 1 (vrai) */
    xold = x; /* on sauvegarde la position de la souris */
    yold=y;
  }
  /* si on relache le bouton gauche */
  if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) 
    presse=0; /* le booleen presse passe a 0 (faux) */
}

void mousemotion(int x,int y)
  {
    if (presse) /* si le bouton gauche est presse */
    {
      /* on modifie les angles de rotation de l'objet
	 en fonction de la position actuelle de la souris et de la derniere
	 position sauvegardee */
      anglex=anglex+(x-xold); 
      angley=angley+(y-yold);
      glutPostRedisplay(); /* on demande un rafraichissement de l'affichage */
    }
    
    xold=x; /* sauvegarde des valeurs courante de le position de la souris */
    yold=y;
  }

