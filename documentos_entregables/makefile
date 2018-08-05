#
# Compilación de documentos entregables.
# Proyecto Lovelace.
#

CARPETA_TEMPORAL 					:= temporales_de_latex
COMPILACION 							:= pdflatex -shell-escape \
														 -halt-on-error -file-line-error \
	                           --output-dir $(CARPETA_TEMPORAL)

# Reporte técnico ##############################################################

REPORTE_TECNICO 					  := reporte_tecnico
CARPETA_REPORTE_TECNICO 	  := reporte_tecnico
FUENTES_REPORTE_TECNICO     := \
	$(shell find reporte_tecnico/ -type f -name '*.tex' -o -name '*.sty')
COMPILACION_REPORTE_TECNICO := $(COMPILACION) \
	$(CARPETA_REPORTE_TECNICO)/$(REPORTE_TECNICO).tex

$(CARPETA_REPORTE_TECNICO)/$(REPORTE_TECNICO).pdf: $(FUENTES_REPORTE_TECNICO) \
																									 referencias.bib
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
		echo "La bibliografía está al día.";\
	fi
	@if grep "Rerun to get cross-references right" salida.temporal; then\
		$(COMPILACION_REPORTE_TECNICO) | tee salida.temporal;\
	else\
		echo "Las referencias están al día.";\
	fi
	rm -f salida.temporal
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
# operación sándwich: pdflatex, makeglossaries, pdflatex.

glosarios:
	makeglossaries -d $(CARPETA_TEMPORAL) $(REPORTE_TECNICO)


# Presentación FPE ###########################################################

PRESENTACION_FPE 					:= presentacion_fpe
CARPETA_PRESENTACION_FPE 	:= presentacion_fpe
FUENTES_PRESENTACION_FPE     := \
	$(shell find presentacion_fpe/ -type f -name '*.tex' -o -name '*.sty')
COMPILACION_PRESENTACION_FPE := $(COMPILACION) \
	$(CARPETA_PRESENTACION_FPE)/$(PRESENTACION_FPE).tex

$(CARPETA_PRESENTACION_FPE)/$(PRESENTACION_FPE).pdf: $(FUENTES_PRESENTACION_FPE)
	mkdir -p $(CARPETA_TEMPORAL)
	$(COMPILACION_PRESENTACION_FPE) | tee salida.temporal
	@if grep "Please (re)run Biber" salida.temporal; then\
		make referencias_fpe;\
		$(COMPILACION_PRESENTACION_FPE) | tee salida.temporal;\
	else\
		echo "La bibliografía están al día.";\
	fi
	rm -f salida.temporal
	mv $(CARPETA_TEMPORAL)/$(PRESENTACION_FPE).pdf ./$(CARPETA_PRESENTACION_FPE)/

referencias_fpe:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(PRESENTACION_FPE).bcf

# Presentación TT! ###########################################################

PRESENTACION_TT1 					:= presentacion_tt_uno
CARPETA_PRESENTACION_TT1 	:= presentacion_tt_uno
FUENTES_PRESENTACION_TT1  := \
	$(shell find presentacion_tt_uno/ -type f -name '*.tex' -o -name '*.sty')
COMPILACION_PRESENTACION_TT1 := $(COMPILACION) \
	$(CARPETA_PRESENTACION_TT1)/$(PRESENTACION_TT1).tex

$(CARPETA_PRESENTACION_TT1)/$(PRESENTACION_TT1).pdf: $(FUENTES_PRESENTACION_TT1)
	mkdir -p $(CARPETA_TEMPORAL)
	$(COMPILACION_PRESENTACION_TT1) | tee salida.temporal
	@if grep "Please (re)run Biber" salida.temporal; then\
		make referencias_tt1;\
		$(COMPILACION_PRESENTACION_TT1) | tee salida.temporal;\
	else\
		echo "La bibliografía están al día.";\
	fi
	rm -f salida.temporal
	mv $(CARPETA_TEMPORAL)/$(PRESENTACION_TT1).pdf ./$(CARPETA_PRESENTACION_TT1)/

referencias_tt1:
	biber --input-directory $(CARPETA_TEMPORAL) \
		$(CARPETA_TEMPORAL)/$(PRESENTACION_TT1).bcf

# Articulo ################################################################

ARTICULO 									:= articulo
CARPETA_ARTICULO 	        := articulo
FUENTES_ARTICULO          := \
	$(shell find articulo/ -type f -name '*.tex' -o -name '*.sty')
COMPILACION_ARTICULO := $(COMPILACION) \
	$(CARPETA_ARTICULO)/$(ARTICULO).tex

$(CARPETA_ARTICULO)/$(ARTICULO).pdf: $(FUENTES_ARTICULO)
	mkdir -p $(CARPETA_TEMPORAL)
	$(COMPILACION_ARTICULO) | tee salida.temporal
	@if grep "Please (re)run Biber" salida.temporal; then\
		make referencias_articulo;\
		$(COMPILACION_ARTICULO) | tee salida.temporal;\
	else\
		echo "La bibliografía están al día.";\
	fi
	rm -f salida.temporal
	mv $(CARPETA_TEMPORAL)/$(ARTICULO).pdf ./$(CARPETA_ARTICULO)/

referencias_articulo:
	bibtex $(CARPETA_TEMPORAL)/$(ARTICULO).aux

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
