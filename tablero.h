#include "LOpenGL.h"
#include "celda.h"

class tablero{
	private:
		int n_;
		int m_;
		float densidad_;
		std::vector<celda> celdas_;
		std::vector<int> obstaculos_;
	public:
		tablero(void);
		tablero(int,int,float);
		~tablero(void);
		int& get_n(void);
		int& get_m(void);
		celda& get_celda(int,int);
		std::vector<int>& get_vec(void);
		void print(void);
	private:
		int get_pos(int,int);
};
