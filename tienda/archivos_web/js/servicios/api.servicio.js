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
     var RUTA_LIBRERIA = '/libreria';

     /* Operaciones de sesión. ************************************************/

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

     /* Operaciones con api de librería. *************************************/

     API.obtenerLibros = function (pagina, limite) {
       return $http.get(RUTA_BASE + RUTA_LIBRERIA + '/libros/'
        + pagina + '/' + limite);
     };

     API.obtenerTotalDeLibros = function () {
       return $http.get(RUTA_BASE + RUTA_LIBRERIA + '/total_de_libros');
     };

     /* Operaciones de carrito. **********************************************/

     API.guardarCarrito = function (carrito) {
       return $http.post(RUTA_BASE + RUTA_TIENDA + '/carrito', carrito);
     };

     API.obtenerCarrito = function () {
       return $http.get(RUTA_BASE + RUTA_TIENDA + '/carrito');
     };

     API.registrarCompra = function (compra) {
       return $http.post(RUTA_BASE + RUTA_TIENDA + '/compra', compra);
     };

     /* Operaciones sobre tarjetas *******************************************/

     API.obtenerTarjetas = function () {
       return $http.get(RUTA_BASE + RUTA_TIENDA + '/tarjetas');
     };

     /* Operaciones sobre direcciones ****************************************/

     API.obtenerDirecciones = function () {
       return $http.get(RUTA_BASE + RUTA_TIENDA + '/direcciones');
     };

     return API;
   }
 ]);
