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

## Fuentes varias

### Pseudo random number generator (PRNG)

Estos algoritmos funcionan con un estado interno, una llave secreta
y semilla. Cuando se genera un dato aleatorio, el algoritmo 
utiliza la semilla y la llave para producir una salida pseudoaleatoria.
El estado interno se actualiza para que la siguiente petición tenga
una salida distinta. 

Existen dos  tipos, los determinísticos y no determinísticos. Los 
primeros dependen de un valor inicial llamado semilla; los segundos
dependen de una fuente física impredecible. Hasta el 2015, no hay 
RNG no determinísticos aprobados por FIPS.

https://www.cryptosys.net/rng_algorithms.html

### OWHF
Utilizar estas funciones hash da más flexibilidad y afectan menos el 
desempeño que cuando se obtienen los tokens por cifrado.

Entendiendo y seleccionando una solución de tokenización - Securosis

### Format Preserving Encryption (FPE)

#### FPE con un cifrado prefijo
Para el caso de las tarjetas bancarias, como el PAN está compuesto entre 
13 y 19 dígitos, se cifra cada elemento {0, 1, 2, ..., 9} y se le asigna
como peso. Posteriormente, se acomodan respecto al peso y se obtiene una
tabla de consulta. O sea:

AES(0, k) = numerote_9 
AES(1, k) = numerote_5
AES(2, k) = numerote_0 
...
AES(9, k) = numerote_2

Entonces la función tokenizadora queda:
F(0) = 9
F(1) = 5
F(2) = 0
...
F(9) = 2

Por lo que, el token para 00291 queda 99025

### Tokenization algorithm of Reversible Hybrid type
Este algoritmo utiliza una entrada extra de manera que se pueden tener 
distintos tokens correspondientes correspondientes al mismo PAN. 
Necesita una base de datos segura que contiene la tabla de consulta con 
los pares PAN - token.

Primero se ingresa el PAN y la entrada extra a una función pública que
regresa una cadena de n bits. Donde n es el tamaño de bloque que utiliza
el algoritmo cifrador que se va a utilizar. La función f puede ser una 
función hash criptográfca. Posteriormente, se cifra el la cadena de bits
obtenida de con la función hash y se verifica que el valor sea 
<<válido>>. Si lo es, crea el token y revisa si está en la base de 
datos. Si ya existe, aumenta en uno la entrada extra y regresa al 
inicio. Si no existe en la base de datos, regresa el token nuevo.

Varias pruebas de seguridad para un algoritmo tokenizador 
- Longo, Aragona y Sala.
