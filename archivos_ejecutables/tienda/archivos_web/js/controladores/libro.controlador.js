/*
 * Controlador de página de detalles de carrito.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorLibro', [
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
    $scope.cambiarTitulo("Detalles de libro", -1);
    $scope.libro = {};
    api.obtenerLibro($routeParams.idDeLibro).then(function (respuesta) {
      $scope.libro = respuesta.data;
      if ($scope.buscarEnCarrito($scope.libro.pk) >= 0) {
        $scope.libro.enCarrito = true;
      } else {
        $scope.libro.enCarrito = false;
      }
    });
  }
]);
