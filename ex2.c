#include <GL/glut.h>
#include <GL/gl.h>
#include<GL/freeglut.h>

// �ngulo de rota��o do bule
GLfloat rotationAngle = 0.0f;
GLfloat fAspect;
GLfloat aux;

GLfloat angle1 = 45.0f ,  angle2 = 45.0f,angle3 = 45.0f,angle4 = 45.0f;

void init()
{
   GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0}; 
	GLfloat luzDifusa[4]={1.0,1.0,1.0,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0};// "brilho" 
	GLfloat posicaoLuz[4]={20.0, 60.0, 100.0, 1.0};
	
	// Capacidade de brilho do material
	GLfloat especularidade[4]={1.0,1.0,1.0,1.0}; 
	GLint especMaterial = 60;

 	// Especifica que a cor de fundo da janela ser� preta
	glClearColor(0.60f, 0.60f, 0.60f, 1.0f);
	
	// Habilita o modelo de coloriza��o de Gouraud
	glShadeModel(GL_SMOOTH);

	// Define a reflet�ncia do material 
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	// Define a concentra��o do brilho
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	// Ativa o uso da luz ambiente 
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	// Define os par�metros da luz de n�mero 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente); 
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

	// Habilita a defini��o da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de ilumina��o
	glEnable(GL_LIGHTING);  
	// Habilita a luz de n�mero 0
	glEnable(GL_LIGHT0);

	// remo��o de faces ocultas 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();
}

void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if ( h == 0 ) h = 1;

	// Especifica o tamanho da viewport
	glViewport(0, 0, w, h);
 
	// Calcula a corre��o de aspecto
	fAspect = (GLfloat)w/(GLfloat)h;
	init();

}

void drawBule()
{	
	init();
	glPushMatrix(); 
	glColor3f(0.0f, 0.0f, 1.0f);
	glDisable(GL_CULL_FACE); // Desabilita a remo��o de faces temporariamente
	glTranslatef(0.0f, 0.0f, 0.0f);
	glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
    glutSolidTeapot(50.0f);
    glPopMatrix();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    // Viewport XY
    glViewport(0, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();
    // Especifica a proje��o perspectiva
	gluPerspective(angle1,fAspect,0.4,500);
    gluLookAt(0, 0, 300, 0, 0, 0, 0, 1, 0);
    drawBule();

    // Viewport YZ
    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();
    gluPerspective(angle2,fAspect,0.4,500);
    gluLookAt(250, 0, 0, 0, 0, 0, 0, 1, 0);
    drawBule();

    // Viewport XZ
    glViewport(0, 0, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);	
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();
    gluPerspective(angle3,fAspect,0.4,500);
    gluLookAt(0, 250, 0, 0, 0, 0, -1, 0, 0);
    drawBule();

    // Viewport perspectiva
    glViewport(glutGet(GLUT_WINDOW_WIDTH) / 2, 0, glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);  
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(angle4,fAspect,0.4,500);
    gluLookAt(200, 200, 200, 0, 0, 0, 0, 1, 0);
    drawBule();
    

    glutSwapBuffers();
}

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0 ) { // scroll para cima
        aux = 1.0f;
    }
    else if (dir < 0) { // scroll para baixo
        aux = -1.0f;
    }
    
    if (x > 0 && x < (glutGet(GLUT_WINDOW_WIDTH) / 2) &&
		y > ( glutGet(GLUT_WINDOW_WIDTH) / 2) && y < ( glutGet(GLUT_WINDOW_WIDTH))
	){
		angle3 += aux;
	}
	
	else if (x >  (glutGet(GLUT_WINDOW_WIDTH)/ 2) && x < (glutGet(GLUT_WINDOW_WIDTH)) &&
		y > ( glutGet(GLUT_WINDOW_WIDTH) / 2) && y < ( glutGet(GLUT_WINDOW_WIDTH))
	){
		angle4 += aux;
	}
	
	else if (x > 0 && x < (glutGet(GLUT_WINDOW_WIDTH) / 2) &&
		y > 0 && y < ( glutGet(GLUT_WINDOW_WIDTH)/2)
	){
		angle1 += aux;
	}
	
	else if (x >  (glutGet(GLUT_WINDOW_WIDTH)/ 2) && x < (glutGet(GLUT_WINDOW_WIDTH)) &&
		y > 0 && y < ( glutGet(GLUT_WINDOW_WIDTH)/2)
	){
		angle2 += aux;
	}
    
    
    
    
    glutPostRedisplay(); // Solicita um redesenho da cena
}



void update(int value)
{
    rotationAngle += 1.0f; // Incrementa o �ngulo de rota��o
    if (rotationAngle > 360){
    	rotationAngle = 0;
	}

    glutPostRedisplay(); // Solicita um redesenho da cena
    // Configura a fun��o update() para ser chamada novamente ap�s 16 milissegundos 
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Viewport Scene");
    
    init();
    
    glutDisplayFunc(display);
    glutReshapeFunc(AlteraTamanhoJanela);
    glutMouseWheelFunc(mouseWheel);
    glutTimerFunc(0, update, 0);
    
    glutMainLoop();
    
    return 0;
}

