/*
 * Controlador de página de carrito.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorCarrito', [
  '$scope',
  'api',
  function (
    $scope,
    api
  )
  {
    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Carrito de compra", 2);
  }
]);
