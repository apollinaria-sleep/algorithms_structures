import numpy as np
import random

def Compare(X, Y):
    return np.abs(X - Y).sum()

def IsTrill(A):
    for i in np.arange(A.shape[0]):
        for j in np.arange(i+1, A.shape[0]):
            if A[i][j] != 0:
                return False
    return True

def SolveSystem(A, b):
    if IsTrill(A)==False:
        raise Exception("Матрица С не треугольная\n")
    
    x = np.zeros(b.shape[0])
    for i in np.arange(b.shape[0]):
        summ = 0
        for j in np.arange(i):
            summ += x[j] * A[i][j]
        x[i] = (b[i] - summ) / A[i][i]
    return x

def CholeskyMethod(A, b): 
    A = np.array(A)
    b = np.array(b)
    if A.shape[0] != A.shape[1]:
        raise Exception("Матрица А не квадратная\n")
    
    if Compare(A, A.T) != 0: # проверка симметричности матрицы А
        raise Exception("Матрица A не симметрична\n")
    
    L = np.zeros(A.shape)
    
    summ = 0
    for i in np.arange(0, A.shape[0]):
        summ = 0
        for k in np.arange(i):
            summ += (L[i][k]**2)
        L[i][i] = (A[i][i] - summ)**0.5
        for j in np.arange(i, A.shape[0]):
            summ = 0
            for k in np.arange(i):
                summ += L[i][k] * L[j][k]
            L[j][i] = (A[j][i] - summ) / L[i][i]

    y = SolveSystem(L, b)
    x = SolveSystem(L.T[::-1, ::-1], y[::-1])[::-1]
        
    return L, x

def Testing(A, b):
    print('A:\n', A)
    print('\nb:\n', b, '\n')

    C, x = CholeskyMethod(A, b)
    print('C:\n', C)
    print('\nx:\n', x)

    print("Отличие от библиотечной функции np.linalg.solve: ", Compare(x, np.linalg.solve(A, b)))
    print("Отличие от библиотечной функции np.linalg.cholesky: ", Compare(C, np.linalg.cholesky(A)))
    

A = np.array([[6, 1],
    [1, 8]])
b = [8, 17]
Testing(A, b)

A = np.array([[1, 2],
    [2, 8]])
b = [1, 2]
Testing(A, b)

A = np.array([[3, 5],
    [5, 9]])
b = [4, 9]
Testing(A, b)

A = np.array([[81, -45, 45],
    [-45, 50, -15],
    [45, -15, 38]])
b = [531, -460, 193]
Testing(A, b)

A = np.array([[9, -5, 4],
    [-5, 8, -6],
    [4, -6, 5]])
b = [10, 3, -5]
Testing(A, b)

A = np.array([[15, 3, 4, 5],
              [3, 16, 4, 5],
              [4, 4, 17, 5],
              [5, 5, 5, 18]])
b = [13, -1, 17, -50]
Testing(A, b)
