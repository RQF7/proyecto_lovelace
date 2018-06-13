"""
  configuraciones.py Archivo de configuraciones de django.
  Proyecto Lovelace.

  Documentación asociada:
  https://docs.djangoproject.com/en/2.0/topics/settings/
  https://docs.djangoproject.com/en/2.0/ref/settings/
"""

import os

# Configuraciones generales ###################################################

BASE_DIR = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
SECRET_KEY = 'pdm$49m@g!kedc&f!t+tem!hex-t4p^3+id(4v354lmog3su0c'
DEBUG = True
ALLOWED_HOSTS = [
  "rqf7",
  "127.0.0.1"
]

# Definición de aplicaciones ##################################################

INSTALLED_APPS = [
  'sistema_tokenizador.programa_tokenizador.configuracion.Configuracion',
  'django.contrib.admin',
  'django.contrib.auth',
  'django.contrib.contenttypes',
  'django.contrib.sessions',
  'django.contrib.messages',
  'django.contrib.staticfiles'
]

MIDDLEWARE = [
  'django.middleware.security.SecurityMiddleware',
  'django.contrib.sessions.middleware.SessionMiddleware',
  'django.middleware.common.CommonMiddleware',
  'django.middleware.csrf.CsrfViewMiddleware',
  'django.contrib.auth.middleware.AuthenticationMiddleware',
  'django.contrib.messages.middleware.MessageMiddleware',
  'django.middleware.clickjacking.XFrameOptionsMiddleware',
]

ROOT_URLCONF = 'sistema_tokenizador.direcciones'

TEMPLATES = [
  {
    'BACKEND': 'django.template.backends.django.DjangoTemplates',
    'DIRS': [],
    'APP_DIRS': True,
    'OPTIONS': {
      'context_processors': [
        'django.template.context_processors.debug',
        'django.template.context_processors.request',
        'django.contrib.auth.context_processors.auth',
        'django.contrib.messages.context_processors.messages',
      ],
    },
  },
]

WSGI_APPLICATION = 'sistema_tokenizador.servidor_web.aplicacion'


# Base de datos ###############################################################
# https://docs.djangoproject.com/en/2.0/ref/settings/#databases

DATABASES = {
  'default': {
    'ENGINE': 'django.db.backends.mysql',
    'NAME': 'lovelace_cdv',
    'USER': 'administrador_lovelace_cdv',
    'PASSWORD': 'l0v3lac3-admin',
    'HOST': 'localhost',
    'OPTIONS' : {
      'init_command': "SET sql_mode='STRICT_ALL_TABLES'"
    }
  }
}


# Validación de contraseñas ###################################################
# https://docs.djangoproject.com/en/2.0/ref/settings/#auth-password-validators

#AUTH_PASSWORD_VALIDATORS = [
#  {
#    'NAME':
#    'django.contrib.auth.password_validation.UserAttributeSimilarityValidator',
#  },
#  {
#    'NAME': 'django.contrib.auth.password_validation.MinimumLengthValidator',
#  },
#  {
#    'NAME': 'django.contrib.auth.password_validation.CommonPasswordValidator',
#  },
#  {
#    'NAME': 'django.contrib.auth.password_validation.NumericPasswordValidator',
#  },
#]


# Internacionalización ########################################################
# https://docs.djangoproject.com/en/2.0/topics/i18n/

LANGUAGE_CODE = 'es-mx'
TIME_ZONE = 'America/Mexico_City'
USE_I18N = True
USE_L10N = True
USE_TZ = True


# Archivos estaticos ##########################################################
# https://docs.djangoproject.com/en/2.0/howto/static-files/

# Dirección en donde se copian todos los archivos estáticos
# &python administrar.py collectstatic
STATIC_ROOT = os.path.join(BASE_DIR, 'archivos_estaticos')

STATIC_URL = '/estaticos/'
STATICFILES_DIRS = [
  os.path.join(BASE_DIR, 'sistema_tokenizador/archivos_cliente/compilados')
]

# En teoría, para desactivar la caché en esta versión de desarrollo
CACHES = {
  'default': {
    'BACKEND': 'django.core.cache.backends.dummy.DummyCache',
  }
}
