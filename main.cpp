#include <GL/gl.h>      //biblioteca que permite todas as chamadas da API openGL
#include <GL/glut.h>     //bibliotecao que permite a manipulação de janelas
#include <Math.h>                   //conjunto de funções para operações matemáticas
#include <iostream>

GLfloat movex = 0, movey = 0;
enum Direcao : GLint { ESQUERDA, DIREITA, CIMA, BAIXO };
GLint direcao = CIMA;

void pista();

void timerPonto(GLint step) {
    if (direcao == ESQUERDA) {
        movex -= step;
    } else if (direcao == DIREITA) {
        movex += step;
    } else if (direcao == CIMA) {
        movey += step;
    } else if (direcao == BAIXO) {
        movey -= step;
    }

    pista();

    glutPostRedisplay();                 //chama a função desenha toda vez que for necessária
    glutTimerFunc(10,timerPonto,1);      //precisamos chamar a função timer toda vez, Ele executa essa função timer e entra aqui novamente. Até eu querer sair da função timer (neste caso, não queremos sair)
    std::cout << movex << " " << movey << std::endl;
}

void pista() {
    if (movex == 0 and movey == 78)
        direcao = ESQUERDA;
    else if (movex == -72 and movey == 78)
        direcao = CIMA;
    else if (movex == -72 and movey == 90)
        direcao = DIREITA;
    else if (movex == 13 and movey == 90)
        direcao = BAIXO;
    else if (movex == 13 and movey == 5)
        direcao = ESQUERDA;
    else if (movex == 0 and movey == 5)
        direcao = CIMA;
}

void pontoCarro(){
    glPointSize(20);           //adiciona espessura do ponto
    glColor3f(0.69, 0.93, 0.93);         //adiciona cor aos pontos

    glBegin(GL_POINTS);       //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
       glVertex2f(75, -03);     //desenha um ponto na coordenada x, y
    glEnd();
}


void poligono1(){
    glColor3f(0, 0, 0);   //adiciona cor ao poligono
    glBegin(GL_POLYGON);       //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glVertex2f(70, 0);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(90, 0);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(90, 90);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(70, 90);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
    glEnd();
}

void poligono2(){
    glColor3f(0, 0, 0);   //adiciona cor ao poligono
    glBegin(GL_POLYGON);       //lBegin e glEnd delimitam os vértices que definem uma primitiva ou um grupo de primitivas semelhantes (definida como parâmetro).
        glVertex2f(0, 70);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(90, 70);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(90, 90);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
        glVertex2f(0, 90);     //adiciona um ponto na coordenada x, y que será usado para fazer nosso poligono
    glEnd();
}

void listrasVerticais(){
    glLineWidth(4);
    glColor3f(1, 1, 0);
    int x = 80, y;
    for (y = 0; y <= 70; y = y + 10){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x, y + 4);
    glEnd();
    }
}

void listrasHorizontais(){
    glLineWidth(4);
    glColor3f(1, 1, 0);
    int x , y = 80;
    for (x = 0; x <= 70; x = x + 10){
    glBegin(GL_LINE_STRIP);
        glVertex2f(x, y);
        glVertex2f(x + 4, y);
    glEnd();
    }
}

//Função de desenho
void desenhaObjetos(void){
    glClear(GL_COLOR_BUFFER_BIT);  //buffer padrão (limpa a tela toda vez que a função é chamada)
 glMatrixMode(GL_PROJECTION);   //projeção dos pontos definidos no plano cartesiano
    glLoadIdentity();              //carrega a projeção
    gluOrtho2D(0,100,0,100);     // define o tamanho do plano cartesiano
 glMatrixMode(GL_MODELVIEW);    // projeção do tipo modelo
    glLoadIdentity();              // carrega a identidade de projeção de modelo

    glPushMatrix();      //insere a matriz de transformação corrente na pilha
        poligono1();      //chama a função que desenha um poligono
    glPopMatrix();       //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

    glPushMatrix();      //insere a matriz de transformação corrente na pilha
        poligono2();      //chama a função que desenha um poligono
    glPopMatrix();       //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

    glPushMatrix();
        listrasVerticais();
    glPopMatrix();

     glPushMatrix();
        listrasHorizontais();
    glPopMatrix();


        glTranslatef(movex, movey,0);         //chama a fução de tranlação e passa como parâmetro o valor para transladar em x e y
        pontoCarro();                           // chama a função que desenha um quadrado
    glPopMatrix();                            //retira a matriz do topo da pilha e torna esta última a matriz de transformação corrente

 glFlush();          //carrega os comandos OpenGL (envia para o hardware os comandos, permitindo assim que os drivers GL iniciem o render)

}
/*função que atriui valores as nossas variáveis de escala e rotação (dependendo da tecla pressionada) */
//void teclas(unsigned char tecla, GLint x, GLint y){
/*    switch(tecla){
       case '+': escala++;         // adiciona 1 ao valor de escala
        break;
        case '-': escala--;         // remove 1 ao valor de escala
        break;
       case '1': rotacao-=10;      // rotaciona o objeto no sentido horário (diminui o ângulo em 10)
        break;
       case '2': rotacao+=10;      // rotaciona o objeto no sentido anti-horário (aumenta o ângulo em 10)
        break;
    }
    glutPostRedisplay();            //redesenha a cena que está na janela
} */
void setasDirecionais(GLint tecla, GLint x, GLint y){
    switch(tecla){
        case GLUT_KEY_LEFT: movex--;               // move nosso objeto para a esquerda
        break;
        case GLUT_KEY_RIGHT: movex++;              // move nosso objeto para a direita
        break;
        case GLUT_KEY_UP: movey++;                 // move nosso objeto para cima
        break;
        case GLUT_KEY_DOWN: movey--;               // move nosso objeto para baixo
        break;
    }
    glutPostRedisplay();
}


int main(void){

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);                                                      //somente um buffer | sistema de cores RGB
glutInitWindowSize(800,600);                                                                      //define o tamanho da janela
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH)-960)/2,(glutGet(GLUT_SCREEN_HEIGHT)-540)/2);   //medidas usadas para posicionar a janela no meio da tela - isso depende da resolução do monitor
    glutCreateWindow("teclado");                                                         //permite a criação de uma janela
    glutDisplayFunc(desenhaObjetos);
//    glutKeyboardFunc(teclas);                                           // Chamada da função teclado (cada pressionamento gera uma chamada do teclado)
    glutSpecialFunc(setasDirecionais);
    glutTimerFunc(10, timerPonto, 1);                                 // três valores disponíveis (tempo (milissegundos) a o nome da função e valor padrão para retorno)                                                               //função de callback - chama a função desenhaObjetos
    glClearColor(0.13, 0.55, 0.13, 0);                                                                            //informa a cor de fundo da tela (branco)
    glutMainLoop();                                                                                   //loop infinito - escuta as informações do sistema até encerrar a aplicação
    return 0;                                                                                         //retorna zero
}

