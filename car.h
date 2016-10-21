#include "LOpenGL.h"

class car{
  private:
      std::vector<int> posicion;
  public:
      car(int,int);
      ~car();
      std::vector<int> get_pos(void);
      void act_pos(int,int);
};
