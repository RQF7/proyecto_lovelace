/*
 * Definición de comunicación con backend,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.factory('api', [
  '$http',
  function (
    $http
  )
  {
    var API = {};
    var RUTA_BASE = '/api';

    API.obtenerUsuarioDeSesion = function () {
      return $http.get(RUTA_BASE + '/usuario_de_sesion');
    };

    API.iniciarSesion = function(usuario) {
      return $http.post(RUTA_BASE + '/iniciar_sesion', usuario);
    };

    API.cerrarSesion = function () {
      return $http.get(RUTA_BASE + '/cerrar_sesion');
    };

    API.registrarCliente = function (cliente) {
      return $http.post(RUTA_BASE + '/registrar_cliente', cliente);
    };

    return API;
  }
]);
