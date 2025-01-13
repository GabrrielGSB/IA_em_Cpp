import pandas as pd
import matplotlib as mat
import matplotlib.pyplot as plt
mat.use('TkAgg')
arquivo = pd.read_csv('MLP/ErroQuadMed(2).csv')

plt.figure(figsize=(10, 6))
plt.plot(arquivo.index, arquivo[arquivo.columns[0]], linestyle='-', color='b', label='Dados')  
plt.title('Erro Quadrático Médio x Época', fontsize=16)
plt.xlabel('Época', fontsize=12)
plt.ylabel(arquivo.columns[0], fontsize=12)
plt.legend()
plt.grid(True)
plt.show()