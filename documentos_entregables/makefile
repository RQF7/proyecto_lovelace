#
# Compilación de documentos entregables.
# Proyecto Lovelace.
#

CARPETA_TEMPORAL 					:= temporales_de_latex

# Reporte técnico ##############################################################

REPORTE_TECNICO 					  := reporte_tecnico
CARPETA_REPORTE_TECNICO 	  := reporte_tecnico
FUENTES_REPORTE_TECNICO     := \
	$(shell find reporte_tecnico/ -type f -name '*.tex' -o -name '*.sty')

COMPILACION_REPORTE_TECNICO := pdflatex -shell-escape \
	-halt-on-error -file-line-error \
	--output-dir $(CARPETA_TEMPORAL) \
	$(CARPETA_REPORTE_TECNICO)/$(REPORTE_TECNICO).tex

CONDICION_DE_REFERENCIAS		:= \
	$(shell grep "Please (re)run Biber" salida.temporal)

$(CARPETA_REPORTE_TECNICO)/$(REPORTE_TECNICO).pdf: $(FUENTES_REPORTE_TECNICO)
	mkdir -p $(CARPETA_TEMPORAL)
	$(COMPILACION_REPORTE_TECNICO) | tee salida.temporal
	@if grep "has been referenced but does not exist" salida.temporal; then\
	  make glosarios;\
		$(COMPILACION_REPORTE_TECNICO) | tee salida.temporal;\
	else\
		echo "El glosario está al día.";\
	fi
	@if grep "Please (re)run Biber" salida.temporal; then\
		make referencias;\
		$(COMPILACION_REPORTE_TECNICO) | tee salida.temporal;\
	else\
		echo "La bibliografía están al día.";\
	fi
	@if grep "Rerun to get cross-references right" salida.temporal; then\
		$(COMPILACION_REPORTE_TECNICO) | tee salida.temporal;\
	else\
		echo "Las referencias están al día.";\
	fi
	rm salida.temporal
	mv $(CARPETA_TEMPORAL)/$(REPORTE_TECNICO).pdf ./$(CARPETA_REPORTE_TECNICO)/

# Es necesario tener el ejecutable de biber en el PATH.
# Si se agregan referencias, generalmente hay que compilar con pdflatex, luego
# ejecutar biber, y después volver a compilar con pdflatex.
# Si biber marca error (luego se vuelve medio loco), es más fácil borrar la
# carpeta de temporales y volver a empezar.

referencias:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(REPORTE_TECNICO).bcf

# Al igual que biber, si se modifican las entradas del glosario hay que hacer
# operación sandwich: pdflatex, makeglossaries, pdflatex.

glosarios:
	makeglossaries -d $(CARPETA_TEMPORAL) $(REPORTE_TECNICO)


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

# Presentación TT! ###########################################################

PRESENTACION_TT1 					:= presentacion_tt_uno
CARPETA_PRESENTACION_TT1 	:= presentacion_tt_uno

$(PRESENTACION_TT1): \
		$(CARPETA_PRESENTACION_TT1)/$(PRESENTACION_TT1).tex
	mkdir -p $(CARPETA_TEMPORAL)
	pdflatex -halt-on-error -file-line-error --output-dir $(CARPETA_TEMPORAL) $<
	mv $(CARPETA_TEMPORAL)/$@.pdf ./$(CARPETA_PRESENTACION_TT1)/

referencias_tt1:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(PRESENTACION_TT1).bcf

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
