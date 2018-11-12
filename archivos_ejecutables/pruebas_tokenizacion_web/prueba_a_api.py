"""
Pruebas de tokenización y detokenización con peticiones
al sistema tokenizador.
Proyecto Lovelace.
"""

"""
Ayudantes:
  delete from programa_tokenizador_token;
  update general_usuario
  set contadorDeMalasAcciones=0, estadoDeUsuario_id='aprobado'
  where correo_id='administracion@tienda-en-linea.com';
"""

import requests, json, time

################ Clase de conexión con el sistema tokenizador #################

class STConector:
  #----------------------------------------------------------------------------
  def __init__(self, host, usuario, contrasenia):
    self.host = host
    self.usuario = usuario
    self.contrasenia = contrasenia
    self.tokenizacion = self.host + '/api/programa_tokenizador/tokenizar'
    self.detokenizacion = self.host + '/api/programa_tokenizador/detokenizar'
    self.auth = (self.usuario, self.contrasenia)
    self.contador = 0

  #----------------------------------------------------------------------------
  def reiniciarContador(self):
    """
    Reinicia el contador de tiempo
    """
    self.contador = 0

  #----------------------------------------------------------------------------
  def obtenerContador(self):
    """
    Regresa el contador de tiempo
    """
    return self.contador

  #----------------------------------------------------------------------------
  def tokenizar (self, numeroDeTarjeta, metodo):
    """
    Realiza una petición de tokenización y cuenta el tiempo que tarda
    en llegar la respuesta
    """
    tiempo_inicial = time.time()
    peticion = requests.post(self.tokenizacion, auth = self.auth,
      data = json.dumps({'pan': numeroDeTarjeta, 'metodo': metodo}))
    tiempo_final = time.time()
    self.contador += tiempo_final - tiempo_inicial

    if peticion.status_code != 200:
      raise SystemError('Error en tokenización, operando '
        + numeroDeTarjeta + ' : ' + peticion.text)

    return peticion.text.replace('\n','')

  #----------------------------------------------------------------------------
  def detokenizar (self, token, metodo):
    """
    Realiza una petición de detokenización y cuenta el tiempo que tarda
    en llegar la respuesta
    """
    tiempo_inicial = time.time()
    peticion = requests.post(self.detokenizacion, auth = self.auth,
      data = json.dumps({'token': token, 'metodo': metodo}))
    tiempo_final = time.time()
    self.contador += tiempo_final - tiempo_inicial

    if peticion.status_code != 200:
      raise SystemError('Error en detokenización, operando '
        + token + ' : ' + peticion.text)

    return peticion.text.replace('\n','')

################################ Clase tarjeta ################################

class Tarjeta:
  """
  A lo mejor ya esta clase esta de más, pero por lo mientras así la dejo
  """
  #----------------------------------------------------------------------------
  def __init__(self, numero):
    """
    Genera un numero de tarjeta a partir de un int
    """
    tarjeta = str(numero).zfill(15)[-15:]

    x = 0
    for i in range(len(tarjeta)):
      digito = int(tarjeta[-(i+1)])
      if i % 2:
        x = x + digito
      else:
        x = x + ((digito * 2) % 10) + ((digito * 2) // 10)

    self.tarjeta = tarjeta + str((x * 9) % 10)

  #----------------------------------------------------------------------------
  def __str__(self):
    return self.tarjeta

###############################################################################

def main():

  # Datos del sistema tokenizador
  SISTEMA_TOKENIZADOR = 'http://127.0.0.1:8080'
  USUARIO_ST          = 'administracion@tienda-en-linea.com'
  CONTRASENIA_ST      = '123456'
  # Creación del conector
  conector = STConector(SISTEMA_TOKENIZADOR, USUARIO_ST, CONTRASENIA_ST)

  mensaje = 'Tiempo requerido para hacer {0} {1} con {2}: {3}'
  numero_operaciones = 1000

  # Métodos y tarjetas base para hacer las peticiones
  paquetes = [
    ['FFX',  225678112233445, []],
    ['BPS',  325678112233445, []],
    ['AHR',  425678112233445, []],
    ['TKR',  525678112233445, []],
    ['DRBG', 628545112233445, []]]

  # Se barren los paquetes
  for metodo, base, tokens in paquetes:
      # Se hacen 'numero_operaciones' peticiones de tokenización
      for i in range(base, base + numero_operaciones):
        tarjeta = str(Tarjeta(i))
        token = conector.tokenizar(tarjeta, metodo)
        tokens.append(token)

      print(mensaje.format(
        numero_operaciones, 'tokenización',
        metodo, conector.obtenerContador()))
      conector.reiniciarContador()

      # Se hacen 'numero_operaciones' peticiones de detokenización
      for token in tokens:
        if token != '':
          conector.detokenizar(token, metodo)

      print(mensaje.format(
        numero_operaciones, 'detokenización',
        metodo, conector.obtenerContador()))
      conector.reiniciarContador()

###############################################################################

if __name__ == '__main__':
  main()

