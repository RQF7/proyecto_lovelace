"""
servidor_web.py Archivo de configuraciones de de interfaz WSGI.
Sistema tokenizador.
Proyecto Lovelace.
"""

import os
import sys

sys.path.insert(0, os.path.abspath(os.path.join(
  os.path.dirname(__file__), "../")))

os.environ["DJANGO_SETTINGS_MODULE"] = "sistema_tokenizador.configuraciones"

from django.core.wsgi import get_wsgi_application
application = get_wsgi_application()
