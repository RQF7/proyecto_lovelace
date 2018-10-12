/*
 * Controlador de página de carrito.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorCuenta', [
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
    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Administración de cuenta", 3);
    $scope.tarjetas = [];
    $scope.direcciones = [];

    api.obtenerTarjetas().then(function (respuesta) {
      $scope.tarjetas = respuesta.data;
    });

    api.obtenerDirecciones().then(function (respuesta) {
      $scope.direcciones = respuesta.data
    });
  }
]);
