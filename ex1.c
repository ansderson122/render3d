#include<GL/freeglut.h>
#include <GL/glut.h>

GLfloat angle=45, fAspect;
void cenario();
void objetos(void);
void display(void)
{
	// Limpa a janela e o depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);

	cenario();
	objetos();
	glutSwapBuffers();
}

void cenario(){
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.0f);  // Posiciona o ret�ngulo no espa�o 3D
    glScalef(100.0f, 5.0f, 100.0f);  // Escala o ret�ngulo nos eixos x, y, z
    glutSolidCube(1.0f);  // Cria um cubo s�lido com tamanho 1.0
    glPopMatrix();
    
    glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(-48.0f, 25.0f, 0.0f);  // Posiciona o ret�ngulo no espa�o 3D
    glScalef(5.0f, 50.0f, 100.0f);  // Escala o ret�ngulo nos eixos x, y, z
    glutSolidCube(1.0f);  // Cria um cubo s�lido com tamanho 1.0
    glPopMatrix();
    
    glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 25.0f, -48.0f);  // Posiciona o ret�ngulo no espa�o 3D
    glScalef(100.0f, 50.0f, 5.0f);  // Escala o ret�ngulo nos eixos x, y, z
    glutSolidCube(1.0f);  // Cria um cubo s�lido com tamanho 1.0
    glPopMatrix();
}

void objetos(void){
	glPushMatrix(); // bule
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(-20.0f, 15.0f, 20.0f);
	glRotatef(45.0f, 0.0f, 1.0f, 0.0f);
	glDisable(GL_CULL_FACE); // Desabilita a remo��o de faces temporariamente
	glutSolidTeapot(15.0f);
	glPopMatrix();
	
	glEnable(GL_CULL_FACE); // Habilita novamente a remo��o de faces
	glPushMatrix(); // bola
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0.0f, 15.0f, -20.0f);
	glutSolidSphere(15.0, 20, 20);
	glPopMatrix();
	
	glPushMatrix(); // Toro
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(30.0f, 7.5f, 10.0f);
	glRotatef(180.0f, 0.0f, 1.0f, 1.0f);
	glutSolidTorus(5.0f, 15.0f, 20, 20);
	glPopMatrix();
}


void init (void)
{ 
	GLfloat luzAmbiente[4]={0.3,0.3,0.3,1.0}; 
	GLfloat luzDifusa[4]={0.9,0.9,0.9,1.0};	   // "cor" 
	GLfloat luzEspecular[4]={0.8, 0.8, 0.8, 1.0};// "brilho" 
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
	
	// Especifica sistema de coordenadas de proje��o
	glMatrixMode(GL_PROJECTION);
	// Inicializa sistema de coordenadas de proje��o
	glLoadIdentity();

	// Especifica a proje��o perspectiva
	gluPerspective(angle,fAspect,0.4,500);

	// Especifica sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa sistema de coordenadas do modelo
	glLoadIdentity();

	// Especifica posi��o do observador e do alvo
	gluLookAt(150,120,150, 
			0,20,0,	
		    0,1,0);
	
}


// Fun��o callback chamada quando o tamanho da janela � alterado 
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

void mouseWheel(int button, int dir, int x, int y) {
    if (dir > 0 ) { // scroll para cima
        angle += -1.0f;
    }
    else if (dir < 0) { // scroll para baixo
        angle += 1.0f;
    }
    init();
    display();
}

// Programa Principal
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400,350);
	glutCreateWindow("Visualizacao 3D");
	glutMouseWheelFunc(mouseWheel);
	glutDisplayFunc(display);
	glutReshapeFunc(AlteraTamanhoJanela);
	
	init();
	glutMainLoop();
}
