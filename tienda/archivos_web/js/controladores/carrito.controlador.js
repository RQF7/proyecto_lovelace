/*
 * Controlador de página de carrito.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorCarrito', [
  '$scope',
  '$route',
  '$routeParams',
  '$location',
  '$mdDialog',
  'api',
  function (
    $scope,
    $route,
    $routeParams,
    $location,
    $mdDialog,
    api
  )
  {
    /* Funciones públicas. ***************************************************/
    $scope.finalizarCompra = function ($event) {
      if ($scope.usuario == undefined) {
        $scope.iniciarSesion(undefined);
        /* TODO: que iniciarSesion regrese una promesa: al terminar su flujo,
         * se hace una llamada recursiva a esta función. */
      } else {
        $mdDialog.show({
          parent: angular.element(document.body),
          targetEvent: $event,
          templateUrl: '/estaticos/html/ventanas/finalizar_compra.ventana.html',
          controller: 'controladorFinalizarCompra',
          focusOnOpen: false,
          locals: {
            'libros': $scope.carrito.libros,
            'tarjetas': $scope.tarjetas,
            'agregarMetodoDePago': $scope.agregarMetodoDePago
          }
        }).then(function (respuesta) {
          if (respuesta != undefined) {
            $scope.reiniciarCarrito();
            $location.path('/');
          }
        });
      }
    };

    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Carrito de compra", 2);
    $scope.$route = $route;
    $scope.$routeParams = $routeParams;
    $scope.$location = $location;
  }
]);
