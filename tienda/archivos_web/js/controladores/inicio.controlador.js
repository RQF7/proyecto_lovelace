/*
 * Controlador de página de inicio.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorInicio', [
  '$scope',
  function (
    $scope
  )
  {


    /* Secuencia de inicio. **************************************************/
    $scope.cambiarTitulo("Catálogo", 1);
    //console.log("DEBUG: controlador de inicio");
  }
]);
