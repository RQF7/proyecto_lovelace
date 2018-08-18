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

    API.iniciarSesion = function(usuario) {
      return $http.post(RUTA_BASE + '/iniciar_sesion', usuario);
    };

    return API;
  }
]);
