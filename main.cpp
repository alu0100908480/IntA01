#include "LOpenGL.h"
#include "tablero.h"
#include "car.h"

const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int SCREEN_FPS = 60;

tablero* entorno;   // declaramos el tablero y el coche
car* coche;
GLuint cubo, suelo;

void init_entorno(int &, int &, float &);
void runMainLoop(int);
void GenerateList(void);
bool initGL(void);
void update(void);
void render(void);

int main(int argc, char *argv[]) {
  int altura, profundidad;
  float ratio;


  init_entorno(altura, profundidad, ratio);
  coche = new car(altura,profundidad);
  entorno = new tablero(altura, profundidad, ratio, coche->get_pos());
  entorno->print();

  glutInit( &argc, argv ); //Inicializamos freeglut
  glutInitContextVersion( 2, 1 ); //Creamos un contexto opengl

  glutInitDisplayMode( GLUT_DOUBLE ); //Creamos una ventana con doble buffer
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "Practica_01_IA" );

  if( !initGL() ){   //Comprobamos que podemos inicializar opengl
      std::cout << "-->Algo raro paso con las librerias gráficas!" << std::endl;
      return 1;
  }
  else{
      std::cout << "-->Las librerias gráficas se cargaron correctamente" << std::endl;
      GenerateList(); // dibujamos todos los objetos 3d que vamos a usar en la simulación
  }


  glutKeyboardFunc( handleKeys );   //hacemos que glut se encargue del input del usuario

  glutDisplayFunc( render );    //le indicamos a glut que queremos que use nuestra función como render

  glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );   //indicamos cual va a ser el loop principal de la app

  glutMainLoop();   //iniciamos glut

  return 0;
}

void init_entorno(int &n, int &m, float &ratio){
  std::cout << std::endl << std::setw(8) << " " << "Práct 01: Búsqueda" << std::endl;
  std::cout << "-->Introduzca las variables del entorno." << std::endl << std::setw(2) << " " << "-altura: ";
  std::cin >> n;
  std::cout << std::setw(2) << " " << "-profundidad: ";
  std::cin >> m;
  std::cout << std::setw(2) << " " <<  "-ratio: ";
  std::cin >> ratio;
}

void runMainLoop(int val){
  render();
  update();
  glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, val );  //hacemos otra llamada 1/60 seg para tener los 60 fps
}

