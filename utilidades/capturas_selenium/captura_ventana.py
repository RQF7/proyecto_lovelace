"""
Clase genérica para pantallas que requieren presionar un botón para abrir una
ventana justo después del inicio de sesión.
Proyecto Lovelace.
"""

import time
from captura_con_sesion import CapturaConSesion

class CapturaVentana (CapturaConSesion):
  """Clase para formularios después de incio de sesión.

  Sobreescribe a CapturaConSesion. Después de la configuración definida por
  la superclase, busca el botón por el identificador dado y abre la ventana.
  """

  def __init__ (ego, urlInicial, rutaArchivo, correo,
    contrasenia, urlFinal, idDeBoton):
    """Constructor de clase.

    Además de los parámetros que necesita la captura con sesión agrega el
    identificador del botón a presionar.
    """

    CapturaConSesion.__init__(ego, urlInicial, rutaArchivo, correo,
      contrasenia, urlFinal)
    ego.mIdDeBoton = idDeBoton


  def configuracionCapturaExtraGrande (ego):
    """Configuración inicial.

    Llama a la cadena de configuraciones de las superclases; solo por fines
    ilustrativos, esa cadena es:
    * CapturaVentana
    * CapturaConSesion
    * CapturaGenericaPagina
    * Captura Generica

    Después de esto abre la ventana dada.

    TODO: no depender del tiempo.
    """
    CapturaConSesion.configuracionCapturaExtraGrande(ego)
    boton = ego.mNavegador.find_element_by_id(ego.mIdDeBoton)
    boton.click()
    time.sleep(0.5)
