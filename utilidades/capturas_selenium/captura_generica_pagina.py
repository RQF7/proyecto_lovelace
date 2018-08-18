"""
  Clase genérica para toma de capturas de páginas principales.
  Proyecto Lovelace.
"""

import time
from captura_generica import CapturaGenerica

class CapturaGenericaPagina (CapturaGenerica):
  """
  Clase genérica para toma de capturas de páginas principales.

  Esta clase abarca a todas las capturas que van directo sobre la
  url del navegador. Una vez quela instancia de selenium entra a la url, no se
  necesitan mayores configuraciones para la toma de capturas.
  """

  def configuracionCapturaMediana (ego):
    """
    Extiende la configuración de la captura genérica.

    Agrega un intervalo entre el cambio de tamaño de ventata y la toma de
    captura en el caso de la configuración de la captura de tamaño medio.
    Esto para que le de tiempo al js de ocultar la barra de navegación lateral.

    TODO: hacer que el delay no esté basado en el tiempo, sino en consultas
    directas sobre el estado del css.
    """
    CapturaGenerica.configuracionCapturaMediana(ego)
    time.sleep(0.5)
