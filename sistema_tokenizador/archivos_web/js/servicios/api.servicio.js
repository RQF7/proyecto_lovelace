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

    /* Operaciones de sesión. */

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
      return $http.post(RUTA_BASE + '/operar_cliente', cliente);
    };

    API.actualizarCliente = function (cliente) {
      return $http.put(RUTA_BASE + '/operar_cliente', cliente);
    };

    API.eliminarCliente = function (cliente) {
      return $http.delete(RUTA_BASE + '/operar_cliente', cliente);
    };

    API.iniciarRefrescoDeLlaves = function (idDeCliente) {
      return $http.post(RUTA_BASE + '/iniciar_refresco_de_llaves/'
      + idDeCliente);
    };

    API.terminarRefrescoDeLlaves = function (idDeCliente) {
      return $http.post(RUTA_BASE + '/terminar_refresco_de_llaves/'
      + idDeCliente);
    };

    API.eliminarTokens = function (idDeCliente) {
      return $http.post(RUTA_BASE + '/eliminar_tokens/' + idDeCliente);
    };


    /* Operaciones de administrador. */

    API.obtenerClientesEnEspera = function (pagina, limite) {
      return $http.get(RUTA_BASE + '/clientes_en_espera/'
      + pagina + '/' + limite)
    };

    API.obtenerTotalDeClientesEnEspera = function () {
      return $http.get(RUTA_BASE + '/total_de_clientes_en_espera');
    };

    API.obtenerClientesEnListaNegra = function (pagina, limite) {
      return $http.get(RUTA_BASE + '/clientes_en_lista_negra/'
      + pagina + '/' + limite)
    };

    API.obtenerTotalDeClientesEnListaNegra = function () {
      return $http.get(RUTA_BASE + '/total_de_clientes_en_lista_negra');
    };

    API.obtenerClientesAprobados = function (pagina, limite) {
      return $http.get(RUTA_BASE + '/clientes_aprobados/'
      + pagina + '/' + limite)
    };

    API.obtenerTotalDeClientesAprobados = function () {
      return $http.get(RUTA_BASE + '/total_de_clientes_aprobados');
    };

    API.aprobarCliente = function (idDeCliente) {
      return $http.get(RUTA_BASE + '/aprobar_cliente/' + idDeCliente);
    };

    API.rechazarCliente = function (idDeCliente) {
      return $http.get(RUTA_BASE + '/rechazar_cliente/' + idDeCliente);
    };

    API.vetarCliente = function (idDeCliente) {
      return $http.get(RUTA_BASE + '/vetar_cliente/' + idDeCliente);
    };

    API.desvetarCliente = function (idDeCliente) {
      return $http.get(RUTA_BASE + '/desvetar_cliente/' + idDeCliente);
    };

    return API;
  }
]);
