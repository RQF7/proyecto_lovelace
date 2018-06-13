#!/usr/bin/env python
#coding: utf-8
"""
  Script para interactuar con el módulo ejecutable de django.
  Proyecto Lovelace.
"""

import os
import sys

if __name__ == "__main__":

  os.environ.setdefault("DJANGO_SETTINGS_MODULE",
      "sistema_tokenizador.configuraciones")

  from django.core.management import execute_from_command_line as ejecutar
  ejecutar(sys.argv)
