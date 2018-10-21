/*
 * Controlador para aregar un método de pago.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorFormularioTarjeta', [
  '$scope',
  '$mdDialog',
  'api',
  'direcciones',
  function (
    $scope,
    $mdDialog,
    api,
    direcciones
  )
  {
    /* Datos públicos. *******************************************************/
    $scope.tarjeta = {};
    $scope.direccion = {};
    $scope.direcciones = direcciones;
    $scope.objetoPadre = {};
    $scope.objetoPadre.direccionAnterior = undefined;

    /* El «objetoPadre» es para colocar el modelo de los radiobuttons
     * adentro de un objeto y así poder acceder a su valor desde este
     * controlador. Sin él, se modifica «direccionAnterior» en un controlador
     * virtual hijo definido por el nf-if. Ver:
     * https://stackoverflow.com/questions/18342917/
     * angularjs-ng-model-doesnt-work-inside-ng-if#18342974 */

    $scope.emisores = [];
    $scope.metodos = [];
    $scope.tipos = [];
    $scope.estados = [];
    $scope.erTarjeta = @@include('expresiones_regulares/numero_de_tarjeta.txt');
    $scope.hoy = new Date();

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
            resultado = undefined;
          } else if (respuesta.data == "2") {
            /* TODO: cambiar el nombre de este txt por algo más corto. */
            titulo = "Error";
            mensaje = "@@include('mensajes/tarjeta_existente_con_distinta_expiracion.txt')";
            resultado = undefined;
          } else if (respuesta.data == "3") {
            titulo = "Error";
            mensaje = "@@include('mensajes/error_al_tokenizar.txt')";
            resultado = undefined;
          } else {
            titulo = "Operación exitosa";
            mensaje = "@@include('mensajes/metodo_de_pago_agregado.txt')";
            resultado = respuesta.data[0];
          }
          var aviso = $mdDialog.alert()
            .title(titulo)
            .textContent(mensaje)
            .ariaLabel(titulo)
            .targetEvent($event)
            .ok('Aceptar')
            .multiple(true);
          $mdDialog.show(aviso).then(function (respuesta) {
            $mdDialog.hide(resultado);
          });
        }
      });
    };

    /* Secuencia de inicio. **************************************************/

    api.obtenerEmisores().then(function (respuesta) {
      $scope.emisores = respuesta.data;
    });

    api.obtenerMetodos().then(function (respuesta) {
      $scope.metodos = respuesta.data;
    });

    api.obtenerTipos().then(function (respuesta) {
      $scope.tipos = respuesta.data;
    });

    api.obtenerEstados().then(function (respuesta) {
      $scope.estados = respuesta.data;
    });

    for (var i = 0; i < $scope.direcciones.length; i++) {
      $scope.direcciones[i].banderaDeSeleccion = false;
    }
  }
]);
