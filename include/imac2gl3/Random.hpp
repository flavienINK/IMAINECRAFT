#ifndef RANDOM_H
#define RANDOM_H

#include <ctime>
#include <cstdlib>

namespace imac2gl3 {
	class Random {
		public:
			bool randomBool(int balance);		
			int randomPosition(char vecteur);			
			int randomBalance(int balance);
	};
}

#endif