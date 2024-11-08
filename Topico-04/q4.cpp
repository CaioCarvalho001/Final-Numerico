// Implementado por Caio Carvalho Gonçalves

// Programa precisa da biblioteca GiNaC por causa dos problemas continuos
// Tutorial de instalação da GiNaC está no README

// Compilar com g++ 

// g++ q4.cpp Funcao.cpp -lcln -lginac



#include <iostream>
#include <string>
#include <vector>
#include "Funcao.h"


/* Problemas Discretos */

// Função que realiza o método dos trapezios repetidos com valores discretos da função f(x)
double TrapeziosRepetidos(std::vector<double>& lista, double a, double b, int n){
    //double n = lista.size();
    double h = (b - a)/n;

    double somatorio = 0; 


    for(int i = 0; i <= n; i++){ 
        
        somatorio += ((i == 0) || (i == n)) ? lista[i]: 2*lista[i];
    }

    somatorio = somatorio * (h/2);
    return somatorio;
}

// Função que realiza o método de um terço de simpson repetido com valores discretos da função f(x)
double SimpsonRepetido(std::vector<double>& lista, double a, double b, int n){
    //double n = lista.size();
    double h = (b - a)/n;
    double somatorio = 0; 

    for(int i = 0; i <= n; i++){       

        if((i == 0) || (i == n))
            somatorio += lista[i];
        else if(!(i % 2))
            somatorio += 2*lista[i];
        else
            somatorio += 4*lista[i];
    }

    somatorio = somatorio * (h/3);
    return somatorio;
}



/* Problemas Continuos */


// Função que realiza o método dos trapezios repetidos com a função f(x)
double TrapeziosRepetidos(std::string funcao, double a, double b, int n){
    
    Funcao F(funcao);
    double h = (b - a)/n;
    double somatorio = 0; 
    double x = a;

    for(int i = 0; i <= n; i++){       
        somatorio += ((i == 0) || (i == n)) ? F.imagem(x): 2*F.imagem(x);
        x = x + h;
    }

    somatorio = somatorio * (h/2);
    return somatorio;
}

// Função que realiza o método de um terço de simpson repetido com a função f(x)
double SimpsonRepetido(std::string funcao, double a, double b, int n){
    
    Funcao F(funcao);
    double h = (b - a)/n;
    double somatorio = 0; 
    double x = a;

    for(int i = 0; i <= n; i++){       
        if((i == 0) || (i == n))
            somatorio += F.imagem(x);
        else if(!(i % 2))
            somatorio += 2*F.imagem(x);
        else
            somatorio += 4*F.imagem(x);

        x = x + h;
    }

    somatorio = somatorio * (h/3);
    return somatorio;
}


int main(void){
    //Declara variáveis
    char op;
    double a, b;
    int n;
    std::string funcao;

    printf("Bem vindo(a) a Calculadora de Vazao\n");
    printf("Deseja calcular a seção transversal de um rio? [S/N]: ");
    scanf("%c%*c", &op);


    // Inicio do loop
    do {

        //Caso usuário insira diferente da letra S, o loop se encerra
        if(op != 'S' && op != 's')
            break;

        char op2;
        printf("Possui uma função que descreve a profundidade pela distancia? [S/N]: ");
        scanf("%c%*c", &op2);
        
        //Entra se o usuário tiver a função f(x)
        if(op2 ==  'S' || op2 ==  's'){
            printf("Insira a função real: ");
            std::getline(std::cin, funcao);
            //scanf("%[^\n]%*c", funcao.c_str());

            printf("Insira o inicio do intervalo [a,b]: ");
            scanf("%lf%*c", &a);

            printf("Insira o fim do intervalo [a,b]: ");
            scanf("%lf%*c", &b);

            printf("Insira o número de subintervalos: ");
            scanf("%d%*c", &n);

            printf("Integral de %s, pelo Método dos Trapezios Repetidos é igual a %.5lf\n", funcao.c_str(), TrapeziosRepetidos(funcao, a, b, n)); 

            //Método de um terço de simpson não pode ser feito com número impar de subintervalos
            if(!(n % 2))
                printf("Integral de %s, pelo Método de Um Terço de Simpson é igual a %.5lf\n", funcao.c_str(), SimpsonRepetido(funcao, a, b, n)); 
            else 
                printf("Método de Um Terço de Simpson não pode ser cálculado para um número ímpares de subintervalos\n");

        
        //Entra se o usuário não tiver função f(x)
        } else if(op2 == 'N' || op2 ==  'n'){
            std::vector<double> lista;
            double h;

            lista.reserve(10);
            

            printf("Insira o inicio do intervalo [a,b]: ");
            scanf("%lf%*c", &a);

            printf("Insira o fim do intervalo [a,b]: ");
            scanf("%lf%*c", &b);

            printf("Insira o número de subintervalos: ");
            scanf("%d%*c", &n);

            h = (b-a)/n;

            // Recebe os valores discretos de f(x) na lista
            printf("Insira o valor da profundidade correspondente de cada f(x_i), i = 1, ... , n: \n");
            for(int i = 0; i <= n; i++){
                double x;

                printf("f(%.3lf) = ", a + i*h);
                scanf("%lf%*c", &x);
                lista.push_back(x);

            }


            printf("Integral de f(x), pelo Método dos Trapezios Repetidos é igual a %.5lf\n", TrapeziosRepetidos(lista, a, b, n)); 
            
            //Método de um terço de simpson não pode ser feito com número impar de subintervalos
            if(!(n % 2))
                printf("Integral de f(x), pelo Método de Um Terço de Simpson é igual a %.5lf\n", SimpsonRepetido(lista, a, b, n)); 
            else 
                printf("Método de Um Terço de Simpson não pode ser cálculado para um número ímpares de subintervalos\n");
        }

        printf("Deseja continuar o uso da aplicação? [S/N]: ");
        scanf("%c%*c", &op);

        puts("\n");
    } while(op == 'S' || op == 's');

    

    
}