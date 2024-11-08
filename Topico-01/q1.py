# Implementado por Pedro Lucas Gomes Ferreira

# Programa precisa da biblioteca numpy 
# Tutorial de instalação da numpy está no README

# Compilação:

# python3 q1.py 

#       ou

# python q1.py


import numpy as np

def JordanMethod(matrix):
    matrix = matrix.astype(float)  # Garantir que todos os elementos sejam float
    rows, cols = matrix.shape

    for i in range(rows):
        # Verificar se é necessário trocar linhas
        if matrix[i][i] == 0:
            for k in range(i + 1, rows):
                if matrix[k][i] != 0:
                    # Troca de linha para evitar pivô zero
                    matrix[[i, k]] = matrix[[k, i]]
                    break
            else:
                print('O sistema é indeterminado ou impossível')
                return None

        # Normalizar a linha para tornar o pivô igual a 1
        pivot = matrix[i][i]
        matrix[i] = matrix[i] / pivot

        # Zerar os elementos nas outras linhas na coluna do pivô
        for j in range(rows):
            if j != i:
                factor = matrix[j][i]
                matrix[j] = matrix[j] - factor * matrix[i]

    # As soluções são os elementos da última coluna
    solutions = matrix[:, -1]
    return solutions

def form():
    while True:
        print('Insira a quantidade de materiais que serão ultilizados na construção.')
        rows = int(input())
        print('Insira a quantidade de minas que serão ultilizados na retirada de materias.')
        cols = int(input())
        if rows > 0 and cols > 0:
            break

    if rows != cols:
        print('O sistema é indeterminado ou impossível')
        return

    n = cols + 1
    m = rows
    matrix = np.zeros((m, n))

    for i in range(m):
        for j in range(n):
            if j == cols:
                print(f'Insira a quantidade do material {(i + 1)} desejada (em m3):')
                matrix[i][j] = float(input())
                break
            print(f'Insira o percentual do material {(i + 1)} disponível na mina {(j + 1)}:')
            p = input()
            matrix[i][j] = float(p) / 100

    solutions = JordanMethod(matrix)
    if solutions is None: return

    print('')
    for i in range(m):
        print(f'{solutions[i]:.3f} m3 devem ser estraidos da mina {(i + 1)}.')

while True:
    form()
    print('')
    print('Deseja recomeçar? 1(sim), 0(não):')
    print('')
    if int(input()) == 0:
        exit()