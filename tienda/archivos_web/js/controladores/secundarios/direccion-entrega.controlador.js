/*
 * Controlador para agregar una dirección de entrega.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioDireccionEntrega', [
  '$scope',
  '$mdDialog',
  'api',
  function (
    $scope,
    $mdDialog,
    api
  )
  {
    /* Funciones públicas. ***************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function () {
      api.iniciarSesion($scope.usuario).then(function (respuesta) {
        if (respuesta.data == '0') {
          $scope.error = 'incorrecto';
        } else if (respuesta.data == '1') {
          $scope.error = 'no verificado';
        } else {
          $mdDialog.hide(respuesta.data);
        }
      });
    };

    /* Secuencia de inicio. **************************************************/
    $scope.direccion = {};

    $scope.estados = [];

    api.obtenerEstados().then(function (respuesta) {
      $scope.estados = respuesta.data;
    })
  }
]);
