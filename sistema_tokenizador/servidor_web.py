"""
  servidor_web.py Archivo de configuraciones de de interfaz WSGI.
  Proyecto Lovelace.
"""

import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE",
  "sistema_tokenizador.configuraciones")

from django.core.wsgi import get_wsgi_application

aplicacion = get_wsgi_application()
