/*
 * Controlador de página de administración de tokens.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorControl', [
  '$scope',
  '$location',
  '$mdDialog',
  'api',
  function (
    $scope,
    $location,
    $mdDialog,
    api
  )
  {
    $scope.cambiarTitulo("Control", 3);
    $scope.cliente = {};

    $scope.actualizarCliente = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/actualizar_cliente.ventana.html',
        controller: 'controladorFormularioActualizarCliente'
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          console.log(respuesta);
        }
      });
    };

    $scope.eliminarCliente = function ($event) {
      var aviso = $mdDialog.confirm()
        .title('Advertencia')
        .textContent("@@include('mensajes/adv_eliminar_cliente.txt')")
        .ariaLabel('Advertencia')
        .targetEvent($event)
        .ok('Aceptar')
        .cancel('Cancelar')
        .multiple(true);
      $mdDialog.show(aviso).then(function (respuesta) {
        api.eliminarCliente($scope.usuario.pk).then(function (respuesta) {
          api.cerrarSesion().then(function (respuesta) {
            $scope.usuario = undefined;
           $location.path('/');
          });
        });

        $mdDialog.hide();
      });
    };

  }
]);
