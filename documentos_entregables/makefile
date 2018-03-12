#
# Compilación de documentos entregables.
# Proyecto Lovelace.
#

CARPETA_TEMPORAL 					:= temporales_de_latex

# Documento final #############################################################

DOCUMENTO_FINAL 					:= reporte_tecnico
CARPETA_DOCUMENTO_FINAL 	:= reporte_tecnico

$(DOCUMENTO_FINAL): \
		$(CARPETA_DOCUMENTO_FINAL)/$(DOCUMENTO_FINAL).tex
	mkdir -p $(CARPETA_TEMPORAL)
	pdflatex -halt-on-error -file-line-error --output-dir $(CARPETA_TEMPORAL) $<
	mv $(CARPETA_TEMPORAL)/$@.pdf ./$(CARPETA_DOCUMENTO_FINAL)/

# Es necesario tener el ejecutable de biber en el PATH.
# Si se agregan referencias, generalmente hay que compilar con pdflatex, luego
# ejecutar biber, y después volver a compilar con pdflatex.
# Si biber marca error (luego se vuelve medio loco), es más fácil borrar la
# carpeta de temporales y volver a empezar.

referencias:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(DOCUMENTO_FINAL).bcf

# Al igual que biber, si se modifican las entradas del glosario hay que hacer
# operación sandwich: pdflatex, makeglossaries, pdflatex.

glosarios:
	makeglossaries -d $(CARPETA_TEMPORAL) $(DOCUMENTO_FINAL)


# Presentación FPE ###########################################################

PRESENTACION_FPE 					:= presentacion_fpe
CARPETA_PRESENTACION_FPE 	:= presentacion_fpe

$(PRESENTACION_FPE): \
		$(CARPETA_PRESENTACION_FPE)/$(PRESENTACION_FPE).tex
	mkdir -p $(CARPETA_TEMPORAL)
	pdflatex -halt-on-error -file-line-error --output-dir $(CARPETA_TEMPORAL) $<
	mv $(CARPETA_TEMPORAL)/$@.pdf ./$(CARPETA_PRESENTACION_FPE)/

referencias_fpe:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(PRESENTACION_FPE).bcf

# Es necesario tener el ejecutable de hunspell en el PATH, y el diccionario
# es_MX instalado. Este comando (ortografía) es ejecutado por Travis para
# validar un push, si lo que se quiere es ejecutar de manera local, es más
# apropiado el modo interactivo
# (hunspell -d es_MX -t diccionario.txt {nombre_de_archivo.tex}).

ortografía:
	hunspell -a -d es_MX -t diccionario.txt $(NOMBRE_DE_ARCHIVO).tex \
		$(UBICACION_CONTENIDO) | ./evaluador.py
	#hunspell -a -d es_MX -t diccionario.txt *.md ../*.md | ./evaluador.py

limpiar:
	rm -Rfv $(CARPETA_TEMPORAL)
