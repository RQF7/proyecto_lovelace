/*
 * Controlador de finalización de compra.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * TODO: si no hay direcciones asociadas, hay que redirigir a formulario
 * de dirección. Lo mismo para las tarjetas.
 */

tienda.controller('controladorFinalizarCompra', [
  '$scope',
  '$mdDialog',
  'api',
  function (
    $scope,
    $mdDialog,
    api
  )
  {
    /* Funciones públicas. ****************************************************/

    $scope.cancelar = function () {
      $mdDialog.hide();
    };

    $scope.continuar = function ($event) {
      if ($scope.secuencia == 1) {
        $scope.secuencia = 2;
      } else if ($scope.secuencia == 2) {
        $scope.secuencia = 3;
      } else if ($scope.secuencia == 3) {
        api.registrarCompra({
          'tarjeta': $scope.tarjeta,
          'direccion': $scope.direccion})
          .then(function (respuesta) {
            var aviso = $mdDialog.alert()
              .title('Registro exitoso')
              .textContent('Su compra ha sido registrada correctamente')
              .ariaLabel('Registro exitoso')
              .targetEvent($event)
              .ok('Aceptar')
              .multiple(true);
            $mdDialog.show(aviso).then(function (respuesta) {
              $mdDialog.hide("todo en orden");
            });
          });
      }
    };

    $scope.regresar = function () {
      $scope.secuencia--;
    };

    /* Secuencia de inicio. ***************************************************/
    $scope.tarjetas = [];
    $scope.tarjeta = 0;
    $scope.direcciones = [];
    $scope.direccion = 0;
    $scope.secuencia = 1;

    api.obtenerTarjetas().then(function (respuesta) {
      $scope.tarjetas = respuesta.data;
      $scope.tarjeta = $scope.tarjetas[0].pk;
      console.log("Tarjtas", $scope.tarjetas);
    });

    api.obtenerDirecciones().then(function (respuesta) {
      $scope.direcciones = respuesta.data;
      $scope.direccion = $scope.direcciones[0].pk;
      console.log("Direcciones", $scope.direcciones);
    });
  }
]);
