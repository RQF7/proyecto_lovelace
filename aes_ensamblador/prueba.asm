;
; Prueba de programación en ensamblador.
; Proyecto Lovelace.
;

segment .data                   ; Segmento de constantes.
  mensaje db '¡Hola, mundo!',10

segment .text                   ; Segmento de etiquetas de programa.
  global _start                 ; Define el punto de acceso al programa.

; Función principal ===========================================================
_start:

  ; Imprimir mensaje
  mov edx,15                    ; Longitud de la cadena.
  mov ecx,mensaje               ; Referencia a constante.
  mov ebx,1                     ; Salida estándar.
  mov eax,4                     ; Llamada al sistema para escribir.
  int 0x80                      ; Interrupción de kernel.

  ; Terminar programa
  mov eax,1                     ; Llamada al sistema para salir.
  int 0x80                      ; Interrupción de kernel.
  
