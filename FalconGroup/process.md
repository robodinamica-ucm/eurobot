### **📄 Documentación del Proyecto: Robot con Ruedas Mecanum**  
**Plataforma:** Arduino Mega 2560  
**Motores:** 4 motores TT con ruedas mecanum  
**Drivers de motor:** 2x HW-627 (MX1508)  
**Batería:** 4x 18650 (8.4V, 2S2P)  
**Regulador de Voltaje:** Mini 360 Buck Converter  

---

## **1️⃣ Introducción**
Este documento describe el sistema de control para un robot diseñado para la Eurobot 2025. El robot utiliza un **Arduino Mega 2560**, **dos drivers HW-627**, y **cuatro motores TT** para lograr desplazamientos multidireccionales.

---

## **2️⃣ Arquitectura del Sistema**
### **2.1. Estructura del Hardware**
El sistema está compuesto por los siguientes módulos:
- **Controlador principal:** Arduino Mega 2560, que gestiona la lógica de control del robot.
- **Módulo de potencia:** Regulador Mini 360 Buck Converter, encargado de reducir el voltaje de 8.4V a 5V para alimentar el Arduino.
- **Actuadores:** Cuatro motores TT con ruedas mecanum, controlados mediante dos drivers HW-627.
- **Drivers de motor:** HW-627, que permite el control bidireccional de los motores sin necesidad de pines de activación (ENA).

### **2.2. Conexión de los Componentes**
Los motores están conectados a los pines del Arduino Mega 2560 de la siguiente manera:
- **Motor delantero izquierdo (FL):** IN1 (2), IN2 (3)
- **Motor delantero derecho (FR):** IN1 (4), IN2 (5)
- **Motor trasero izquierdo (RL):** IN1 (6), IN2 (7)
- **Motor trasero derecho (RR):** IN1 (8), IN2 (9)

El Buck Converter alimenta el Arduino Mega 2560 a través del pin **Vin**.

---

## **3️⃣ Modos de Operación**
El sistema soporta los siguientes movimientos mediante una lógica específica de control:
- **Avance y retroceso**
- **Desplazamiento lateral**
- **Rotación sobre su eje**

Para lograr el desplazamiento lateral, es necesario un **patrón de giro especial** en las ruedas mecanum:
| Movimiento      | Motor FL | Motor FR | Motor RL | Motor RR |
|---------------|---------|---------|---------|---------|
| Adelante      | ⬆️ | ⬆️ | ⬆️ | ⬆️ |
| Atrás         | ⬇️ | ⬇️ | ⬇️ | ⬇️ |
| Derecha       | ⬆️ | ⬇️ | ⬇️ | ⬆️ |
| Izquierda     | ⬇️ | ⬆️ | ⬆️ | ⬇️ |
| Rotación CW   | ⬆️ | ⬇️ | ⬆️ | ⬇️ |
| Rotación CCW  | ⬇️ | ⬆️ | ⬇️ | ⬆️ |

El código está diseñado para permitir **aceleración progresiva**, logrando movimientos más suaves y eficientes.

---

## **4️⃣ Software y (TODOs)**
🔹 **Development:**
- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement.ino
	- **`moveForward(int speed)`**: Controla los motores para avanzar en línea recta. - **`moveBackward(int speed)`**: Ejecuta el retroceso del robot. - **`moveRight(int speed)`**: Permite el desplazamiento lateral hacia la derecha. - **`moveLeft(int speed)`**: Realiza el desplazamiento lateral hacia la izquierda. - **`rotateClockwise(int speed)`**: Gira el robot en sentido horario. - **`rotateCounterClockwise(int speed)`**: Gira en sentido antihorario. - **`stopMotors()`**: Detiene todos los motores.  
	- Estamos ajustando el parametro de **velocidad en moveLeft** para conseguir movimiento horizontal real
		Velocidad de las delanteras entre 2.5
	- Adicion de **comunicacion morse** para tener interaccion antes de implementar ultrasonidos
		Copiamos morse.ino de knockdown5, ponemos el pin, OUTPUT, play3Char
	
	- **Obstacle detection**: comenzamos con printeo de distancias para comprobar que funciona correctamente; despues comunicamos detecciones por morse;
		despues giros tras deteccion de objetos frontales
		Funcional pero hay que hacer cambios importantes para llevar los procesos de interaccion y potencia en paralelo

- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement2.ino		
	- corregir problemas de gpt
	- Eliminamos completamente los **delay()** para poder ejecutar updateDistance() con frecuencia constante.
	- La distancia la estamos **midiendo con mucha precision**, deteniendo las acciones cuando percibe algo a menos de safetyDistance
	- La deteccion de obstaculos no es lo suficientemente rapida como para evitar chocarse, reducimos la velocidad y aumentamos safetyDistance
	- **Ajuste moveLeft:** reducimos la velocidad de RL y RR para evitar derrape excesivo, reducimos aun mas la velocidad en FL y FR
	- **initial trayectory:** introducimos la funcion pushStructure(bool direction), en el loop hacemos front, rotate, pushStructure(0) para empujar una estructura situada a nuestra izquierda
	- **Ajustes finos:** La rotacion es muy larga, en moveLeft las delanteras estan demasiado reducidas y no giran, las traseras van demasiado rapido.
		Las trayectorias funcionan mejor pero el movimiento lateral sigue sin funcionar
		
