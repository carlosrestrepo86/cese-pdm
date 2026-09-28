# Práctica 5 de la Carrera de Especialización en Sistemas Embebidos
> Implementar un módulo de software para utilizar la UART y una MEF para parsear comandos recibidos por UART en modo polling.

## Características principales
- Comunicación UART mediante USART2 (puerto USB para programar).
- Configuración de comunicación:
    - Baudrate: 115200 bps
    - Bits de datos: 8
    - Paridad: None
    - Bits de parada: 1
- Recepción de comandos mediante una máquina de estados finitos (MEF).
- Comandos separados mediante espacio (comando argumento).
- Terminación de línea mediante CR (\r) y LF (\n).
- Comandos disponibles:
    - LED ON — enciende el LED.
    - LED OFF — apaga el LED.
    - LED TOGGLE — cambia el estado del LED.
    - STATUS — consulta el estado actual del LED.
    - HELP — muestra los comandos disponibles.
- Las líneas que comienzan con # o // son tratadas como comentarios e ignoradas.
- Las tramas con formato o comandos no válidos son detectadas y manejadas como errores.
- El procesamiento de comandos es independiente de la ejecución de las acciones.

## Uso mediante terminal UART
El sistema puede utilizarse desde cualquier terminal serial que permita configurar una conexión UART, como RealTerm o PuTTY.

### Configuración de la conexión

Utilizar los siguientes parámetros:

    - Puerto	COM correspondiente a la Nucleo
    - Baudrate	115200
    - Data bits	8
    - Paridad	None
    - Stop bits	1
    - Flow control	None

El número de puerto COM depende del equipo y de la conexión de la placa.

- RealTerm
    -  Conectar la placa STM32 al computador mediante USB.
    - Identificar el puerto COM asignado a la placa.
    - Abrir RealTerm.
    - Seleccionar el puerto COM correspondiente.
    - Configurar:
        -   Baud: 115200
        -   Data Bits: 8
        - Parity: None
        - Stop Bits: 1
        - Flow Control: None
- Abrir el puerto serial.
- Escribir uno de los comandos disponibles y enviarlo utilizando la terminación de línea configurada.
- Ejemplos
    - LED ON\n\r Encender led (obligatorio agregar \r o \n).

    - LED OFF\n\r Apagar led (obligatorio agregar \r o \n).

    - LED TOGGLE\n\r Cambiar el estado del led (obligatorio agregar \r o \n).

    - STATUS\n\r Consulta el estado del LED.

    - HELP\n\r Muestra los comandos disponibles.


## Requisitos de Hardware y Software

### Hardware
- **Microcontrolador:** STM32F446RE
- **Placa de desarrollo:** NUCLEO-F446RE

### Software e Interfaz
- **IDE:** STM32CubeIDE (Versión 2.2.0)

## Configuración y Uso

### Clonar y Abrir el Proyecto

```bash
git clone https://github.com/carlosrestrepo86/cese-pdm.git
```
Abre **STM32CubeIDE**, ve a `File -> Import -> Existing Projects into Workspace` y selecciona la carpeta raíz del proyecto.

## 📂 Estructura del Código de la API
El proyecto organiza el blink del led separando la lógica del delay no bloqueante y anti-rebote del código principal "main.c":

```text
📂 practica_5
 ├── 📂 Core
 │    ├── 📂 Inc
 │    │    └── main.h         <-- Definiciones globales y prototipos del sistema.
 │    └── 📂 Src
 │         └── main.c         <-- Punto de entrada principal y bucle de control.
 └── 📂 Drivers
      └── 📂 API
           ├── 📂 inc
           │    └── API_cmdparser.h <-- Interfaz pública de la API para parsear los comandos (prototipos).
           │    └── API_delay.h     <-- Interfaz pública de la API de retardos (prototipos).
           │    └── API_uart.h      <-- Interfaz pública de la API para la UART (prototipos).
           └── 📂 src
                └── API_cmdparser.c <-- Implementación lógica para parsear los comandos.
                └── API_delay.c     <-- Implementación lógica de los retardos.   
                └── API_uart.c      <-- Implementación lógica de la UART.         
```
