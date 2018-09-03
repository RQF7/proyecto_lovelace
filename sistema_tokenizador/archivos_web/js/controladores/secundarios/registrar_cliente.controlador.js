/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioRegistrarCliente', [
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

    $scope.cliente = {};
    $scope.erCorreo = @@include('expresiones_regulares/correo.txt');
    $scope.erContrasenia = @@include('expresiones_regulares/contrasenia.txt');
    $scope.error = false;

    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.aceptar = function ($event) {
      api.registrarCliente($scope.cliente).then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Registro exitoso')
            .textContent('Para poder iniciar sesión es necesario que '
              + 'verifique su cuenta accediendo al vínculo enviado a su '
              + 'correo electrónico.')
            .ariaLabel('Registro exitoso')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });
        } else {
          $scope.error = true;
        }
      });
    };
  }
]);
