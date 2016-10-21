#include "car.h"

car::car(int x,int y):
posicion(){
  posicion.push_back(rand() % x);
  posicion.push_back(rand() % y);
}

car::~car(){
}

std::vector<int> car::get_pos(void){
  return posicion;
}

void car::act_pos(int x, int y){
  posicion[0] = x;
  posicion[1] = y;
}
