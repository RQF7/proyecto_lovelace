# Carpeta de documentos entregables

## Sobre hunspell y el archivo de diccionario

[Hunspell](https://github.com/hunspell/hunspell) es un analizador de
ortografía. La idea es que nuestro modelo de distribución continua también
valide esto antes de emitir un resultado sobre el estado del proyecto. Travis
ejecutará el objetivo **ortografía** del [makefile](makefile); si hunspell y
el [script de python evaluador](evaluador.py) no reportan errores, se continúa
con la fase de construcción, si sí hay errores, el estado de la construcción
pasa a *fallido* (Travis manda correos a todos los interesados, y el ícono
del [README principal](../README.md) se pone en rojo).

En el [archivo de diccionario](diccionario.txt) se especifican las excepciones:
palabras en otros idiomas, tecnicismos, omisiones del diccionario, etc. Los
prefijos para esta especificación son:

* `*`: Agergar al diccionario.
* `@`: Aceptar palabra, pero dejar fuera de diccionario.
