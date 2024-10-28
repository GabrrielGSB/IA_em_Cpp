#ifndef __NEURONIO_HPP
#define __NEURONIO_HPP

#define <stdio.h>
#define <vector>
#define <cmath>

class neuronio
{
	public:
		double saida, Delta;
		vector<double> pesos;
		neuronio(int, int);
		void inicializarPesos(int, int);		
};

#endif