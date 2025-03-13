# HuskyLens + Arduino Mega 2560

## 1. Potencia y Alimentación
- **Consumo de HuskyLens**: 310mA@3.3V o 220mA@5V.
- **Arduino Mega 2560**:
  - Regulador de 5V soporta hasta 800-1000mA, pero puede sobrecalentarse si se exige demasiado.
  - Mejor usar una fuente de **5V, 2A o más**, conectada directamente al **5V/GND** del Mega.
  - **No conectar periféricos de alto consumo al Mega**, sino directamente a la fuente de alimentación para evitar sobrecargas.
  - [Foro sobre la potencia de mega 2560](https://forum.arduino.cc/t/max-current-draw-mega-2560/680799/4)
  - [Datasheet de Arduino](https://docs.arduino.cc/resources/datasheets/A000067-datasheet.pdf)
  
## 2. Instalación de Arduino IDE en Linux
- Se descargó el archivo **tar** y se ejecutó el instalador automáticamente (detalles en `installed.txt`).
- Se creó y probó el archivo `print_1.ino`, que imprime una cadena correctamente en el **Monitor Serie** con la configuración de baudios adecuada.

## 3. Instalación de la Librería HuskyLens
- Se descargó desde GitHub y el tutorial oficial:
  - [Repositorio GitHub](https://github.com/HuskyLens/HUSKYLENSArduino)
  - [Tutorial Oficial](https://wiki.dfrobot.com/HUSKYLENS_V1.0_SKU_SEN0305_SEN0336#target_28)
- Ambas versiones fueron descargadas e importadas en el IDE de Arduino usando **Sketch > Incluir Librería > Añadir ZIP**.
- Las librerías están en `~/Arduino/libraries` y se pueden incluir en los programas con `#include <HUSKYLENS.h>`.

## 4. Conexión de HuskyLens con Arduino Mega 2560
- **Serial1 (Hardware UART)**:
  - Se probó la conexión con `Serial1`, pero no se estableció comunicación.
  - **Se detectó un error en la serigrafía de la placa Mega 2560:** los pines RX1/TX1 están etiquetados al revés.
  - **Solución:** Invertimos las conexiones RX/TX y HuskyLens funcionó perfectamente.
- **SoftwareSerial**:
  - Probamos un código de la documentación con `SoftwareSerial` y funcionó sin problemas.
  - Se confirma que Arduino Mega 2560 tiene excelente estabilidad con este método.

## 5. Pruebas y Resultados
- Los programas funcionan correctamente.
- Se puede cambiar el algoritmo de HuskyLens fácilmente con:
  ```cpp
  huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING);
  ```
- La documentación en GitHub es clara y útil.

## 6. Proyecto Autonomous Car
- Revisaremos el **Terrenator-Arduino** para adaptarlo y agregar HuskyLens.
- Se conectará HuskyLens directamente a una **fuente de alimentación de 5V** para evitar sobrecargar el Arduino Mega.

# Documentación del Código: HuskyLens con Arduino Mega 2560
cesar@asus:~/Arduino/huskylens_serial1

## Descripción
Este programa establece comunicación entre un **Arduino Mega 2560** y el sensor **HuskyLens** mediante **UART (Serial1)**. Configura HuskyLens en modo **Object Tracking**, solicita datos y los muestra en el Monitor Serie.

## Requisitos
- **Hardware:** Arduino Mega 2560, HuskyLens, cables de conexión.
- **Software:** Arduino IDE, librería HuskyLens ([GitHub](https://github.com/HuskyLens/HUSKYLENSArduino)).

## Conexión
| HuskyLens | Arduino Mega 2560 |
|-----------|------------------|
| TX (Verde) | RX1 (Pin 19) |
| RX (Azul) | TX1 (Pin 18) |
| GND | GND |
| VCC | 5V |

## Funcionamiento
1. **Inicialización (`setup()`)**
   - Inicia `Serial` (115200) y `Serial1` (9600).
   - Verifica la conexión con HuskyLens.
   - Activa el modo **Object Tracking**.

2. **Bucle Principal (`loop()`)**
   - Solicita datos a HuskyLens.
   - Verifica si ha aprendido un objeto.
   - Imprime la detección en el Monitor Serie.

3. **Impresión de Resultados (`printResult()`)**
   - Muestra posición y tamaño de los objetos detectados.
   - Identifica coordenadas de flechas si están disponibles.

## Salida Esperada
```
###########
Block: xCenter=150, yCenter=120, width=50, height=60, ID=1
```

##########################################################################################################################################################
##########################################################################################################################################################
##########################################################################################################################################################


# Documentación del Código: Control Bluetooth para BLUE RC JFK v3
cesar@asus:~/Arduino/Blue_RC_JFK_v2

## Descripción
Este programa permite el control de un vehículo a través de comandos Bluetooth enviados en formato `l#r#`, donde `#` representa un valor entre **0 y 255** para los motores izquierdo y derecho.

## Requisitos
- **Hardware:** Arduino, módulo Bluetooth, motores, controladora de motores.
- **Software:** Arduino IDE, librería `SoftwareSerial`.

## Conexión
| Componente | Pin Arduino |
|------------|------------|
| Bluetooth RX | 3 |
| Bluetooth TX | 2 |
| Motor A Forward | 6 |
| Motor B Forward | 5 |
| Motor A Control | 7, 8 |
| Motor B Control | 12, 13 |
| Tono | 10 |

## Funcionamiento
1. **Inicialización (`setup()`)**
   - Configura los pines de control de motores.
   - Inicializa la comunicación **Bluetooth (9600 baudios)**.
   - Reproduce tonos de inicio (`Play7Char`, `Play3Char`).

2. **Recepción de Comandos (`loop()`)**
   - Escucha datos Bluetooth y almacena la cadena recibida.
   - Si el formato es correcto (`l#r#`), extrae y convierte los valores de los motores.
   - Asigna los valores de **potencia (PWM)** a los motores.

## Notas y Correcciones
- **Corrección de pines:** Se reasignó `pin_motor_a_forward` a **6** para que el mando izquierdo controle la rueda derecha.
- **Optimización:** Se eliminaron `Serial.print` para evitar retrasos en la ejecución.




##########################################################################################################################################################
##########################################################################################################################################################
##########################################################################################################################################################

## Project 0: Search and KnockDown:
Para hacer una versión más simple del proyecto, donde el robot se dirige hacia el objeto detectado, lo derriba, y luego realiza una maniobra de búsqueda hasta encontrar otro objeto, se puede seguir la siguiente estructura básica:

**LLMS Assistants:**
https://chat.deepseek.com/a/chat/s/af75c7e9-1dbd-4faa-ac9e-2fb245f79830

### 0. **Carpetas y avances**
   - **Folders**
     Real directory for compiling: ~/Arduino
     (~/Documents/1Robodinamica/huskylens/autonomous-car)
     - search-and-knockdown.ino 
		Version para la mega(utiliza Serial1)
     - search-and-knockdown-uno-version.ino
		Utilizamos SoftwareSerial
	 - huskylens-com-search-knockdown.ino
		Conseguimos conexion e interaccion con el entorno	 
	 - ~/Arduino/motors_test (created at 13/03/2025)
	    Lo descargamos del repositorio RC-development para hacer pruebas antes de la implementacion real de motores
	    El tone funciona correctamente sin cambios
	    Los motores funcionan correctamente de forma estable en la mesa.
	    Corregido el sentido de la marcha.
	    Test de motores en el suelo exitoso, no perdemos la conexion(23:50).
	 - ~/Arduino/motors_test2
	    Hacemos cambios para que los motores funcionen de forma continua
	 - huskylens-com-search-knockdown2 
	    Implementamos el control de motores	
	    
   - **Progress**
     - Software
		Hemos configurado los pines de tone y de huskylens
		Hemos actualizado la funcion loop para evitar el nest excesivo y aumentar la eficiencia
		Incluido control proporcional en moveTowardsObject
		searchForNextObject no tiene delay, se mueve en circulos siempre que se cumpla !huskylens.available()
		Incluidos: byte baseMotorSpeed = 200; byte leftSpeed = 0; byte rightSpeed = 0;
		Al principio no conseguiamos ejecutar los tone, hemos tenido que cambiar la sintaxis para que funcione: PlayChar("f"); => PlayChar('f');
		Al hacer funcionar el buzzer vemos que el codigo queda aqui:
		while (!huskylens.begin(Serial)) {
			//Serial.println(F("Fail com. Huskylens"));
			PlayChar('f');
			delay(300);
		}
		No conseguimos comenzar la comunicacion. Probaremos a quitar todo el cableado y conectarnos con scripts simples => solucionado, era problema con GND
		
		No conseguimos hacer funcionar el morse con Play3Char y sucesivos, vamos a hacer pruebas
		Hemos hecho funcionar el morse correctamente en: /home/cesar/Arduino/prueba-buzzer2
		void MorseDot() { tone(pinTone, NOTE_A4);  delay(dotLen); noTone(pinTone);  delay(dotLen);  }
		PlayChar('f'); Play3Char("set"); delay(300); Play7Char("pruebaj");
		
		Ahora conseguimos conectar las huskylens con huskylens-software-serial pero no con search-knockdown; vamos a hacer una copia de
		cp huskylens-software-serial huskylens-com-search-knockdown
		**huskylens-com-search-knockdown**: por primera vez conseguimos huskylens y morse
			El codigo reproduce morse de forma correcta e informa por println; El robot interactua de forma correcta ejecutando move() y marcando potencias proporcionales al error en los motores.
			Cuando no detecta el objeto ejecuta circle correctamente.
		**huskylens-com-search-knockdown2**: implementamos el control de motores	
		
		(13/03/2025)
		
		
     - Hardware
	    Vamos a cambiar el pin del Tone del 10 al 11 con el fin de dejar espacio y poder utilizar los pines de huskylens en 9 y 10
	    Al tener conectada las huskylens a una fuente aparte tenemos diferentes potenciales por lo que no nos podemos conectar por UART entre Arduino y 
	    Huskylens: https://forum.arduino.cc/t/l298n-motor-driver-ground-connection-with-arduino/929056/4
	    Hemos conectado un cable entre el GND del L298N y un pin GND de arduino, ya tenemos conexion correcta con Huskylens usando SoftwareSerial
	    
	    (13/03/2025)
	    **Optimizacion de los puertos:** Los pines de potencia del puente H siempre reciben la misma signal while we plan our routes to make the wheels move in the same direction, thus, we could supply them with a constant 5V from the 5V pin and GND for the LOW pins. This will give us 4 extra free ports.
	    
	    Hemos cometido el fallo de conectar los reguladores de lo motores a pines que no son PWM
### Objetivos del Proyecto Simplificado:
1. **Detección de Objetos**: El robot detecta objetos con Huskylens.
2. **Dirigirse hacia el objeto**: Una vez detectado, el robot se dirige hacia el objeto.
3. **Impactar y Derribar el objeto**: El robot se mueve hacia el objeto hasta hacer contacto con él, lo derriba.
4. **Búsqueda de otro objeto**: Tras derribar el objeto, el robot realiza una maniobra de búsqueda hasta encontrar otro objeto y repetir el proceso.

### Descripción del Código:

1. **Detección de objetos con HuskyLens**: 
   - Usamos la función `request()` para obtener datos de HuskyLens, y si hay un objeto detectado, obtendremos las coordenadas del objeto con `read()`.
   
2. **Movimiento hacia el objeto**:
   - La función `moveTowardsObject()` hace que el robot se mueva hacia el objeto. Dependiendo de su posición (`xCenter`), el robot ajustará su dirección (giro a la izquierda, a la derecha o avance directo).
   
3. **Derribar el objeto**:
   - La función `knockDownObject()` simula el impacto del robot con el objeto y luego se detiene brevemente.

4. **Búsqueda de otro objeto**:
   - Después de derribar el objeto, la función `searchForNextObject()` ejecuta una maniobra de búsqueda, en este caso, un movimiento circular, para encontrar el siguiente objeto.

5. **Control de motores**:
   - Las funciones `moveForward()`, `turnLeft()`, `turnRight()` y `moveInCircle()` controlan los motores del robot para que se mueva en la dirección adecuada.

### Mejoras posibles:
- Implementar una mejor maniobra de búsqueda, como un patrón en zigzag o un barrido más eficiente.
- Incorporar una mejora en el manejo de la distancia con el objeto para ajustar el movimiento y evitar que el robot se quede "pegado" al objeto.
- Añadir un sensor de proximidad para detectar el impacto real o para asegurarse de que el objeto ha sido derribado.
- **Optimizacion de los puertos:** Los pines de potencia del puente H siempre reciben la misma signal while we plan our routes to make the wheels move in the same direction, thus, we could supply them with a constant 5V from the 5V pin and GND for the LOW pins. This will give us 4 extra free ports.
 




## Project 1: Autonomous Explorer: Explorador Autónomo con Mapa Dinámico

### 0. **Carpetas y avances**
   - **Folders**
     - detection-process-maneuver.ino
### 1. **Definición de Objetos y Zonas**
   - **Objetivos:**
     - Definir un conjunto de objetos que el robot debe reconocer.
     - Asignar un código o una ID a cada objeto que represente una maniobra específica.
   - **HuskyLens:** Puedes utilizar HuskyLens para identificar objetos en el entorno y asignarles un identificador único. Esto permitirá que el robot sepa qué hacer cuando detecte cada objeto.
   - **Ubicación Predefinida:** Los objetos pueden estar distribuidos en la zona, y el robot puede memorizar estas ubicaciones para saber a dónde ir a continuación.

### 2. **Planificación de las Maniobras**
   - **Objetivos:**
     - Asignar una maniobra (como movimiento hacia adelante, rotación, retroceso, etc.) para cada objeto detectado.
     - Crear un flujo de trabajo donde el robot navegue a través de la zona en función de los objetos que detecta.
        
### 4. **Comunicación con Bluetooth**
     - Enviar información de la posición del robot y los objetos detectados a un dispositivo móvil en tiempo real: (ID, tipo, y posible posición)
### 6. **Flujo Básico del Sistema**
   - **Inicio:**
     - El robot comienza en un punto inicial.
   - **Detección de Objeto:**
     - Usa HuskyLens para detectar el primer objeto en el área.
   - **Ejecución de Maniobra:**
     - El robot realiza la maniobra asociada con el objeto detectado.
   - **Envío de Información:**
     - Se envía la información del objeto detectado y la ubicación del robot a través de Bluetooth al móvil.
   - **Repetir Proceso:**
     - El robot continúa buscando objetos y repitiendo el ciclo hasta que termine el recorrido o se detenga por intervención manual.

### 8. **Consideraciones Adicionales**
   - **Manejo de Obstáculos:** Si el robot se encuentra con un obstáculo inesperado, podrías integrar sensores adicionales (como ultrasónicos o LIDAR) para evitarlo y continuar el recorrido.
   - **Optimización de Rutas:** Con el tiempo, podrías añadir funciones para que el robot optimice sus rutas basadas en el entorno detectado o para evitar áreas problemáticas.
   - **Interfaz Móvil:** La aplicación móvil que recibe la información Bluetooth podría mostrar en tiempo real la ubicación del robot y los objetos que ha detectado, permitiendo al operador tener una visión del mapa.
   - **Objetivos:**
     - A medida que el robot explore, podrá crear un mapa de la zona. Este mapa no solo contendrá las posiciones de los objetos, sino también las rutas que ha seguido.
   - **Tecnología:**
     - Utilizar un sistema de localización, como encoders de los motores y/o un sensor IMU para estimar la posición relativa del robot en el espacio.
     - El robot podría almacenar información sobre su entorno, como distancias recorridas, objetos detectados y coordenadas relativas.
   - **Tecnología:** Algoritmos de navegación con motores y control de actuadores.
   - **Optimizacion de los puertos:** Los pines de potencia del puente H siempre reciben la misma signal while we plan our routes to travel in the same direction, thus, we could supply them with a constant 5V from the 5V pin and GND for the LOW pins. This will give us 4 extra free ports.
   


