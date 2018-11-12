/*
 * Controlador de formulario de inicio de sesión,
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioIniciarSesion', [
  '$scope',
  '$mdDialog',
  'api',
  function (
    $scope,
    $mdDialog,
    api
  )
  {
    /* Datos públicos. *******************************************************/

    $scope.usuario = {};
    $scope.error = '';

    /* Acciones públicas. ****************************************************/

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
  }
]);
