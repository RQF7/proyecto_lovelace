/*
 * Controlador de finalización de compra.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Recibe, entre otras cosas, una función como argumento (agregarMetodoDePago).
 * Esa función está registrada en el contrlador general, por lo que se puede
 * acceder a ella desde cualquier tro controlador de página (el controlador
 * de la cuenta la usa sin ningún problema). Para el caso de los controladores
 * de ventanas, sí necesitan una referencia directa (supongo que hay alguna
 * clase de control de aislamiento, para evitar choques de nombres).
 */

tienda.controller('controladorFinalizarCompra', [
  '$scope',
  '$mdDialog',
  'api',
  'tarjetas',
  'agregarMetodoDePago',
  function (
    $scope,
    $mdDialog,
    api,
    tarjetas,
    agregarMetodoDePago
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
    $scope.tarjetas = tarjetas;
    $scope.tarjeta = 0;
    $scope.agregarMetodoDePago = agregarMetodoDePago;

    /* TODO:
     * Hacer que «agregarMetodoDePago» regrese una promes; al terminar
     * se tiene que seleccionar el nuevo método. */

    $scope.direcciones = [];
    $scope.direccion = 0;
    $scope.secuencia = 1;

    api.obtenerDirecciones().then(function (respuesta) {
      $scope.direcciones = respuesta.data;
      $scope.direccion = $scope.direcciones[0].pk;
    });

    /* TODO:
     * ¿Qué pasa si el usuario le dá «cancelar» a la ventana para agregar
     * método de pago? Se tiene que implementar lo de las promesas para
     * identificar ese caso y cerrar esta ventana (sin métodos de pago no se
     * debe poder continuar). */

    if ($scope.tarjetas.length == 0) {
      $scope.agregarMetodoDePago(undefined);
    } else {
      $scope.tarjeta = $scope.tarjetas[0].pk;
    }
  }
]);
