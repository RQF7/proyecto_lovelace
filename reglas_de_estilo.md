# Reglas y sugerencias de estilo

Concentración de reglas y sugerencias de estilo. Las generales le aplican a
todo el repositorio, mientras que en la sección de *Particulares* se detallan
las específicas a cada lenguaje usado. En caso de conflicto entre una regla
particular y una general, la particular tiene preferencia.

## Generales

Todos los archivos de texto plano del repositorio deben de cumplir con los
siguientes puntos:

* Tabulares blandos de 2 espacios.
* Margen derecho de 80 caracteres (mientras no se entre en conflicto con la
  sintaxis del lenguaje en cuestión).
* Nombres de archivos y carpetas:
  * Estilo **nombre_de_archivo**.
  * Salvo que se traten de siglas, solamente se ocupan minúsculas.
  * Nombres en español sin salir de conjunto ASCII (sin tildes o «ñ»).
* Comentario al inicio del archivo con explicación de contenido y
  el nombre del proyecto: **Proyecto Lovelace**.

## Particulares

### Git/github

* **Sobre mensajes de commits:** tanto el título como el cuerpo del mensaje
  son obligatorios. Ambos deben responder a la pregunta *¿qué se hizo?*.
  Es preferible extenderse (incluso al *cómo*) a quedarse solamente en el
  título, sin poner ningún cuerpo. **Importante:** al texto de los mensajes
  del commit también le aplica la regla de los 80 caracteres.

* **Sobre las observaciones:** es preferible marcarle los errores al
  responsable (por insignificantes que sean) a adoptar una actitud de *ya,
  mejor yo lo corrijo*.

* **Sobre la ubicación de las observaciones:** los errores u observaciones
  focalizados en un solo punto o en un solo commit se deben colocar mediante
  comentarios de github en la página del propio commit. Si se trata de errores
  u observaciones sobre muchos archivos o sobre muchos commits, se debe
  levantar un *issue*.

* **Sobre la historia de los issues:** la página de un *issue* no solamente
  describe una tarea (eso lo hace el primer comentario) sino que también
  muestra la historia de cómo se fue desarrollando la tarea. Para esto se deben
  crear referencias en la página de un commit hacia el *issue* al que está
  relacionado.

### LaTeX

Recomendaciones:

* **Sobre la distribución de contenidos:** dar preferencia a la creación de
  muchos archivos **tex** con poco contenido, a la creación de pocos archivos
  con mucho contenido. En la medida de los posible, la estructura de
  archivos debe imitar la estructura del documento.

* **Separación entre contenido y elementos estructurales:** todo el contenido
  de los documentos (la información) debe de ir dentro de archivos **tex**,
  mientras que las instrucciones para modificar el formato van en archivos
  **sty**. Se debe evitar a toda costa colocar instrucciones estructurales
  junto con el contenido (p. ej. modificaciones de espaciado, saltos de página).

Reglas. Todos los archivos **tex** y **sty** deben cumplir con los siguientes
puntos:

* Ligas entre archivos relativas (paquete *import*).
* Los únicos elementos que introducen niveles de indentación son los entornos
  (i. e. `\begin{} ... \end{}`), los contenidos extensos entre llaves:
  ```
  \comando[argumentos_opcionales]{contenidos_cortos}
  {
    contenidos_extensos
  }
  ```
  y las líneas secundarias de los `\item`. En caso de ocupar un contenido
  extenso, las llaves de apertura y cierre deben de estar en su propio renglón.
* Todas las imágenes se colocan dentro de una carpeta *diagramas* hermana al
  archivo desde el cual se importan. Dentro de esta carpeta se debe de colocar
  una versión binaria del archivo del programa desde el cual se generó (p. ej.
  los xml de draw.io).

### C++

Todo el código en c++ debe cumplir con los siguientes puntos:

* Nombres de identificadores:
  * Clases y espacios de nombres: **NombreDeClase**.
  * Funciones y variables: **nombreDeVariable**.
  * Prefijo para variables miembro de clase: «m».
* Posición de llaves:
  * Tanto en declaraciones (espacios de nombres, clases, funciones) como
    en controles de flujo (ciclos, condicionales) ambas llaves se colocan en
    un renglón propio. Para los controles de flujo, no se colocan llaves si
    el bloque solamente contiene una línea.
* Espacios en blanco:
  * Debe haber un espacio en blanco antes y después de cualquier palabra
    reservada:
    ```c++
    if (condicion)
    for (;;)
    ```
  * Los operadores binarios llevan espacios en blanco antes y después:
    ```c++
    5 + 6;
    prueba = funcion(76) - (45 / 98);
    ```
  * El contenido de paréntesis, corchetes o llaves no lleva espacios por
    el lado de adentro:
    ```c++
    funcion(a + b);
    for (int i = 6; i <= 7; i++)
    ```
  * Las listas de argumentos van separadas por espacios después de cada coma:
    ```c++
    llamadaAFuncion(arg1, arg2, funcionDos(5 + 8, arg3));
    ```
* Terminación de archivos:
  * Código fuente: **.cpp**.
  * Archivos de cabeceras: **.hh**.
* Distribución de archivos:
  * Todas las cabeceras deben de ir dentro de una carpeta *cabeceras*.
  * Solamente debe de haber una clase por archivo de cabecera; el nombre del
    archivo debe imitar al nombre de la clase (con las respectivas reglas
    para cada uno). Por ejemplo, una distribución común para una clase
    `ClaseDeEjemplo` es poner la declaración en
    `cabeceras/clase_de_ejemplo.hh` y la definición en `clase_de_ejemplo.cpp`.
* Comentarios:
  * El estilo de los comentarios es tipo C: `/* */`.
  * Los comentarios de doxygen (`/** */`) pueden ser todo un bloque:
    ```
    /**
     * Contenido del bloque
     */
    ```
    O de solo una línea: `/** Contenido de línea. */`. Los de bloque deben
    tener una línea en blanco tanto arriba como abajo; mientras que los de
    línea solamente tienen una línea en blanco antes.
* Documentación:
  * El modelo de documentación del código es estricto: todo debe llevar
    comentarios de documentación (clases, miembros de clase tanto privados
    como públicos, funciones autónomas, argumentos, valores de retorno, etc.).
* Notación para constructores: las llamadas a constructores se deben hacer con
  la notación de llaves, a no ser que el contructor en cuestión reciba a la
  entrada una lista de inicialización (en cuyo caso, dada la ambigüedad, se
  debe regresar a la notación de paréntesis).
