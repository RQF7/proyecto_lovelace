"""
Programa para graficar los resultados de las pruebas con peticiones
al sistema tokenizador.
Proyecto Lovelace.
"""

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.ticker import FuncFormatter

"""
Tiempo requerido para hacer 10000 tokenización   con FFX:   206.5263979434967
Tiempo requerido para hacer 10000 detokenización con FFX:   208.2042772769928
Tiempo requerido para hacer 10000 tokenización   con BPS:   219.0368800163269
Tiempo requerido para hacer 10000 detokenización con BPS:   219.4488935470581
Tiempo requerido para hacer 10000 tokenización   con TKR:   824.9695003032684
Tiempo requerido para hacer 10000 detokenización con TKR:   103.8542270660400
Tiempo requerido para hacer 10000 tokenización   con AHR:   436.0533792972564
Tiempo requerido para hacer 10000 detokenización con AHR:   132.2974607944488
Tiempo requerido para hacer 10000 tokenización   con DRBG:  437.4067518711092
Tiempo requerido para hacer 10000 detokenización con DRBG:  124.0646553039550
"""

def millions(x, pos):
  return '%1.0f s' % (x)

metodos        = ['FFX', 'BPS', 'TKR', 'AHR', 'DRBG']
tokenizacion   = [206.52, 219.03, 824.96, 436.05, 437.40]
detokenizacion = [208.20, 219.44, 103.85, 132.29, 124.06]

fig, ax = plt.subplots()
indice = np.arange(len(tokenizacion))
ancho = 0.4

ax.set_ylabel('Tiempo')
ax.set_title('Peticiones de tokenización/detokenización')
ax.set_xticks(indice)
ax.yaxis.grid(True, color='#424242', linestyle=':')
ax.set_xticklabels(metodos)

ax.bar(indice - ancho/2, tokenizacion, ancho,
  color='#616161', label='Tokenización')
ax.bar(indice + ancho/2, detokenizacion, ancho,
  color='#757575', label='Detokenización')

formatter = FuncFormatter(millions)
ax.yaxis.set_major_formatter(formatter)
ax.legend()

plt.savefig('../documentos_entregables/reporte_tecnico/contenidos/\
implementacion_api_web/resultados/diagramas/peticiones_tokenizacion\
_grafica.png', dpi=200, bbox_inches='tight')
