# Sobre el dígito verificador en el PAN

Aclaración sobre lo que pasa con el tamaño del espacio de mensajes cuando se
toma en cuenta al dígito verificador:

El tamaño del espacio de mensaje sí se ve afectado de una manera uniforme por
la presencia del dígito verificador. En otras palabras, dado que la cardinalidad
del alfabeto es 10, el tamaño del espacio de mensajes es un décimo más pequeño.
Si se piensa en los 16 dígitos de un número de tarjeta normal, el tamaño del
conjunto de mensajes es `10^16`, sin embargo, entre todos esos hay muchos que
no tienen un código de Luhn válido; en particular, solo un décimo (`(10^16) /
10`, esto es `10^15`) son números de tarjeta correctos.

### Explicación

Para entenderlo, se puede considerar un espacio mucho más pequeño: solo 3
dígitos; el tamaño del conjunto es `1000` (`10^3`). Ahora se puede considerar
un caso específico con los primeros dos dígitos fijos (`00`):
```
000
001
002
003
004
005
006
007
008
009
```
En condiciones normales estas serían las 10 posibles permutaciones para una base
de `00`; sin embargo, al introducir el dígito verificador, *solo una* de estas
10 es válida (el último paso del algoritmo es una operación módulo la
cardinalidad). Lo mismo ocurre para todas las demas bases de dos dígitos: el
tercero es único (distinto según cada caso particular). Visto como árbol de
permutaciones, el primer y el segundo dígito aportan 10 posibilidades, sin
embargo el tercero sólo aporta una (`10 * 10 * 1`).