- ~/Arduino/mecanumSidewaysTest
	- Cada motor tiene una curva caracteristica demasiado diferente como para poder poner unos parametros funcionales facilmente
	
- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement3.ino		

	- Evitamos los movimientos laterales: avance, rotacion 90 clockwise(cw), avance hasta tener el muro a la distancia apropiada, rotacion 90 cw, empujamos
	- moveForwardToApproach(float distance)
	- const int decelDelay = 10; => 1 para obtener movimientos mas cortos sin sacrificar velocidad ni precision
	- Tenemos que solucionar la logica if (currentDistance < safetyDistance) { pues puede entrar en un bucle sin volver a ejecutar updateDistance()

- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement4.ino			
	- logica if (currentDistance < safetyDistance) => hacemos updateDistance() antes de ejecutar nuevos comandos.
	- quitamos la deceleracion suave para quitar carga de trabajo.
	- ajustamos speed a 50 en **accelerateSafely** para respuesta mas rapida
	- Cuando no alimentamos el ultrasonidos lee incorrectamente y registra distancia 0 lo que puede llevar a errores
	- quitamos la condicion temporal en **updateDistance()**  
	- quitamos el timout //long duration = pulseIn(echoPin, HIGH, 25000); // 25 ms max timeout
	
- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement5.ino			
	-  Trayectoria inicial para dirigirse a la estructura, desplazarse y empujarla	**FUNCIONAL**
	
- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement6.ino				
	- Implementamos lateralRightDistance() y lateralLeftDistance() que devuelvan float con los ultrasonidos laterales
	- Ajustamos una distancia de deteccion lateral para saber cuando estamos sobrepasando las latas
		Funcion: moveParallelToObject(float perpendicularDistance, float distanceToTravellSinceDetection)
		Nos encontramos avanzando hacia la estructura. Una vez que el sensor derecho detecta una distancia menor a un cierto
		umbral determinado por perpendicularDistance comienza a medir la distancia paralela que estamos recorriendo y continua
		avanzando hasta llegar a distanceToTravellSinceDetection.
		Podemos aproximar la distancia viajada(distanceTravelled) experimentalmente midiendo velocidades 
	
		
	- Funcion para determinar el angulo en el que nos encontramos utilizando la informacion de ultrasonidos
		
	- trayectoria completa con empuje

- ~/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/mecanum-basic-movement7.ino				
	- Abandonamos la version 6. Comenzamos desde la 5. Queremos continuar con la serie de trayectorias
		0. Empujar las latas(conseguido en v5), debemos poner un parametro para cuanto debemos empujar
			Push structure es innecesaria, no la vamos a utilizar
			
		1. Retroceso, 90 izquierda, avanzar, 90 izquierda
			Debemos modificar accelerate safely para poner un parametro que pueda regular mejor la distancia que vamos a recorrer
			/home/cesar/Documents/1Robodinamica/eurobot/avances/eurobot/FalconGroup/accelerate-safely-test.ino
			Utilizamos integracion de la velocidad, vamos a testearlo y ajustar los parametros
			PlayChar('i'); no funciona con comillas dobles.
			Cuando hacemos play3char con un caracter reproduce una s al final, debe ser el caracter final de string
			
			Solo tenemos que asegurarnos de hacer un giro de 90 confiable, no necesitamos otras maniobras
			accelerateSafely: int speed = 30; => int speed = 80;
			Hemos quitado la frenada con la condicion temporal en accelerateSafely. Ahora tenemos 90+/-2 para los giros
			funcion con resultados accelerate-safely-test3.ino
				Todos los resultados son tomados con PWM 160 por lo que nos quedaremos con esa para la competicion excepto para la recta larga.
				La distancia recorrida es 3.2, 3.375, 3.43 veces mayor que la indicada en el argumento de accelerateSafely(la constante cambia al utilizar diferentes distancias por lo que cada vez el efecto de la aceleracion progresiva es menor, esto puede dar imprecisiones relevantes para distancias cortas).
				
				const float speedToCMsFactor = 0.1; => 0.33
				Los giros de 90 eran con 8 o 9 cm recorridos por lo que ahora tenemos 26.4 o 29.7 para los 90
		
			Introducimos los cambios de accelerate-safely-test3 al codigo(modificamos el speedFactor)		
			
			latas a 300mm(ancho robot 22 cm). Giro a la derecha. Avanzamos hasta tener la pared frontal a 775mm o las latas a 650mm. Derecha, empujar. Retrocedemos 20cm. Giro a la izquierda. Avanzamos hasta las latas frontales. Giro izquierda. Avanzamos hasta la pared del aparcamiento(1700mm).
			
			

		2. Comprobar que estamos alineados con el tablero
		3. Avanzar hasta el aparcamiento comprobando nuestro angulo en todo momento
		4. Alinearnos usando la pared y asegurarnos que nos encontramos dentro del area
		
	- Poner unos parametros claros al principio del programa que permitan su rapida configuracion en el momento
	
	
🔹 **Tareas planeadas:**
- [x] Morse para comunicacion efectiva.
- [x] Añadir detección de obstáculos con ultrasonidos basico.
	Utilizamos los ultrasonidos para poder detectar las paredes y las estructuras
- [x] Trayectoria inicial para dirigirse a la estructura, desplazarse y empujarla
- [ ] Implementacion de ultrasonidos laterales
- [ ] Trayectoria completa hasta aparcamiento	
- [ ] Funcion extra para programar en nivel mas alto: pasamos direccion, velocidad y la distancia que queremos recorrer
- [ ] Integrar uso de encoders.
- [ ] Implementar un control de velocidad con PID.
- [ ] Integrar comunicación Bluetooth/Wifi para control remoto.
- [ ] Mejorar la estabilidad en giros con ajuste de aceleración.
- [ ] Implementar uso de matriz de ultrasonidos
- [ ] Coordinar con los sensores TOF y encoders
- [ ] Programar trayectoria completa teniendo en cuenta cualquier posible excepcion en el trayecto
- [ ] Programacion de tests
- [ ] Programar otras variantes para el caso de desorientacion 
- [ ] Programar trayectorias para las otras 2 zonas de salida

🔹 **Posibles expansiones:**
- Implementación de algoritmos de optimización de trayectorias.

---

## Anexos:

### Error cargar Arduino Mega 2560 
el usuario no tiene los permisos necesarios para acceder al puerto serie `/dev/ttyUSB0`. Este es un problema común en sistemas Linux y puede resolverse siguiendo estos pasos: ([Upload failure due to permission denial - Arduino Forum](https://forum.arduino.cc/t/upload-failure-due-to-permission-denial/1182637?utm_source=chatgpt.com))

---

#### 🔧 Solución paso a paso

1. **Verificar el grupo del puerto serie**

   Ejecuta el siguiente comando en la terminal para verificar el grupo asociado al puerto:

   ```bash
   ls -l /dev/ttyUSB0
   ```

   La salida debería mostrar algo similar a:

   ```
   crw-rw---- 1 root dialout ... /dev/ttyUSB0
   ```

   Esto indica que el grupo `dialout` tiene permisos de lectura y escritura en el puerto.

2. **Agregar tu usuario al grupo `dialout`**

   Para otorgar a tu usuario los permisos necesarios, agrégalo al grupo `dialout` con el siguiente comando:

   ```bash
   sudo usermod -a -G dialout $USER
   ```

   Después de ejecutar este comando, es necesario cerrar la sesión y volver a iniciarla para que los cambios surtan efecto. 

3. **Verificar los grupos de tu usuario**

   Una vez que hayas iniciado sesión nuevamente, verifica que tu usuario pertenezca al grupo `dialout`:

   ```bash
   groups
   ```

   Deberías ver `dialout` listado entre los grupos de tu usuario.

4. **Probar la carga del sketch**

   Intenta cargar tu sketch nuevamente desde el IDE de Arduino. Si todo está configurado correctamente, el error de permiso debería haber desaparecido.

---

#### ⚠️ Solución temporal (no recomendada)

Si necesitas una solución inmediata y temporal (por ejemplo, para una prueba rápida), puedes cambiar los permisos del puerto directamente:

```bash
sudo chmod a+rw /dev/ttyUSB0
```


Ten en cuenta que esta solución es temporal y los permisos se restablecerán cuando el dispositivo se desconecte o el sistema se reinicie. 

---

#### 🛠️ Consideraciones adicionales

- **Uso de dispositivos con chip CH340**: Si tu Arduino Mega utiliza un chip CH340 para la interfaz USB-serial, asegúrate de tener instalados los controladores adecuados para este chip en tu sistema.

- **Reglas de udev personalizadas**: En algunos casos, puede ser necesario crear reglas de udev para asignar los permisos correctos al puerto serie de forma persistente. Sin embargo, agregar tu usuario al grupo `dialout` suele ser suficiente en la mayoría de los casos. ([Upload failure due to permission denial - Arduino Forum](https://forum.arduino.cc/t/upload-failure-due-to-permission-denial/1182637?utm_source=chatgpt.com))

Si después de seguir estos pasos el problema persiste, por favor proporciona más detalles sobre tu sistema operativo y la configuración de tu entorno de desarrollo para poder asistirte mejor. 
