"""
  servidor_web.py Archivo de configuraciones de de interfaz WSGI.
  Proyecto Lovelace.
"""

import os, sys

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), "../")))

os.environ["DJANGO_SETTINGS_MODULE"] = "sistema_tokenizador.configuraciones"
#os.environ.setdefault("DJANGO_SETTINGS_MODULE",
#  "sistema_tokenizador.configuraciones")

from django.core.wsgi import get_wsgi_application

application = get_wsgi_application()
