import matplotlib.pyplot as plt
import numpy as np
from numpy.random import rand
import random
time = list(range(30))
speeds = [
    13.04, 18.25, 23.36, 17.51, 31.75, 34.22, 38.07, 34.62, 37.94, 38.30,
    33.87, 47.96, 42.53, 31.42, 38.03, 34.45, 35.53, 27.60, 31.86, 39.46,
    34.48, 47.36, 46.54, 53.64, 58.74, 58.91, 62.17, 73.54, 87.03, 86.86
]


poly = np.polyfit(time, speeds, 6, None, False, None, False )

curve_function = np.poly1d(poly)

tiempo_suave = np.linspace(0, len(time)-1, 100)
velocidad_suave = curve_function(tiempo_suave)
plt.scatter(time, speeds, color='red', zorder=5, label='Datos Reales')

# Dibujamos la línea de la función continua en color azul
plt.plot(tiempo_suave, velocidad_suave, color='blue', label='Curva de Regresión')

# 5. Formato del gráfico (etiquetas y grilla)
plt.title('Regresión Polinómica de Velocidad')
plt.xlabel('Tiempo (s)')
plt.ylabel('Velocidad (m/s)')
plt.grid(True, linestyle='--', alpha=0.6)
plt.legend()

# 6. ¡Mostramos el gráfico en pantalla!
plt.show()
print(poly)
