#include <ginac/ginac.h>
#include <string>

#ifndef FUNCAO_H
#define FUNCAO_H

class Funcao {
    private:
        GiNaC::symbol x;
        GiNaC::ex f;
        GiNaC::ex df;
    
    public:
        Funcao(std::string);
        void imagem(void) const;
        double imagem(double) const;
        void derivada(void) const;
        double derivada(double) const;

};

#endif