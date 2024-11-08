#include <iostream>
#include <string>
#include <ginac/ginac.h>
#include "Funcao.h"


Funcao::Funcao(std::string entrada){
    GiNaC::parser leitor;

    f = leitor(entrada);
    GiNaC::symtab tabela = leitor.get_syms();
    x = GiNaC::ex_to<GiNaC::symbol>(tabela["x"]);

    df = f.diff(x);

}

void Funcao::imagem(void) const{
    

    std::cout << "f(x) = "<< f;
    
    return;
}

double Funcao::imagem(double num) const{
    GiNaC::ex valor = f.subs(x == num);
    //std::cout << "f(" << num << ") = " << f.subs(x == num) << std::endl;
    double resutado = GiNaC::ex_to<GiNaC::numeric>(valor.evalf()).to_double();
    
    return resutado;
}

void Funcao::derivada(void) const{
    std::cout << f.diff(x) << std::endl;
    
    return;
}

double Funcao::derivada(double num) const{
    GiNaC::ex valor = df.subs(x == num);
    //std::cout << "f(" << num << ") = " << f.subs(x == num) << std::endl;
    double resutado = GiNaC::ex_to<GiNaC::numeric>(valor.evalf()).to_double();
    
    return resutado;
}
