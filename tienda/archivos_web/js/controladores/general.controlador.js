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
        obtenerTarjetas();
        obtenerDirecciones();
      }
    });

    $scope.iniciarSesion = function ($event) {
      $mdDialog.show({
        parent: angular.element(document.body),
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/iniciar_sesion.ventana.html',
        controller: 'controladorFormularioIniciarSesion'
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          $scope.usuario = respuesta;
          obtenerTarjetas();
          obtenerDirecciones();
        }
      });
    };

    $scope.cerrarSesion = function () {
      api.cerrarSesion().then(function (respuesta) {
        $scope.usuario = undefined;
        $scope.tarjetas = [];
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
          "operacion": "registrar",
          "usuario": undefined
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

    api.obtenerCarrito().then(function (respuesta) {
      if (respuesta.data != '') {
        $scope.carrito = respuesta.data;
      }
    });

    $scope.reiniciarCarrito = function () {
      $scope.carrito = {};
      $scope.carrito.total = 0.0;
      $scope.carrito.libros = [];
    };

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

    $scope.reiniciarCarrito();

    /* Para acciones comunes a varias páginas. *******************************/
    /* TODO: lo de las direcciones también debe de ir aquí. */
    $scope.tarjetas = [];

    $scope.agregarMetodoDePago = function($event) {

      /* Armar arreglo de direcciones asociadas. */
      var direccionesDeTarjetas = [];
      var banderaAgregado;
      for (var i = 0; i < $scope.tarjetas.length; i++) {
        banderaAgregado = false;
        for (var j = 0; j < direccionesDeTarjetas.length; j++) {
          if (direccionesDeTarjetas[j].pk == $scope.tarjetas[i].direccion.pk) {
            banderaAgregado = true;
            break;
          }
        }
        if (!banderaAgregado)
          direccionesDeTarjetas.push($scope.tarjetas[i].direccion);
      }

      /* Mostrar formulario. */
      $mdDialog.show({
        parent: angular.element(document.body),
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/tarjeta.ventana.html',
        controller: 'controladorFormularioTarjeta',
        multiple: true,
        locals: {
          'direcciones': direccionesDeTarjetas
        }
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          $scope.tarjetas.push(respuesta);
          api.obtenerDireccionDeTarjeta(respuesta.fields.direccion)
            .then(function (respuesta) {
              for (var i = 0; i < $scope.tarjetas.length; i++) {
                if ($scope.tarjetas[i].fields.direccion == respuesta.data[0].pk
                  && $scope.tarjetas[i].direccion == undefined) {
                    $scope.tarjetas[i].direccion = respuesta.data[0];
                    break;
                }
              }
            });
        }
      });
    };

    $scope.direcciones = [];
    $scope.agregarDireccionDeEntrega = function($event) {
      $mdDialog.show({
        parent: angular.element(document.body),
        targetEvent: $event,
        templateUrl: '/estaticos/html/ventanas/direccion.ventana.html',
        controller: 'controladorFormularioDireccionEntrega',
        multiple: true
      }).then(function (respuesta) {
        if (respuesta != undefined) {
          $scope.direcciones.push(respuesta);
        }
      });
    };

    /* Funciones privadas. ***************************************************/

    obtenerTarjetas = function () {

      /* TODO:
       * * La dirección de una tarjeta tendría que venir desde la primera
       *   petición (es una llave foranea); esto se arregla encontrando
       *   un serializador funcional para las últimas versiones de django.
       * * La función de retorno de petición de dirección de tarjeta
       *   debería poder acceder al contexto del for desde el que
       *   fue llamada (para no volver a recorrer todo); seguro que hay
       *   sintaxis para eso. */

      api.obtenerTarjetas().then(function (respuesta) {
        $scope.tarjetas = respuesta.data;
        for (var i = 0; i < $scope.tarjetas.length; i++) {
          api.obtenerDireccionDeTarjeta($scope.tarjetas[i].fields.direccion)
            .then(function (respuesta) {
              for (var i = 0; i < $scope.tarjetas.length; i++) {
                if ($scope.tarjetas[i].fields.direccion == respuesta.data[0].pk
                  && $scope.tarjetas[i].direccion == undefined) {
                    $scope.tarjetas[i].direccion = respuesta.data[0];
                    break;
                  }
              }
            });
        }
      });
    };

    obtenerDirecciones = function () {
      api.obtenerDirecciones().then(function (respuesta) {
        $scope.direcciones = respuesta.data
      });
    };

  }
]);
