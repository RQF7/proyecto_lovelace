/*
 * Controlador para aregar un método de pago.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioTarjeta', [
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

    $scope.cambioEnDireccionAnterior = function () {
      for (var i = 0; i < $scope.direcciones.length; i++) {
        if ($scope.direcciones[i].pk == $scope.objetoPadre.direccionAnterior) {
          if ($scope.direcciones[i].banderaDeSeleccion) {
            $scope.objetoPadre.direccionAnterior = undefined;
            $scope.direcciones[i].banderaDeSeleccion = false;
            $scope.direccion = {};
          } else {
            $scope.direcciones[i].banderaDeSeleccion = true;
            $scope.direccion = $scope.direcciones[i];
          }
        } else {
          $scope.direcciones[i].banderaDeSeleccion = false;
        }
      }
    };

    $scope.aceptar = function ($event) {
      $scope.tarjeta.direccion = $scope.direccion;
      if ($scope.objetoPadre.direccionAnterior == undefined)
        $scope.tarjeta.direccion.pk = 0;
      api.agregarTarjeta($scope.tarjeta).then(function (respuesta) {
        if (respuesta != undefined) {
          var mensaje, titulo, resultado;
          if (respuesta.data == "1") {
            titulo = "Error";
            mensaje = "@@include('mensajes/tarjeta_existente.txt')";
          } else if (respuesta.data == "2") {
            /* TODO: cambiar el nombre de este txt por algo más corto. */
            titulo = "Error";
            mensaje = "@@include('mensajes/tarjeta_existente_con_distinta_expiracion.txt')";
          } else {
            titulo = "Operación exitosa";
            mensaje = "@@include('mensajes/metodo_de_pago_agregado.txt')";
          }
          var aviso = $mdDialog.alert()
            .title(titulo)
            .textContent(mensaje)
            .ariaLabel(titulo)
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide();
          });
        }
      });
    };

    /* Secuencia de inicio. **************************************************/
    $scope.tarjeta = {};
    $scope.direccion = {};

    $scope.emisores = [];
    $scope.metodos = [];
    $scope.tipos = [];
    $scope.estados = [];

    api.obtenerEmisores().then(function (respuesta) {
      $scope.emisores = respuesta.data;
    });

    api.obtenerMetodos().then(function (respuesta) {
      $scope.metodos = respuesta.data;
    });

    api.obtenerTipos().then(function (respuesta) {
      $scope.tipos = respuesta.data;
    })

    api.obtenerEstados().then(function (respuesta) {
      $scope.estados = respuesta.data;
    })
  }
]);
