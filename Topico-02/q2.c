// Implementado por Heitor Wolf Queiroz

// Compilação: gcc q2.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#define TOLERANCE 0.0001
#define MAX_ITERATIONS 100
#define VA 30.0
#define VD 0.0
#define RAB 20.0
#define RAC 120.0
#define RBC 120.0
#define RCD 120.0
#define RBD 120.0


//Critério de linhas
bool linhas(double V_A, double R_AB, double R_AC, double R_BC, double R_CD, double R_BD)
{
	if(abs(R_BD*R_BC+R_AB*R_BC+R_AB*R_BD)>abs(R_AB*R_BD)&&abs(R_CD*R_BC+R_AC*R_BC+R_AC*R_CD)>abs(R_AC*R_CD))
	return true;
	else
	return false;
}


//Critério Sassenfeld
bool sassenfeld(double V_A, double R_AB, double R_AC, double R_BC, double R_CD, double R_BD)
{
	double b1,b2;
	b1=(R_AB*R_BD)/(R_BD*R_BC+R_AB*R_BC+R_AB*R_BD);
	b2=(R_AC*R_CD)/(R_CD*R_BC+R_AC*R_BC+R_AC*R_CD);
	if(abs(b1)<1 && abs(b2)<1)
	return true;
	else
	return false;
}


// Método de Gauss-Seidel com essas equações V_B =(V_A*R_BD*R_BC+V_C*R_AB*R_BD)/(R_BD*R_BC+R_AB*R_BC+R_AB*R_BD);V_C =(V_A*R_CD*R_BC+V_B*R_AC*R_CD)/(R_CD*R_BC+R_AC*R_BC+R_AC*R_CD);
void gaussSeidel(double V_A, double V_B_i, double V_C_i, double *V1, double *V2, double R_AB, double R_AC, double R_BC, double R_CD, double R_BD)
{
	int inte=0;
	 do{
        V_B_i = *V1;
        V_C_i = *V2;

    
        *V1 =(V_A*R_BD*R_BC+(*V2)*R_AB*R_BD)/(R_BD*R_BC+R_AB*R_BC+R_AB*R_BD);
        *V2 =(V_A*R_CD*R_BC+(*V1)*R_AC*R_CD)/(R_CD*R_BC+R_AC*R_BC+R_AC*R_CD);

        inte++;

        // Condição de parada baseada na tolerância
    } while ((fabs(*V1 - V_B_i) > TOLERANCE || fabs(*V2 - V_C_i) > TOLERANCE) && inte < MAX_ITERATIONS);
}


int main() {

    double V_B = 0.0, V_C = 0.0;
    double V_B_i, V_C_i,V_A,V_D,R_AB,R_AC,R_BC,R_CD,R_BD,*V1,*V2;
    char a;
    V1=&V_B;
    V2=&V_C;
    //Flexibiliza o código podendo mudar a tensão e resistência
	printf("Deseja mudar a tensao da fonte,ou resistores? se sim digite S");
	scanf("%c",&a);
    if (a == 's' || a == 'S') {
        printf("Digite o valor da fonte de tensao: ");
        scanf("%lf", &V_A);
        
        printf("Digite o valor de R1: ");
        scanf("%lf", &R_AB);

        printf("Digite o valor de R2: ");
        scanf("%lf", &R_AC);

        printf("Digite o valor de R3: ");
        scanf("%lf", &R_CD);

        printf("Digite o valor de R4: ");
        scanf("%lf", &R_BD);

        printf("Digite o valor de R5: ");
        scanf("%lf", &R_BC);
        V_D=VD;
    }
	else
	{
		//Caso da questão
		V_A=VA;
		V_D=VD;
		R_AB=RAB;
		R_AC=RAC;
		R_BC=RBC;
		R_CD=RCD;
		R_BD=RBD;	
	}

	if(linhas(V_A,R_AB, R_AC, R_BC, R_CD, R_BD)||sassenfeld(V_A, R_AB, R_AC, R_BC, R_CD, R_BD))
	{
	gaussSeidel(V_A, V_B_i, V_C_i, V1, V2, R_AB, R_AC, R_BC, R_CD, R_BD);
    // Cálculo das correntes em cada resistor
    double I_AB = (V_A - V_B) / R_AB;
    double I_AC = (V_A - V_C) / R_AC;
    double I_BC = (V_B - V_C) / R_BC;
    double I_CD = (V_C - V_D) / R_CD;
    double I_BD = (V_B - V_D) / R_BD;

    // Mostra as correntes em cada resistor
    printf("Corrente entre A e B (I1): %.4f A\n", I_AB);
    printf("Corrente entre A e C (I2): %.4f A\n", I_AC);
    printf("Corrente entre C e D (I3): %.4f A\n", I_CD);
    printf("Corrente entre B e D (I4): %.4f A\n", I_BD);
    printf("Corrente entre B e C (I5): %.4f A\n", I_BC);

    // Mostra a corrente total fornecida pela fonte
    double I_total = I_AB + I_AC;
    printf("\nCorrente total fornecida pela fonte: %.4f A\n", I_total);

    return 0;
}
else
{
	printf("Segundo criterio das linhas e de Sassenfeld, pode nao convergir");
	return 0;
}
}