void GenerateList(){
    suelo = glGenLists(1);   //se genera la lista cubo.

    glNewList(suelo, GL_COMPILE);

    glBegin(GL_LINES);

    GLfloat x = entorno->get_m();
    GLfloat z = entorno->get_n();

    glColor3f(0.282f, 0.820f, 0.800f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, -1 * z);

    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(1 * x, 0.0f, 0.0f);

    glVertex3f(x, 0.0f, 0.0f);
    glVertex3f(x, 0.0f, -1 * z);

    glVertex3f(x, 0.0f, -1 * z);
    glVertex3f(0.0f, 0.0f, -1 * z);

    //Lineas verticales
    for(GLfloat i = 0.0f; i < z; i += 1.0f){
        glVertex3f(0.0f, 0.0f,-1 * i);
        glVertex3f(x, 0.0f, -1 * i);
    }

    //Lineas horizontales
    for(GLfloat j = 0.0f; j > -x; j -= 1.0f){
        glVertex3f(-1 *j, 0.0f, 0.0f);
        glVertex3f(-1 *j, 0.0f, -1 * z);
    }

    glEnd(); // tenemos un grid redimensionable de cuadros de 1 x 1.

    glEndList();

    cubo = glGenLists(1);   //se genera la lista cubo.

    glNewList(cubo, GL_COMPILE);

    glBegin(GL_QUADS); // obstáculos del mapa y el coche

    for(int k = 0; k < entorno->get_vec().size(); k++){
      std::vector<int> vect = entorno->get_vec();
      int dummy = entorno->get_m() * entorno->get_n();
      int j = vect[k]/entorno->get_m() +1;
      int i = vect[k] % entorno->get_m() +1;
      glNormal3f(0.0f, 1.0f, 0.0f);
      glVertex3f(i-1, 0.0f, -1 * (j-1));
      glVertex3f(i-1, 0.0f, -1 * j);
      glVertex3f(i, 0.0f, -1 * j);
      glVertex3f(i, 0.0f, -1 * (j-1));
    }

    std::vector<int> dummy = coche->get_pos();
    int i = dummy[0];
    int j = dummy[1];
    glColor3f(0.863f, 0.078f, 0.235f);

    //cara abajo
    glNormal3f(0, -1, 0);
    glVertex3f(i-1,   0, -1 * (j - 1)  );
    glVertex3f(i-1,   0, -1 * j        );
    glVertex3f(i  ,   0, -1 * j        );
    glVertex3f(i  ,   0, -1 * (j - 1)  );

    //cara arriba
    glNormal3f(0, 1, 0);
    glVertex3f(i-1, 1,  -1 * (j-1)     );
    glVertex3f(i-1, 1,  -1 * j         );
    glVertex3f(i,   1,  -1 * j         );
    glVertex3f(i,   1,  -1 * (j-1)     );

    //cara izquierda
    glNormal3f(-1, 0, 0);
    glVertex3f(i-1,   0,  -1 * (j-1) );
    glVertex3f(i-1,   1,  -1 * (j-1) );
    glVertex3f(i-1,   1,  -1 * j     );
    glVertex3f(i-1,   0,  -1 * j     );

    //cara frontal
    glNormal3f(0, 0, 1);
    glVertex3f(i,     0,  -1 * (j-1) );
    glVertex3f(i,     1,  -1 * (j-1) );
    glVertex3f(i-1,   1,  -1 * (j-1) );
    glVertex3f(i-1,   0,  -1 * (j-1) );

    //cara derecha
    glNormal3f(1, 0, 0);
    glVertex3f(i  ,   0,  -1 * j        );
    glVertex3f(i,     1,  -1 * j         );
    glVertex3f(i,     1,  -1 * (j-1)     );
    glVertex3f(i  ,   0,  -1 * (j - 1)  );

    //cara trasera
    glNormal3f(0, 0, -1);
    glVertex3f(i-1,     0,  -1 * (j-1) );
    glVertex3f(i-1,     1,  -1 * (j-1) );
    glVertex3f(i,   1,  -1 * (j-1) );
    glVertex3f(i,   0,  -1 * (j-1) );

    glEnd();

    glEndList();
}

bool initGL(){
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode( GL_PROJECTION );  //inicalizamos la matriz de proyección
    glLoadIdentity();
    gluPerspective(50.0f, (GLfloat)SCREEN_WIDTH / (GLfloat)SCREEN_HEIGHT, 0.5f, 50.0f);

    GLfloat x = entorno->get_m();
    GLfloat z = entorno->get_n();

  //  gluLookAt(7.5, 12, 8, 7.5, 0, -5, 0, 1, 0);
    gluLookAt(x/2, x-3, z-5, x/2, 0, -5, 0, 1, 0);

    glMatrixMode( GL_MODELVIEW ); //inicializamos la matriz de vista de modelos
    glLoadIdentity();

    glClearColor( 0.f, 0.f, 0.f, 1.f ); //inicializamos el color del clear

    GLenum error = glGetError(); //comprobamos que no haya ningún error
    if( error != GL_NO_ERROR ){
        printf( "Error iniciando OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }
    return true;
}

void update(){
}

void render(void){
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //limpiamos el buffer


    glMatrixMode( GL_MODELVIEW ); //reseteamos la matriz de modelos
    glLoadIdentity();

    glCallList(suelo);

    glMatrixMode( GL_MODELVIEW ); //reseteamos la matriz de modelos
    glLoadIdentity();

    glCallList(cubo);

   glutSwapBuffers(); //intercambia los buffers y actualiza la pantalla
}
