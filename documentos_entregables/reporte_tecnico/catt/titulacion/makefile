
CARPETA_DE_TEMPORALES := temporales_de_latex
COMPILACION           := latexmk \
		-pdf \
		-pdflatex=" \
	    xelatex \
				-halt-on-error \
				-shell-escape \
				--output-dir $(CARPETA_DE_TEMPORALES)" \
		-auxdir=$(CARPETA_DE_TEMPORALES) \
	  -outdir=$(CARPETA_DE_TEMPORALES)

empastado:
	make empastado_interno
	fswatch -1 $@.tex
	make empastado

empastado_interno:
	mkdir -p $(CARPETA_DE_TEMPORALES)
	$(COMPILACION) empastado.tex

lomo:
	make lomo_interno
	fswatch -1 $@.tex
	make lomo

lomo_interno:
	mkdir -p $(CARPETA_DE_TEMPORALES)
	$(COMPILACION) lomo.tex

documento:
	make documento_interno
	fswatch -1 $@.tex
	make documento

documento_interno:
	mkdir -p $(CARPETA_DE_TEMPORALES)
	$(COMPILACION) documento.tex
