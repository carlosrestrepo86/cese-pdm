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
git clone https://github.com
```
Abre **STM32CubeIDE**, ve a `File -> Import -> Existing Projects into Workspace` y selecciona la carpeta raíz del proyecto.

## 📂 Estructura del Código de la API
El proyecto organiza el control del periférico separando la lógica de los datos para evitar dependencias circulares:
```text
📂 Core
 ├── 📂 Inc
 │    ├── API_types.h  <-- Estructuras de datos, Enums y Macros de configuración.
 │    ├── API.h        <-- Interfaz pública con prototipos de funciones.
 │    └── main.h
 └── 📂 Src
      ├── API.c        <-- Implementación lógica y control de hardware de la API.
      └── main.c
```

## 🛠️ Diagnóstico de Errores
El proyecto cuenta con dos mecanismos de contención:
- **`Error_Handler()`**: Se activa ante fallos críticos de hardware del HAL (bloquea el MCU y parpadea el LED de emergencia).
- **`assert_failed()`**: Captura errores de paso de parámetros inválidos en las funciones HAL e imprime la línea y archivo exacto por la consola UART antes de congelar el sistema.
