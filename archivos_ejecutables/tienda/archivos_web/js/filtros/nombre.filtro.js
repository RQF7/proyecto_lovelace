/*
 * Filtro para cadenas de nombres.
 * Pone la primera letra de cada palabra en mayúsculas.
 * Proyecto Lovelace.
 */

tienda.filter('nombre', function() {
  return function(entrada) {
    if (entrada == undefined)
      return;
    entrada = entrada.toLowerCase()
    var palabras = entrada.split(" ")
    var resultado = ""
    for (var i = 0; i < palabras.length; i++)
      resultado += palabras[i].charAt(0).toUpperCase()
        + palabras[i].slice(1) + ' ';
    return resultado;
  };
});
