# Implementado por Caio Carvalho Gonçalves

# Programa usa um arquivo .csv para a entrada dos dados (ano e transistores)
# O arquivo "entrada.csv" contém os dados da questão, basta compilar da forma a seguir

# Compilação:

# python3 q3.py < entrada.csv

#       ou

# python q3.py < entrada.csv


import sys
import math

# Calcula o coeficiente angular e linear da reta de ajuste
def minimos_quadrados(x, y):
    # Número de dados em cada lista
    n = len(x)
    
    # Somatórios
    somatorio_x = sum(x)
    somatorio_y = sum(y)
    somatorio_xy = sum(x_i * y_i for x_i, y_i in zip(x, y)) # Somatorio do produto x_i * y_i
    somatorio_x2 = sum(x_i * x_i for x_i in x) # Somatorio do produto x_i * x_i

    # Coeficiente Angular
    a = (n * somatorio_xy - somatorio_x * somatorio_y) / (n * somatorio_x2 - somatorio_x * somatorio_x)

    # Coeficiente Linear
    b = (somatorio_y - (a * somatorio_x)) / n

    return a, b

# Função calcula o R^2 da reta de ajuste obtida anteriormente
def calcular_r2(y, y_ajuste):
    
    # Calcula a média de y
    media_y = sum(y) / len(y)
    
    # Soma dos quadrados dos resíduos
    ss_res = sum((yi - y_aj) ** 2 for yi, y_aj in zip(y, y_ajuste))
    
    # Soma dos quadrados totais
    ss_tot = sum((yi - media_y) ** 2 for yi in y)
    
    # Cálculo do R^2
    r2 = 1 - (ss_res / ss_tot)

    return r2

def ler_csv():
    print("Insira o conteúdo do arquivo .CSV pela entrada padrão (sem cabeçalho, primeira coluna para X e segunda para Y):")
    
    # Lê o conteúdo da entrada padrão, limpando linhas e espaços
    csv_input = sys.stdin.read().strip().splitlines()
    
    # Inicializa as listas de x e y
    x = []
    y = []
    
    # Processa cada linha do .CSV
    for linha in csv_input:
        valores = linha.split(',')
        
        # Verifica se a linha tem duas colunas
        if len(valores) != 2:
            print("Erro: Cada linha do .CSV deve conter exatamente dois valores separados por vírgula.")
            return None, None
        
        try:
            # Converte os valores para float e coloca os valores de y em base logaritmica 
            x.append(float(valores[0].strip()))
            y.append(math.log10(float(valores[1].strip())))
        except ValueError:
            print("Erro: Certifique-se de que todos os valores são números válidos.")
            return None, None
    
    return x, y

def main():
    
    # Recebe os dados de x e f(x) no arquivo .CSV por meio da entrada padrão
    x, y = ler_csv()

    # Verifica se os dados foram carregados corretamente
    if x and y:        
        
        # Calcula o Coeficiente Angular (m) e o Coeficiente Linear (n)
        m, n = minimos_quadrados(x, y)
    
        # Declara lista dos y = f(x) e calcula y_ajuste para cada x_i
        y_ajuste = [(m * x_i) + n for x_i in x] 
    
        # Calcula o R^2 da Reta de Ajuste
        r2 = calcular_r2(y, y_ajuste)

        # Imprime na tela a reta e os f(2010), f(2020), f(2030)
        print(f"Reta de Ajuste: f(a) = y = {m:.2f} x {"+" if n >= 0 else ""}{n:.2f}, R² = {r2:.4f}")
        print(f"f(2010) = {((m * 2010) + n):.3f}")
        print(f"f(2020) = {((m * 2020) + n):.3f}")
        print(f"f(2030) = {((m * 2030) + n):.3f}")

    else:
        print("Erro ao carregar os dados.")

if __name__ == "__main__":
    main()
