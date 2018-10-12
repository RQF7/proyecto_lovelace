/*
 * Controlador general de aplicación.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.controller('controladorGeneral', [
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
    /* Datos públicos. *******************************************************/
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

    /* Control de botón de barra lateral. *************************************
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
        $scope.usuario = respuesta.data;
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
          // if ($scope.$routeParams.siguiente != undefined) {
          //   $location.path($scope.$routeParams.siguiente);
          //   $location.search('siguiente', null)
          // }
        }
      });
    };

    $scope.cerrarSesion = function () {
      api.cerrarSesion().then(function (respuesta) {
        $scope.usuario = undefined;
        $location.path('/');
      });
    };


    /* Secuencia de inicio. **************************************************/
    //console.log("DEBUG: controlador general");

    /* Registrar cliente *****************************************************/

    $scope.registrarse = function ($event) {
      var padre = angular.element(document.body);
      $mdDialog.show({
        parent: padre,
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/operar_usuario.ventana.html',
        controller: 'controladorFormularioOperarUsuario',
        locals: {
          "tituloOperacion": "Registrar datos",
          "operacion": "registrar"
        }
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          console.log(respuesta);
        }
      });
    };

    $scope.$on('$routeChangeSuccess', function () {

      if ($scope.$routeParams.siguiente != undefined) {
        $scope.iniciarSesion(undefined);
      }

      /* Verificación correcta. */
      else if ($scope.$routeParams.correo_verificado != undefined) {
        var aviso = $mdDialog.alert()
          .title('Verificación de correo correcta')
          .textContent('Su cuenta ha sido verificada correctamente.')
          .ariaLabel('Verificación de correo correcta')
          .targetEvent(undefined)
          .ok('Aceptar');
        $mdDialog.show(aviso).then(function (respuesta) {
          $location.search('correo_verificado', null);
        });
      }

      /* Verificación incorrecta. */
      else if ($scope.$routeParams.correo_no_verificado != undefined) {
        var aviso = $mdDialog.alert()
          .title('Vínculo expirado')
          .textContent('Han transcurrido más de 72 horas desde su registro.'
            + 'Para verificar su correo vuelva a registrarse.')
          .ariaLabel('Vínculo expirado')
          .targetEvent(undefined)
          .ok('Aceptar');
        $mdDialog.show(aviso).then(function (respuesta) {
          $location.search('correo_no_verificado', null);
        });
      }
    });


    /* Control de carrito. ***************************************************/
    $scope.carrito = {};
    $scope.carrito.total = 0.0;
    $scope.carrito.libros = [];

    api.obtenerCarrito().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.carrito = respuesta.data;
      }
    });

    $scope.buscarEnCarrito = function(idDeLibro) {
      for (var i = 0; i < $scope.carrito.libros.length; i++)
        if (idDeLibro == $scope.carrito.libros[i].pk)
          return i;
      return -1;
    };

    $scope.agregarAlCarrito = function (libro) {
      libro.cantidad = 1;
      libro.enCarrito = true;
      $scope.carrito.libros.push(libro);
      $scope.carrito.total += Number(libro.precio);
      api.guardarCarrito($scope.carrito);
    };

    $scope.quitarDelCarrito = function (libro) {
      libro.enCarrito = false;
      idDeLibro = $scope.buscarEnCarrito(libro.pk);
      $scope.carrito.total -= libro.precio
        * $scope.carrito.libros[idDeLibro].cantidad;
      $scope.carrito.libros.splice(idDeLibro, 1)
      api.guardarCarrito($scope.carrito);
    };

    $scope.cambioDeCantidad = function () {
      $scope.carrito.total = 0;
      for (var i = 0; i < $scope.carrito.libros.length; i++)
        $scope.carrito.total += $scope.carrito.libros[i].precio
          * $scope.carrito.libros[i].cantidad;
      api.guardarCarrito($scope.carrito)
    };

  }
]);
