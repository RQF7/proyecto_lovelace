/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioIniciarSesion', [
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
        } else if (respuesta.data == '2') {
          $scope.error = 'no aprobado'
        } else if (respuesta.data == '3') {
          $scope.error = 'rechazado'
        } else if (respuesta.data == '4') {
          $scope.error = 'en lista negra'
        } else {
          $mdDialog.hide(respuesta.data[0]);
        }
      });
    };
  }
]);
