#include<GL/gl.h>
#include<GL/glut.h>
#include <math.h>
#define PI 3.1415926535898

//Variaveis Globais

GLfloat escala = 1;
GLfloat rotacao = 0;
GLfloat movx = 0; //recebe do teclado para mover a nave
GLfloat movy = 0; //recebe do teclado para mover a nave


GLint movePontoX = 0; // velocidade da bola
GLint movePontoY = 0; // velocidade da bola

GLint direcaoX = 0;  // positivo / negativo no plano
GLint direcaoY = 0; // positivo / negativo no plano
GLint tempoexecucao = 0;



void Navi(){
    //corpo navi
    glBegin(GL_POLYGON);
        glColor3f(0,0,1);
        glVertex2f(0,0);
        glVertex2f(1,0);
        glVertex2f(2,-2);
        glVertex2f(2,-5);
        glVertex2f(1,-6);
        glVertex2f(-1,-6);
        glVertex2f(-2,-5);
        glVertex2f(-2,-2);
        glVertex2f(-1,0);
    glEnd();

    //cokpit
    /*
    glBegin(GL_QUADS);
        glColor3f(1,0,1);
        glVertex2f(-2.5,-3.5);
        glVertex2f(0,0);
        glVertex2f(-1,-1);
        glVertex2f(1,1);
    glEnd();
    */

    //motor direito
    glBegin(GL_POLYGON);
        glColor3f(0.41,0.41,0.41);
        glVertex2f(2,-3);
        glVertex2f(3,-3);
        glVertex2f(3,-5);
        glVertex2f(2,-5);
    glEnd();
    //fogo
    //glScalef(escala, escala, 0);
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex2f(3,-5);
        glVertex2f(2,-5);
        glVertex2f(2.5,-7);
    glEnd();
    //glLoadIdentity();


    //esquerda
    glBegin(GL_POLYGON);
        glColor3f(0.41,0.41,0.41);
        glVertex2f(-2,-3);
        glVertex2f(-3,-3);
        glVertex2f(-3,-5);
        glVertex2f(-2,-5);
    glEnd();
    //fogo
    glBegin(GL_TRIANGLES);
        glColor3f(1,0,0);
        glVertex2f(-3,-5);
        glVertex2f(-2,-5);
        glVertex2f(-2.5,-7);
    glEnd();

}

void Bola(){
    glBegin(GL_POLYGON);
        glColor3f(1, 0.27, 0);
        for (int i=0; i<20; i++){
            float angulo = 2 * PI * i/20;
            glVertex2f(cos(angulo)+ movePontoX, sin(angulo)*1.2 + movePontoY);
        }
    glEnd();
}


//CONFIG CARTESEANA PARA DESENHAR
void Desenha(void){
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION); //entrada na matrix
    glLoadIdentity(); //F5
    gluOrtho2D(-40,40,-40,40); // define2D e o tamano do plano carteseano
    glMatrixMode(GL_MODELVIEW); //projeta a matrix
    glLoadIdentity();//F5

    //NAVI
    glPushMatrix();
        glScalef(escala, escala, 0);
        glRotatef(rotacao,0,0,1);
        glTranslatef(movx, movy, 0);
        Navi();
    glPopMatrix();


    //bola
    if (tempoexecucao > 0){
        glPushMatrix();
            Bola();
        glPopMatrix();
    }


    glutSwapBuffers();
}

// Animação da bola
void timerPonto(int passo){
    if(direcaoX ==1) {
        movePontoX +=1.3;
        if(movePontoX >=40){direcaoX =0;}
    }else{
        movePontoX -= 1.3;
        if(movePontoX <= -40){direcaoX =1;}
    }


    if(direcaoY ==1) {
        movePontoY +=2.2;
        if(movePontoY >=40){direcaoY =0;}
    }else{
        movePontoY -= 2.2;
        if(movePontoY <= -40){direcaoY =1;}
    }
    tempoexecucao -=1;
    glutPostRedisplay();
    glutTimerFunc(10, timerPonto, 1);
}

void Teclas(unsigned char tecla, GLint x, GLint Y){
    switch(tecla){
        case '+':   escala++;     break;
        case '-':   escala--;     break;
        case '1':   rotacao-=3;   break;
        case '2':   rotacao+=3;   break;
        case 'a':
            //glutTimerFunc(10, timerPonto, 1);
            timerPonto(0);
            tempoexecucao = 100;
        break;

    }
    glutPostRedisplay();
}

//controle da navi
void Controle(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_UP:       movy++;     break;
        case GLUT_KEY_DOWN:     movy--;     break;
        case GLUT_KEY_RIGHT:    movx++;     break;
        case GLUT_KEY_LEFT:     movx--;     break;
    }
    glutPostRedisplay();
}



//PRINCIPAL
int main(void){

    // configuração de janela e buffers
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); //buffer de tela
    glutInitWindowSize(800,600);                //tamanho da tela
    glutInitWindowPosition(250,100);            //posição da tela
    glutCreateWindow("Exemplo em operGL");  // cria janela e da um nome
    glClearColor(1,1,1,0);                  //cor de fundo da janela
    glutDisplayFunc(Desenha);               //desenha dentro da janela
    //glutTimerFunc(10, timerPonto, 1);
    glutKeyboardFunc(Teclas);
    glutSpecialFunc(Controle);

    glutMainLoop();
    return 0;
}
