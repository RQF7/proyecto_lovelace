#
# Compilación de documento final.
# Proyecto Lovelace.
#

NOMBRE_DE_ARCHIVO := documento_final
CARPETA_TEMPORAL := temporales_de_latex
UBICACION_CONTENIDO := **/**/*.tex **/**/**/*.tex

$(NOMBRE_DE_ARCHIVO): $(NOMBRE_DE_ARCHIVO).tex $(UBICACION_CONTENIDO)
	mkdir -p $(CARPETA_TEMPORAL)
	pdflatex -halt-on-error -file-line-error --output-dir $(CARPETA_TEMPORAL) $<
	mv $(CARPETA_TEMPORAL)/$@.pdf ./

# Es necesario tener el ejecutable de biber en el PATH.
# Si se agregan referencias, generalmente hay que compilar con pdflatex, luego
# ejecutar biber, y después volver a compilar con pdflatex.
# Si biber marca error (luego se vuelve medio loco), es más fácil borrar la
# carpeta de temporales y volver a empezar.

referencias:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(NOMBRE_DE_ARCHIVO).bcf

# Es necesario tener el ejecutable de hunspell en el PATH, y el diccionario
# es_MX instalado. Este comando (ortografía) es ejecutado por Travis para
# validar un push, si lo que se quiere es ejecutar de manera local, es más
# apropiado el modo interactivo
# (hunspell -d es_MX -t diccionario.txt {nombre_de_archivo.tex}).

ortografía:
	hunspell -a -d es_MX -t diccionario.txt $(NOMBRE_DE_ARCHIVO).tex \
		$(UBICACION_CONTENIDO) | ./evaluador.py
