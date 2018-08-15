/*
 * Controlador general de aplicación.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorGeneral', [
  '$scope',
  '$route',
  '$routeParams',
  '$location',
  function (
    $scope,
    $route,
    $routeParams,
    $location
  )
  {
    $scope.$route = $route;
    $scope.routeParams = $routeParams;
    $scope.$location = $location;

    console.log('Controlador general');
  }
]);
