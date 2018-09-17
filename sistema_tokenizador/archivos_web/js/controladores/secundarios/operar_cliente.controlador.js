/*
 * Controlador de formulario de inicip de sesión,
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorFormularioOperarCliente', [
  '$scope',
  '$location',
  '$mdDialog',
  'api',
  'TituloOperacion',
  'Operacion',
  function (
    $scope,
    $location,
    $mdDialog,
    api,
    TituloOperacion,
    Operacion
  )
  {
    /* Datos públicos. *******************************************************/

    $scope.cliente = {};
    $scope.erCorreo = @@include('expresiones_regulares/correo.txt');
    $scope.erContrasenia = @@include('expresiones_regulares/contrasenia.txt');
    $scope.error = false;

    $scope.TituloOperacion = TituloOperacion;
    $scope.Operacion = Operacion;
    mensaje = 'Para poder iniciar sesión es necesario que '
      + 'verifique su cuenta accediendo al vínculo enviado a su '
      + 'correo electrónico (revise su carpeta de spam).'

    api.obtenerUsuarioDeSesion().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.usuario = respuesta.data[0];
      }
    });


    /* Acciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.operar = function () {
      if (Operacion == "registrar") {
        $scope.aceptar_registro()
      } else if (Operacion == "actualizar") {
        $scope.aceptar_actualizacion()
      }
    };

    $scope.aceptar_registro = function ($event) {
      api.registrarCliente($scope.cliente).then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Registro exitoso')
            .textContent(mensaje)
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

    $scope.aceptar_actualizacion = function ($event) {
      api.actualizarCliente($scope.cliente).then(function (respuesta) {
        if (respuesta.data == '0') {
          var aviso = $mdDialog.alert()
            .title('Actualización exitosa')
            .textContent(mensaje)
            .ariaLabel('Actualización exitosa')
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });
          api.cerrarSesion().then(function (respuesta) {
            $scope.usuario = undefined;
            $location.path('/');
          });
        } else {
          $scope.error = true;
        }
      });
    };

  }
]);
