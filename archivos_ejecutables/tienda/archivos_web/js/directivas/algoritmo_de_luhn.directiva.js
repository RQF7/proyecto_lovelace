/*
 * Directiva para validar con algoritmo de luhn.
 * Tienda en línea.
 * Proyecto Lovelace.
 *
 * Para usarse en la entrada de un número de tarjeta. */

 tienda.directive('ngAlgoritmoDeLuhn', function () {
   return {
     restrict: 'A',
     require: 'ngModel',
     link: function($scope, $element, $attrs, ngModel) {
       ngModel.$validators.algoritmoDeLuhn = function (valor) {
         if (valor == undefined)
           return true;

         var suma = 0;
         var contadorUno = valor.length - 2;
         var contadorDos = 0;

         while (contadorUno >= 0) {
           if (contadorDos % 2 == 0) {
             suma += ((Number(valor[contadorUno]) * 2) % 10)
              + Math.floor(Number(valor[contadorUno]) * 2 / 10);
           } else {
             suma += Number(valor[contadorUno]);
           }
           contadorUno--;
           contadorDos++;
         }

         return (suma * 9) % 10 == Number(valor[valor.length - 1]);
       }
     }
   }
 });
