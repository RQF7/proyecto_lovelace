/*
 * Controlador general de aplicación.
 * Aplicación web de sistema tokenizador.
 * Proyecto Lovelace.
 */

sistemaTokenizador.controller('controladorGeneral', [
  '$scope',
  '$route',
  '$routeParams',
  '$location',
  '$timeout',
  '$mdSidenav',
  '$mdDialog',
  'api',
  function (
    $scope,
    $route,
    $routeParams,
    $location,
    $timeout,
    $mdSidenav,
    $mdDialog,
    api
  )
  {
    $scope.$route = $route;
    $scope.$routeParams = $routeParams;
    $scope.$location = $location;

    /* Control de secciones. *************************************************/

    /* Gestión del título de sección.
     *
     * Cada controlador de página es responsable de establecer el título
     * de sección al cargarse. El entero (sección) es para colocar un
     * indicador en la barra lateral (un círculo) que indica la
     * página que está cargada (y por lo tanto el controlador) al momento.
     */

    $scope.tituloDeSeccion = "";
    $scope.seccion = 0;

    $scope.cambiarTitulo = function (nuevoTitulo, identificador)
    {
      $scope.tituloDeSeccion = nuevoTitulo;
      $scope.seccion = identificador;

      /* Cambiar el estado de la barra de navegación (solo en pantallas
       * pequeñas). La idea es que al abrir un link la barra se oculte.
       * https://developer.mozilla.org/en-US/docs/Web/API/Window/matchMedia */
      if (!window.matchMedia("(min-width: 1280px)").matches) {
        if ($mdSidenav('barraDeNavegacion').isOpen())
          $scope.cambiarEstadoBarra();
      }
    };

    /* Control de botón de barra lateral.
     *
     * La idea general salió de aquí:
     * https://material.angularjs.org/latest/demo/sidenav
     * No es algo precisamente claro.
     * TODO: Lo ideal sería que al dar click afuera (en una pantalla pequeña)
     *       también se muestre una animación. */

    $scope.cambiarEstadoBarra = contruirCambiador('barraDeNavegacion');

    function rebotar(funcion, tiempo, contexto) {
      var temporizador;
      return function rebotada() {
        var contexto = $scope;
        var argumentos = Array.prototype.slice.call(arguments);
        $timeout.cancel(temporizador);
        temporizador = $timeout(function() {
          temporizador = undefined;
          funcion.apply(contexto, argumentos);
        }, tiempo || 10);
      };
    }

    /* Regresa una función que cambia el estado de la barra dada por su
     * identificador. La animación dura 200 milisegundos. */
    function contruirCambiador(identificador) {
      return rebotar(function() {
        $mdSidenav(identificador).toggle()
      }, 200);
    };

    /* Operaciones de sesión **************************************************/

    $scope.usuario = undefined;
    api.obtenerUsuarioDeSesion().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.usuario = respuesta.data[0];
      }
    });

    /* Al terminar resolución de ruta. */
    $scope.$on('$routeChangeSuccess', function () {

      /* Para mostrar login en caso de redirección. */
      if ($scope.$routeParams.siguiente != undefined) {
        $scope.iniciarSesion(undefined);
      }

      /* Verificación correcta. */
      else if ($scope.$routeParams.correo_verificado != undefined) {
        var aviso = $mdDialog.alert()
          .title('Verificación de correo correcta')
          .textContent('Su cuenta ha sido verificada correctamente. '
            + 'En un máximo de 24 horas recibirá un correo con el resultado '
            + 'de su solicitud.')
          .ariaLabel('Verificación de correo correcta')
          .targetEvent(undefined)
          .ok('Aceptar');
        $mdDialog.show(aviso).then(function (respuesta) {
          $mdDialog.hide();
        });
      }

      /* Verificación incorrecta. */
      else if ($scope.$routeParams.correo_no_verificado != undefined) {
        var aviso = $mdDialog.alert()
          .title('Vínculo expirado')
          .textContent('Han transcurrido más de 24 horas desde su registro. '
            + 'Para verificar su correo vuelva a registrarse.')
          .ariaLabel('Vínculo expirado')
          .targetEvent(undefined)
          .ok('Aceptar');
        $mdDialog.show(aviso).then(function (respuesta) {
          $mdDialog.hide();
        });
      }
    });

    $scope.iniciarSesion = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/iniciar_sesion.ventana.html',
        controller: 'controladorFormularioIniciarSesion'
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          $scope.usuario = respuesta;
          if ($scope.$routeParams.siguiente != undefined) {
            $location.path($scope.$routeParams.siguiente);
            $location.search('siguiente', null)
          } else if ($scope.usuario.fields.tipoDeUsuario == 'cliente') {
            $location.path('/administración_de_tokens');
          } else {
            $location.path('/administración');
          }
        }
      });
    };

    $scope.cerrarSesion = function () {
      api.cerrarSesion().then(function (respuesta) {
        $scope.usuario = undefined;
        $location.path('/');
      });
    };

    /* Registrar cliente *****************************************************/

    $scope.registrarse = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/registrar_cliente.ventana.html',
        controller: 'controladorFormularioRegistrarCliente'
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          console.log(respuesta);
        }
      });
    };

  }
]);
