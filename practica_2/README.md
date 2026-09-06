# Práctica 2

Este módulo contiene la resolución de la práctica 2 y el análisis de su comportamiento.

## Respuestas al cuestionario

### ¿Se pueden cambiar los tiempos de encendido de cada led fácilmente en un solo lugar del código o éstos están hardcodeados? 

Sí, se pueden cambiar fácilmente, ya que están parametrizados a través de un vector de configuración.

### ¿Qué bibliotecas estándar se debieron agregar para que el código compile? Si las funcionalidades crecieran, habría que pensar cuál sería el mejor lugar para incluir esas bibliotecas y algunos typedefs que se usan en el ejercicio.

Se agregó la librería stdint.h para el manejo de los tipos de datos nativos.
Se agregó la librería stdbool.h para manejo de datos booleanos.

### ¿Es adecuado el control de los parámetros pasados por el usuario que se hace en las funciones implementadas? ¿Se controla que sean valores válidos? ¿Se controla que estén dentro de los rangos correctos?

Sí, el control de los parámetros actualmente es adecuado, ya que se verifica que el puntero no sea NULL.
En el valor del delay se valida que no sea cero; el límite superior no es necesario, ya que no se puede almacenar un número mayor a 4.294.967.295 (solo si se quisiera limitar a un tiempo específico) y
los valores negativos se controlan con el tipo de dato sin signo (uint32_t).

### ¿Cuán reutilizable es el código implementado? 

El código implementado mantiene un alto nivel de reutilización debido a que las funciones para manejo de delay no bloqueante solo llaman a la función HAL_getTick() 
que está disponible en toda la familia STM32, por lo que estas podrían migrar a otros microcontroladores de esta familia.

### ¿Cuán sencillo resulta en su implementación cambiar el patrón de tiempos de parpadeo?

Solo se requiere cambiar el tamaño del vector en la variable VECTOR_SIZE y los valores de tiempo en su definición.