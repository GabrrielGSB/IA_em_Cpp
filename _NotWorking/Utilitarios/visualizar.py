import numpy as np
import matplotlib.pyplot as plt

# Carregar dados do arquivo .ubyte
with open(r"C:\Users\G.Gonzaga.S.Barreto\Desktop\IA_Cpp\DATA\dados\train-images-idx3-ubyte", "rb") as f:
    f.read(16)  # Ignorar cabeçalho de 16 bytes
    dados = np.fromfile(f, dtype=np.uint8)

num_imagens = dados.size // (28 * 28)
# Redimensionar a matriz para a forma esperada (exemplo: 28x28 para MNIST)
imagens = dados.reshape((num_imagens, 28, 28))

# Mostrar a imagem
print(num_imagens)
plt.imshow(imagens[50041], cmap="gray")
plt.show()

