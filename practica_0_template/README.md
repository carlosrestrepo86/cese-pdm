# Práctica 0

Este módulo contiene la resolución de la práctica 0 y el análisis de su comportamiento.

## Respuestas al cuestionario

### ¿De qué serviría usar un array de “tiempos” en el programa? ¿Qué pasa con nuestro programa si nos piden agregar/sacar/cambiar un tiempo de encendido? 

Se facilita el manejo de los tiempos, ya que al tenerlos en un array es mucho más fácil realizar operaciones sobre estos; es más ordenado y permitiría varios tiempos en una variable.

### ¿Cómo responde el programa a las pulsaciones? ¿Hay falsos positivos o pulsaciones no detectadas?

Sí, hay pulsaciones no detectadas debido a que no se trabaja con interrupciones; entonces, mientras se ejecuta un PWM, se pierden pulsaciones sobre el botón.
También hay falsos positivos debido a que falta control para el antirrebote.

### ¿Cuál es el mejor momento para leer el pulsador, luego de un ciclo completo de la secuencia o después de encender y apagar el led? ¿Qué diferencia hay entre estas alternativas?

La lectura es igual en ambas formas, ya que es muy difícil que el usuario presione el botón cuando el microcontrolador va a pasar al condicional de lectura; entonces, visualmente y al presionar el botón, la sensación es la misma: se pierden pulsaciones.

### ¿Cambiaría las respuestas a las preguntas anteriores si el tiempo de encendido del led fuera sensiblemente más grande, 2 segundos, por ejemplo? ¿Y si fuera sensiblemente más chico, 50 ms, por ejemplo?

Si el tiempo es mayor, la pérdida de pulsaciones aumenta, ya que el microcontrolador va a estar más tiempo bloqueado y no cambiarían las respuestas anteriores.
Si el tiempo es menor, mejora el funcionamiento del código; es mejor, tendría menos pérdida de pulsaciones y no influiría si la lectura del botón va al inicio o fin del código.