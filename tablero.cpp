#include "tablero.h"

tablero::tablero(void):
n_(),
m_(),
densidad_(),
celdas_(){}

tablero::tablero(int n, int m, float r):
n_(n),
m_(m),
densidad_(r),
celdas_(){
  std::cout << "-->Información de la tabla" << std::endl;
  int num = n_ * m_; // numero de casillas del tablero
  int num_u = num - (num * densidad_); // numero de casillas disponibles
  int index = 0;
  int aux;
  celda* dummy;

  std::cout << std::setw(2) << " " << "-Numero de casillas totales: " << num << std::endl;
  std::cout << std::setw(2) << " " << "-Numero de casillas disponibles: " << num_u << std::endl << std::endl;

  srand(time(NULL));

  for(int i = 0; i < (num-num_u); i++){
    obstaculos_.push_back(rand() % num);
  }

  for(int i = 0; i < obstaculos_.size(); i++){
        for(int x = i; x < obstaculos_.size(); x++){
          if(obstaculos_[i] > obstaculos_[x]){
            aux = obstaculos_[i];
            obstaculos_[i] = obstaculos_[x];
            obstaculos_[x] = aux;
          }
        }
  }

  for(int i = 0; i < num; i++){
    if(i == obstaculos_[index]){
      index++;
      while(obstaculos_[index] == obstaculos_[index -1])
        index++;
      dummy = new celda('o');
    }
    else{
      dummy = new celda('r');
    }
    celdas_.push_back(*dummy);
  }
}

tablero::~tablero(void){
  n_ = 0;
  m_ = 0;
  densidad_ = 0;
}

celda& tablero::get_celda(int i, int j){
  return celdas_[get_pos(i,j)];
}

std::vector<int>& tablero::get_vec(void){
  return obstaculos_;
}

int& tablero::get_n(void){
  return n_;
}

int& tablero::get_m(void){
  return m_;
}

void tablero::print(void){
  int num = n_ * m_;
  for(int i = 0; i < num; i++){
    if((i % m_ == 0) && (i != 0)){
      std::cout << std::endl << celdas_[i].get_type() << " ";
    }
    else{
      std::cout << celdas_[i].get_type() << " ";
    }
  }
  std::cout << std::endl << std::endl;
}

int tablero::get_pos(int i, int j){
  return i * (j-1) + j;
}
