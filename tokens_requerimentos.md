# Requerimientos de los Tokens:

--------------------------------------------------------------------------------

## Tokens Irreversibles 

* El algoritmo o mecanismo generador de tokens debe de ser probabilisticamente 
irreversible.
* El token no debe contener ninguna parte del PAN original que representa.
* La creación de un diccionario de tokens debe ser inviable, teniendo en cuenta 
que la probabilidad de adivinar un token tiene que ser menor a 1/10^6
* Al usar un token para autenticación, el proceso no debe de filtrar información 
con la cual se pueda analizar el PAN que representa.
* La llave usada en el proceso de tokenización debe seguir un ciclo de vida 
descrito en el ISO/IEC 11568-1.

--------------------------------------------------------------------------------

## Tokens Criptográficos Reversibles

* El manejo de las llaves para la tokenización deben ser seguro, incluyendo que: 
no se puedan exportar en claro las llaves, que estas no tengan ningún otro uso 
mas que generar tokens, y que todas las llaves hayan sido generadas por lo menos 
con 128 bit de entropía.
* La probabilidad de adivinar el PAN original de un token debe ser menor a 
1/10^6, no se deben de tener maneras de sufrir un ataque estadístico.
* Se debe garantizar que el proceso de tokenización puede verse como un conjunto 
de permutaciones aleatorias en el espacio de tokens. 
* Al cambiar tanto la llave como el PAN en claro, debe de cambiar el 
*token mapping*.
* No se tiene que almacenar parte del PAN original en el mismo sistema en el que 
se almacenan los tokens.
* El tamaño de las llaves para la tokenización debe ser minimo de 128 bits, 
además de ser estadísticamente independientes entre si.

--------------------------------------------------------------------------------

## Tokens No-Criptográficos Reversibles

* La generación de un token debe ser independiente del PAN que representa y la 
relación PAN/Token solo se debe almacenar en el *Card Data Vault*.
* Si se usan varias *Card Data Vault* estas deben de ser independientes 
estadísticamente.
* La probabilidad de adivinar el PAN original de un token debe ser menor a 
1/10^6, no se deben de tener maneras de sufrir un ataque estadístico.
* Se debe garantizar que el proceso de tokenización puede verse como un conjunto 
de permutaciones aleatorias en el espacio de tokens. 
* Al cambiar tanto la llave como el PAN en claro, debe de cambiar el 
*token mapping*, además de que en el proceso de tokenización se deben de 
incluir parámetros que al ser modificados se produzca igualmente un un cambio 
en el *token mapping*.
* Se debe de garantizar que la probabilidad de encontrar cualquier relación 
PAN/Token es la misma.

--------------------------------------------------------------------------------

## Requerimientos para el sistema de tokenización

* El sistema de tokenización no debe de proporcionar PANs a ninguna solicitud 
externa que no esté definida en el mismo entorno del sistema.
* Todos los componentes del proceso de tokenización deben de estar en redes 
internas y aisladas de redes inseguras.
* Se establece que la comunicación segura solo se encuentra dentro del entorno 
del sistema de tokenización.
* El sistema de tokenización tiene que usar criptografía y protocolos de 
seguridad para proteger los datos que se encuentran almacenados y los que se 
transmiten.
* El sistema debe implementar controles de acceso y autenticación.
* El sistema debe estar diseñado siguiendo estándares de configuración y estar 
protegido contra vulnerabilidades.
* Se deben de tener mecanismos para la eliminación de los datos almacenados.
* Se deben llevar a cabo el registro, monitoreo y alertas para identificar 
actividades sospechosas.

--------------------------------------------------------------------------------
