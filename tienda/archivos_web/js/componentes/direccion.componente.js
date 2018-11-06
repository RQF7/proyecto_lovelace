/*
 * Componenete para mostrar en una cadena de una dirección.
 * Tienda en línea.
 * Proyecto Lovelace.
 */

tienda.component('egoDireccion', {
  restrict: 'E',
  templateUrl: '/libreria/estaticos/html/componentes/direccion.componente.html',
  bindings: {
    informacionDeDireccion: '=informacion'
  }
});
