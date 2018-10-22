"""
Funciones comunes de backend,
Tienda en línea.
Proyecto Lovelace.
"""

import django
import email
import functools
import smtplib
import _thread


def respuestaJSON (objeto):
  """Empaqueta el objeto dado como una respuesta HTTP con JSON.

  Ocupa los serializadores de django, que solo están pensados para los propios
  modelos de django; si se quiere serializar algo externo, mejor ocupar
  json.dumps.

  OJO: si el objeto dado no es iterable, es convertido a una lista
  con un solo elemento, para que sea posible serializarlo."""
  try:
    iterador = iter(objeto)
  except TypeError:
    objeto = [objeto]
  return django.http.HttpResponse(
    django.core.serializers.serialize("json", objeto))


def privilegiosRequeridos (funcion):
  """Decorador de privilegios.

  Valida que haya un registro de usuario en las variables de sesión."""
  
  @functools.wraps(funcion)
  def envolturaDePrivilegios(peticion, *argumentos, **argumentosEnDiccionario):
    if 'usuario' not in peticion.session:
      return django.http.HttpResponseForbidden()
    else:
      return funcion(peticion, *argumentos, **argumentosEnDiccionario)

  return envolturaDePrivilegios


def enviarCorreo (destinatario, asunto, cuerpo):
  """Envolvente alededor de transacciones de correo

  La función opera en modo no bloqueante: crea un hilo para hacer la
  transacción del envío del correo y regresa, independientemente de
  si el envío fue o no correcto.

  destinatario: cadena con correo destino.
  asunto: cadena con campo de subject en correo.
  cuerpo: contenido del correo."""
  _thread.start_new_thread(transaccionDeCorreo, (destinatario, asunto, cuerpo))


def transaccionDeCorreo (destinatario, asunto, cuerpo):
  """Envía un correo desde la cuenta de administración del servidor.

  destinatario: cadena con correo destino.
  asunto: cadena con campo de subject en correo.
  cuerpo: contenido del correo.

  TODO: Quitar contraseña de aquí."""
  dominio = 'ricardo-quezada.159.65.96.59.xip.io'
  usuario = 'administracion'
  correo = usuario + '@' + dominio
  servidor = smtplib.SMTP(dominio, 587)
  servidor.ehlo()
  servidor.starttls()
  servidor.ehlo()
  servidor.login(
    correo,
    'config-1321-admin')
  mensaje = email.mime.text.MIMEText(cuerpo.encode('utf-8'), _charset='utf-8')
  mensaje['Subject'] = asunto
  mensaje['From'] = correo
  mensaje['To'] = destinatario
  servidor.sendmail(
    correo,
    [destinatario],
    mensaje.as_string())
  servidor.close()


def calcularAlgoritmoLuhn (arreglo):
  """Cálculo de dígito de verificación.

  Calcula el valor del digito verificador mediante el algoritmo de Luhn.
  No toma en cuenta el último elemento del arreglo."""

  suma = 0
  i = len(arreglo) - 2
  j = 0

  while i >= 0:

    if (j % 2) == 0:
      suma = suma + ((int(arreglo[i]) * 2) % 10) + (int(arreglo[i]) * 2 // 10)
    else:
      suma = suma + int(arreglo[i])

    i = i - 1
    j = j + 1

  return (suma * 9) % 10
