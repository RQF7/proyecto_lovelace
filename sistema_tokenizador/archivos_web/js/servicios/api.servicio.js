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
      return $http.post(RUTA_BASE + '/registrar_cliente', cliente);
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

    return API;
  }
]);
