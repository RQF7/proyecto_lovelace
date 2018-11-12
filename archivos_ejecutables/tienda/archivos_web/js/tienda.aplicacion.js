/*
 * Definición de aplicación de angular global,
 * tienda en línea: librería.
 * Proyecto Lovelace.
 */

var tienda = angular.module(
  'tienda',
  [
    'ngMaterial',       /* Estilos y componentes de angular material. */
    'ngMessages',       /* Ventanas emergentes. */
    'ngRoute',          /* Controla la navegación en la aplicación. */
    'md.data.table'     /* Directivas para tablas. */
  ]
)
