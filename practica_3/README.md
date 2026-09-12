# Práctica 3 de la Carrera de Especialización en Sistemas Embebidos
> Implementación de un módulo para trabajar con retardos no bloqueantes.

## Características principales
- Generación de un blink en led "LD2" utilizando las funciones del módulo.
- API dedicada para el manejo de las funciones del delay.
- El led trabaja con un ciclo de dureza de 50%.
- Se puede generar varias señales con diferentes tiempos, estas señales se definen con dos arreglos:
	- const uint32_t TIEMPOS[] = {500, 100, 100, 1000}; define los tiempos de las señales. Tiene 4 señales definidas
	- const uint8_t REPETICIONES [] = {1, 1, 1, 1};     define la cantidad de veces que se repite la señal.
- Gestión de errores en los parámetros recibidos por las funciones mediante.

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
El proyecto organiza el blink del led separando la lógica del delay no bloqueante del código principal "main.c":

```text
📂 Mi_Proyecto_STM32
 ├── 📂 Core
 │    ├── 📂 Inc
 │    │    └── main.h         <-- Definiciones globales y prototipos del sistema.
 │    └── 📂 Src
 │         └── main.c         <-- Punto de entrada principal y bucle de control.
 └── 📂 Drivers
      └── 📂 API
           ├── 📂 Inc
           │    └── API_delay.h  <-- Interfaz pública de la API de tiempos (prototipos).
           └── 📂 Src
                └── API_delay.c  <-- Implementación lógica de los retardos.
```

## Diagnóstico de Errores
El proyecto cuenta con un mecanismo de contención:
- **`API_Error_Handler()`**: Se activa cuando a las funciones de control de delay se le envian parámetros erroneos (ejemplo puntero NULL o tiempo del delay en 0).
