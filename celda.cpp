#include "celda.h"
/*Las celdas pueden ser de varios tipos:
    - tipo r --> no presentan ningún obstáculo
    - tipo o --> presentan obstáculos para el vehículo
    - tipo n --> se comportan como r
*/
celda::celda(char t):
type_(t){
}

celda::celda(void){
type_ = 'n';
}

celda::~celda(void){
}

char& celda::get_type(void){
  return type_;
}
