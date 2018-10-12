/*
 * Definición de comunicación con backend.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

 tienda.factory('api', [
   '$http',
   function (
     $http
   )
   {
     var API = {};
     var RUTA_BASE = '/api';
     var RUTA_TIENDA = '/tienda';

     /* Operaciones de sesión. *************************************************/

     API.obtenerUsuarioDeSesion = function () {
       return $http.get(RUTA_BASE + RUTA_TIENDA + '/usuario_de_sesion');
     };

     API.iniciarSesion = function(usuario) {
       return $http.post(RUTA_BASE + RUTA_TIENDA + '/iniciar_sesion', usuario);
     };

     API.cerrarSesion = function () {
       return $http.get(RUTA_BASE + RUTA_TIENDA + '/cerrar_sesion');
     };

    /* Operaciones de clientes. ***********************************************/

    API.registrarUsuario = function (usuario) {
      console.log(usuario)
      return $http.post(RUTA_BASE + RUTA_TIENDA + '/operar_usuario', usuario);
    };

    //API.actualizarUsuario = function (usuario) {
    //  return $http.put(RUTA_BASE + RUTA_TIENDA + '/operar_usuario', usuario);
    //};

    //API.eliminarUsuario = function () {
    //  return $http.delete(RUTA_BASE + RUTA_TIENDA + '/operar_usuario');
    //};

     return API;
   }
 ]);
