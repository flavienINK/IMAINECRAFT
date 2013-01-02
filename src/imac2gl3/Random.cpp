#include "imac2gl3/Random.hpp"
#include "imac2gl3/settings.hpp"

namespace imac2gl3 {

    bool Random::randomBool(int balance){
            if (rand()%100 < balance) return true;
            else return false;
    }
    
    int Random::randomPosition(char vecteur){
            if (vecteur == 'x') return rand()%LARGEUR_TERRRAIN;
            if (vecteur == 'y') return rand()%LONGUEUR_TERRRAIN;
            if (vecteur == 'z') return rand()%HAUTEUR_TERRRAIN;
            return 0;
    }
    
    int Random::randomBalance(int balance){
            if (balance < 0) return 0;
            return rand()%balance;
    }

}
