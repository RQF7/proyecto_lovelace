/*
 * Configuración de ruteo en sitio público.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Mapeo entre urls, archivos estáticos y controladores.
 */

tienda.config(function($routeProvider, $locationProvider){

  $routeProvider.when('/',
  {
    templateUrl: 'estaticos/html/inicio.html',
    controller: 'controladorInicio'
  });

  $routeProvider.when('/carrito',
  {
    templateUrl: 'estaticos/html/carrito.html',
    controller: 'controladorCarrito'
  });

  $routeProvider.when('/cuenta',
  {
    templateUrl: 'estaticos/html/cuenta.html',
    controller: 'controladorCuenta'
  });

  $routeProvider.when('/libro/:idDeLibro',
  {
    templateUrl: 'estaticos/html/libro.html',
    controller: 'controladorLibro'
  });

  $locationProvider.hashPrefix('');
  $locationProvider.html5Mode(true);

});
