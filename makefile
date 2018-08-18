#
# Tareas genéricas del repositorio.
# Proyecto Lovelace.
#

sitio_local:
	bundle exec jekyll serve

documentación_doxygen:
	doxygen .doxygen


# Toma de capturas de pantalla para reporte técnico.
# OJO: evidentemente, para que esto funcione, el sitio debe
# estar disponible en el dominio dado (el servidor de pruebas
# de django debe de estar corriendo).

# TODO:
# Agregar archivos de sass a las dependencias de los objetivos.

CARPETA_IMAGENES     := documentos_entregables/reporte_tecnico/contenidos/analisis_y_disenio_api_web/analisis/capturas
CARPETA_FUENTES      := sistema_tokenizador/archivos_web
LISTA_DE_FUENTES     := inicio_1920x1080.png \
	                      documentacion_1920x1080.png \
												iniciar_sesion_1920x1080.png
LISTA_DE_OBJETOS     := $(addprefix $(CARPETA_IMAGENES)/, \
	                      $(LISTA_DE_FUENTES))
DEPENDENCIAS_COMUNES := index.html \
												js/configuraciones/tema.configuracion.js
SCRIPTS_CAPTURAS     := utilidades/capturas_selenium
DOMINIO 						 := http://127.0.0.1:8080

# Las fuentes están todas en los archivos web
VPATH := $(CARPETA_FUENTES)

toma_de_capturas: $(LISTA_DE_OBJETOS)
	@echo "Toma de capturas lista"

$(CARPETA_IMAGENES)/inicio_1920x1080.png: \
		html/inicio.html \
		$(DEPENDENCIAS_COMUNES)
	python $(SCRIPTS_CAPTURAS)/inicio.py $(DOMINIO)/ $@

$(CARPETA_IMAGENES)/documentacion_1920x1080.png: \
		html/documentacion.html \
		$(DEPENDENCIAS_COMUNES)
	python $(SCRIPTS_CAPTURAS)/documentacion.py $(DOMINIO)/documentación $@

$(CARPETA_IMAGENES)/iniciar_sesion_1920x1080.png: \
		html/ventanas/iniciar_sesion.ventana.html \
		$(DEPENDENCIAS_COMUNES)
	python $(SCRIPTS_CAPTURAS)/iniciar_sesion.py $(DOMINIO)/ $@
