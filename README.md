<h1 align="center">
  Proyecto Lovelace
</h1>

<p align="center">
  <a href="https://travis-ci.com/RQF7/proyecto_lovelace" alt="">
     <img src="https://travis-ci.com/RQF7/proyecto_lovelace.svg?token=57K77bpWmFas4ams6Ewm&branch=master"/>
  </a>
  <a href="https://github.com/RQF7/proyecto_lovelace/commits/master" alt="">
     <img src="https://img.shields.io/github/last-commit/RQF7/proyecto_lovelace.svg?style=flat-square&label=%C3%9Altimo+commit"/>
  </a>
  <a href="https://github.com/RQF7/proyecto_lovelace/search?l=tex" alt="">
     <img src="https://img.shields.io/github/languages/code-size/RQF7/proyecto_lovelace.svg?style=flat-square&label=Tama%C3%B1o+del+c%C3%B3digo"/>
  </a>
  <a href="https://github.com/RQF7/proyecto_lovelace/search?l=tex" alt="">
     <img src="https://img.shields.io/github/languages/count/RQF7/proyecto_lovelace.svg?style=flat-square&label=N%C3%BAmero+de+lenguajes"/>
  </a>
  <a href="https://github.com/RQF7/proyecto_lovelace/search?l=tex" alt="">
     <img src="https://img.shields.io/github/languages/top/RQF7/proyecto_lovelace.svg?style=flat-square&colorB=ff8024"/>
  </a>
</p>

<p align="center">
  ESCOM IPN, trabajo terminal 2017-B008:
  Generación de tokens para proteger los datos de tarjetas bancarias.
</p>

Hoy en día, es bien conocido que los datos de tarjetas bancarias son datos
sensibles y, por tanto, garantizar su privacidad, es de suma importancia. Una
solución que se ha vuelto muy popular es sustituir el dato sensible por un
token, es decir, un valor que no revela la información original.
Lamentablemente, la mayor parte de las soluciones que existen en el mercado son
muy poco claras sobre sus métodos de generación de tokens, ya que, al no
existir un estudio criptográfico formal, no hay ninguna certeza sobre la
seguridad de sus métodos. En este trabajo se analizan e implementan
diversos algoritmos para la generación de tokens.

Reporte técnico:
[reporte_tecnico.pdf](documentos_entregables/reporte_tecnico/reporte_tecnico.pdf)

Otros documentos:
[protocolo.pdf](documentos_entregables/protocolo.pdf),
[presentacion_tt_uno.pdf](documentos_entregables/presentacion_tt_uno/presentacion_tt_uno.pdf),
[presentacion_tt_dos.pdf](documentos_entregables/presentacion_tt_dos/presentacion_tt_dos.pdf),
[presentacion_rci.pdf](documentos_entregables/presentacion_rci/presentacion_rci.pdf),
[presentacion_fpe.pdf](documentos_entregables/presentacion_fpe/presentacion_fpe.pdf),
[articulo_rci.pdf](documentos_entregables/articulo_rci.pdf).

### Estructura de carpetas

* **bases_de_datos:** scripts de administración de bases de datos.
* **documentos_entregables:** LaTeX de reporte técnico, presentaciones y
  artículos.
* **fuentes_bibliograficas:** registro de publicaciones consultadas.
  * **iacr:** artículos de la IACR y parecidos.
  * **pci_y_nist** recomendaciones y estándares del PCI SSC y del NIST.
* **implementaciones:** programas de C++ con implementaciones de algoritmos
  tokenizadores.
* **sistema_tokenizador:** aplicación web de sistema tokenizador
  (Django + Angularjs)
* **tienda:** ejemplo de tienda en línea que consume el servicio dado
  por *sistema_tokenizador*.
* **travis:** scripts asociados a la fase de ejecución de pruebas en Travis.
* **utilidades:** contendor de código genérico: estructuras de datos de
  implementaciones (C++); toma de capturas de aplicaciones web (Selenium);
  peticiones de demostración de sistema_tokenizador (Postman); estilos de
  documentación de Doxygen.
