import matplotlib.pyplot as plt

# Dados do vetor
valores  = [0.4173,0.0062,0.3387,0.1886,0.7418,0.3138,0.4466,0.0835,0.1930,0.3807,0.5438,0.5897,0.3536,0.2210,0.0631,0.4499,0.2564,0.7642,0.1411,0.3626]
valores1 = [0.3522,0.0050,0.3589,0.1393,0.7597,0.2668,0.4569,0.0739,0.1557,0.4085,0.5085,0.5522,0.3436,0.2180,0.0697,0.4365,0.2353,0.7529,0.1291,0.3775]  # Substitua pelos valores reais
valores2 = [0.4018,0.0179,0.3693,0.1515,0.7279,0.2354,0.4367,0.1243,0.2240,0.4092,0.5417,0.6078,0.3198,0.2305,0.0663,0.4151,0.2393,0.7956,0.1416,0.3465]
valores3 = [0.4421,0.0174,0.3494,0.2666,0.7449,0.1712,0.4056,0.0826,0.2318,0.2707,0.5420,0.6218,0.3684,0.2463,0.1724,0.4032,0.2502,0.8003,0.1225,0.3234]


# Eixo X como os índices do vetor
indices = list(range(len(valores)))

# Criar o gráfico
plt.figure(figsize=(8, 5))  # Tamanho opcional do gráfico
plt.plot(indices, valores, label="Saidas desejadas", marker='o', linestyle='-', color='b')
plt.plot(indices, valores1,  label="TDNN3 (T3)", marker='o', linestyle='-', color='r')

# Adicionar título e rótulos aos eixos
plt.title("Saídas x Saídas desejadas")  # Título do gráfico
plt.xlabel("Índices")                     # Rótulo do eixo X
plt.ylabel("Saídas")                     # Rótulo do eixo Y

# Exibir legenda
plt.legend()

# Mostrar a grade
plt.grid(True, linestyle='--', alpha=0.7)

# Exibir o gráfico
plt.show()
