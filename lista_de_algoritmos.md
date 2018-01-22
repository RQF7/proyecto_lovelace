# Lista de posibles algoritmos tokenizadores

## A Cryptographic Study of Tokenization Systems

### TKR1

Tokenización a través de cifrados que preservan el formato. No se necesita una
base de datos para guardar las PAN originales. El algoritmo de cifrado recibe
el número de tarjeta, la información asociada y la llave y regresa un token
(el PAN cifrado). El algoritmo de descifrado recibe el token, la llave y la
información asociada, y regresa el PAN.

### TKR2

Esta construcción usa una primitiva RN(k) que regresa un elemento aleatorio
del espacio de tokens. Necesita de una base de datos para almacenar la
relación entre PANs y tokens. El algoritmo de cifrado recibe el número de
tarjeta y la información asociada; busca en la base de datos un registro
existente de los datos dados, si no existe, genera un token aleatorio y lo
ingresa en la base, si sí existe, es este el que regresa. El procedimiento
de descifrado es solamente una búsqueda en la base de datos.

**DUDA:** ¿Para qué sirve la llave que recibe RN?

### TKR2a

Es una modificación sobre TKR2 para cifrar el contenido de la base de datos y
así alcanzar mayor seguridad (en TKR2, cualquiera con acceso a la base puede
robar PANs). En la base sólo se guardan pares: el PAN cifrado y el token
cifrado. La información asociada se introduce en el mecanismo cifrador. Para
generar tokens, se cifra el PAN dado y se busca en la base; si no existe, se
genera un token aleatorio, se cifra y se guarda en la base; si sí existe, se
descifra el token y se regresa. Para descifrar, se cifra el token dado, se
busca en la base de datos, se descifra el PAN resultado de la búsqueda y se
regresa.
