# Práctica 4 de la Carrera de Especialización en Sistemas Embebidos
> Implementación de una máquina de estados finitos (MEF) para trabajar con anti-rebotes por software.

## Características principales
- Generación de un blink en led "LD2" utilizando las funciones del módulo.
- El tiempo de parpadeo del led se puede cambiar entre 100 ms y 500 ms mediante el boton "B1".
- API dedicada para el manejo de las funciones del delay no bloqueante.
- API dedicada para el manejo de la MEF que se encarga del anti-rebote.
- Gestión de errores en los parámetros recibidos por las funciones.

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
📂 practica_4
 ├── 📂 Core
 │    ├── 📂 Inc
 │    │    └── main.h         <-- Definiciones globales y prototipos del sistema.
 │    └── 📂 Src
 │         └── main.c         <-- Punto de entrada principal y bucle de control.
 └── 📂 Drivers
      └── 📂 debounce
           ├── 📂 Inc
           │    └── API_debounce.h  <-- Interfaz pública de la API para anti-rebote (prototipos).
           └── 📂 Src
                └── API_debounce.c  <-- Implementación lógica del anti-rebote.
           📂 delay
           ├── 📂 Inc
           │    └── API_delay.h     <-- Interfaz pública de la API de tiempos (prototipos).
           └── 📂 Src
                └── API_delay.c     <-- Implementación lógica de los retardos.
```

## Diagnóstico de Errores
El proyecto cuenta con un mecanismo de contención:
- **`API_Error_Handler()`**: Se activa cuando a las funciones de control de delay se le envian parámetros erroneos (ejemplo puntero NULL o tiempo del delay en 0).
