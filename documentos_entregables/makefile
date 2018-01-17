#
# Compilación de documento final.
# Proyecto Lovelace.
#

NOMBRE_DE_ARCHIVO := documento_final
CARPETA_TEMPORAL := temporales_de_latex

$(NOMBRE_DE_ARCHIVO): $(NOMBRE_DE_ARCHIVO).tex **/*.tex
	mkdir -p $(CARPETA_TEMPORAL)
	pdflatex --shell-escape --output-dir $(CARPETA_TEMPORAL) $<
	mv $(CARPETA_TEMPORAL)/$@.pdf ./
