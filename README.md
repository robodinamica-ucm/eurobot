# eurobot
Repositorio del proyecto Eurobot 2025, categoría senior. Incluye estrategia, diseño mecánico, electrónica avanzada, y software para construir un robot autónomo que manipula latas, despliega carteles y evita obstáculos. Documentación completa, código, diseño CAD y resultados de pruebas. 🚀


**Eurobot 2025 - Proyecto de Robótica Competitiva**  

Este repositorio documenta el diseño, desarrollo y ejecución de nuestro robot para la competición Eurobot 2025, categoría senior. Nuestro enfoque combina estrategias innovadoras, diseño mecánico optimizado y control avanzado para maximizar el puntaje y la eficiencia en cada partida.

El objetivo es construir un robot autónomo capaz de realizar tareas complejas utilizando visión artificial, control preciso, estrategias de movimiento y diseño innovador. El equipo está formado por varios grupos de trabajo especializados en diferentes áreas del proyecto.

## Grupos de Trabajo

El proyecto está organizado en varios grupos que trabajan de manera colaborativa en las diferentes fases del desarrollo:

### 1. **Grupo Falcon** - Visión Artificial, Control y Estrategia de Movimiento

- **Responsable:** Julio
- **Descripción:** Este grupo se encarga de la visión artificial, el control del robot y la estrategia de movimiento. El objetivo es desarrollar un sistema autónomo que permita al robot navegar, reconocer objetos y tomar decisiones en tiempo real basándose en la información visual y de sensores.
  
#### Tareas clave:
- Implementación de algoritmos de procesamiento de imágenes para la detección de objetos y navegación.
- Desarrollo de algoritmos de control para gestionar la velocidad, dirección y precisión de los movimientos del robot.
- Estrategia de movimiento autónoma para la competencia.

#### Tecnologías y herramientas:
- **Hardware:** Cámaras de alta resolución, sensores de distancia (LiDAR, infrarrojos).
- **Software:** OpenCV, TensorFlow, ROS (Robot Operating System), Gazebo/Webots para simulación.
  
### 2. **Grupo T-Rex** - Montaje de las Estructuras y Latas

- **Responsable:** Bruno
- **Descripción:** Este grupo se encarga de la construcción física del robot, centrado principalmente en el ensamblaje de las estructuras, y la implementación de las latas que forman parte del diseño del robot.

#### Tareas clave:
- Montaje de las estructuras principales del robot.
- Integración de las latas en el diseño estructural.
  
### 3. **Grupo Tigre** - Chasis

- **Responsable:** Diego
- **Descripción:** Este grupo está enfocado en el diseño y fabricación del chasis del robot. Se están evaluando varias opciones para crear una estructura sólida y ligera que soporte todos los componentes del robot.

#### Tareas clave:
- Diseño del chasis, tomando en cuenta la movilidad, la estabilidad y la resistencia.
- Elección de los materiales adecuados (aluminio, perfiles metálicos, cartón).

### 4. **Grupo Electrónica** - Microcontrolador, Sensores y Motores

- **Responsable:** Arturo
- **Descripción:** Este grupo se encarga de la parte electrónica del robot, que incluye la gestión de los microcontroladores, la integración de los motores paso a paso, y la incorporación de sensores para la detección de objetos y navegación.

#### Tareas clave:
- Integración de los microcontroladores (STM32, Arduino Mega, Raspberry Pi).
- Conexión de los motores, actuadores y sensores al sistema central.
- Gestión de la alimentación y distribución de energía.

### 5. **Grupo Minibots** - Desarrollo y Pruebas de Subsistemas

- **Responsables:** M y Jaime
- **Descripción:** Este grupo está dedicado al desarrollo de subsistemas más pequeños y pruebas relacionadas, asegurando que todos los componentes sean funcionales y se integren correctamente en el sistema general.

#### Tareas clave:
- Desarrollo de subsistemas adicionales como el siguelíneas.
- Realización de pruebas para asegurar la fiabilidad de los sistemas.

## Objetivos del Proyecto

1. **Desarrollo y construcción de un robot autónomo** capaz de realizar tareas específicas dentro del campo de competencia Eurobot.
2. **Implementación de visión artificial** para la detección de objetos y obstáculos.
3. **Desarrollo de algoritmos de control** para gestionar los movimientos del robot de manera precisa y eficiente.
4. **Optimización de la estrategia de movimiento** para que el robot pueda actuar en entornos dinámicos y de alta competencia.

## Tecnologías

### Hardware:
- **Motores paso a paso** para el movimiento del robot.
- **Cámaras** para visión artificial.
- **Sensores** de proximidad, LiDAR, e infrarrojos.
- **Microcontroladores** (STM32, Arduino Mega, Raspberry Pi).
  
### Software:
- **Lenguajes:** Python, C++, Arduino.
- **Bibliotecas:** OpenCV, TensorFlow, ROS, Gazebo/Webots.
- **Sistemas operativos:** Linux, ROS para el control.

## Colaboraciones y Proyectos Adicionales

El proyecto Eurobot también colabora con otras iniciativas y asociaciones relacionadas con la robótica, como **DACyA** y **Oshwdem**, para promover la creación de soluciones innovadoras y participar en actividades de difusión y aprendizaje.

## Contribuir

Este proyecto está en desarrollo activo, y las contribuciones son bienvenidas. Si deseas participar, puedes realizar un **fork** de este repositorio, trabajar en las áreas que más te interesen y enviar un **pull request**. Asegúrate de seguir las guías de codificación y de realizar pruebas exhaustivas.

1. Haz un **fork** de este repositorio.
2. Crea una nueva rama para tu tarea (`git checkout -b nombre-tarea`).
3. Realiza tus cambios y haz un **commit** (`git commit -am 'Descripción del cambio'`).
4. Empuja tus cambios a tu repositorio (`git push origin nombre-tarea`).
5. Abre un **pull request** para revisión.

## Contacto

Para cualquier duda o sugerencia, por favor contacta a los responsables de cada grupo:

- **Grupo Falcon (Visión Artificial, Control, Estrategia de Movimiento):** Julio
- **Grupo T-Rex (Montaje de Estructuras, Latas):** Bruno
- **Grupo Tigre (Chasis):** Diego
- **Grupo Electrónica (Microcontrolador, Sensores, Motores):** Arturo
- **Grupo Minibots (Subsistemas, Pruebas):** M y Jaime

---



### **Características principales del proyecto**  

- **Estrategia**: 
  - Construcción eficiente de tribunas mediante estructuras de dos niveles, utilizando electroimanes y sistemas de brazos móviles para manipular las latas y las tablas superiores.
  - Despliegue dinámico de un cartel de 500x250 mm en el escenario, cumpliendo con los requisitos de la competición.
  - Navegación autónoma con localización por balizas y detección de obstáculos para evitar colisiones.  

- **Diseño mecánico**: 
  - Dimensiones ajustadas al reglamento: ≤ 1200 mm (plegado) y ≤ 1400 mm (desplegado). 
  - Actuadores móviles en todos los módulos de acción clave.  

- **Sistema electrónico avanzado**: 
  - Microcontrolador central (STM32, Arduino Mega o Raspberry Pi según necesidades).  
  - Sensores ultrasónicos, infrarrojos, LiDAR y cámaras para una detección y reconocimiento de alta precisión.  
  - Gestión energética segura con baterías LiPo, reguladores y protección contra sobrecargas.  

- **Software robusto**: 
  - Algoritmos de control basados en PID y planificación de tareas en tiempo real con RTOS.  
  - Simulaciones en Gazebo o Webots para optimizar estrategias antes de la construcción física.  
  - Evasión de obstáculos en tiempo real y ajustes dinámicos durante la competición.  

- **Seguridad y redundancia**: 
  - Botón de emergencia accesible.  
  - Sistema de comunicación inalámbrica confiable (5 GHz) con redundancia para evitar fallos críticos.  

- **Fabricación y pruebas**: 
  - Prototipos mediante impresión 3D y mecanizado CNC.  
  - Pruebas iterativas por subsistema para asegurar una integración fluida y confiable.  

### **¿Qué encontrarás aquí?**  
1. **Documentación completa**: Desde el análisis inicial hasta las pruebas finales.  
2. **Códigos y algoritmos**: Control del robot, planificación de tareas y estrategias.  
3. **Diseño CAD**: Modelos mecánicos optimizados para el robot.  
4. **Manuales de fabricación y ensamblaje**: Detalles para replicar o modificar el robot.  
5. **Resultados de pruebas y simulaciones**: Datos recopilados para mejorar el desempeño del robot.  

Este repositorio está diseñado para ser una herramienta colaborativa para el equipo, así como un recurso educativo para otros interesados en la robótica competitiva.  

¡Únete a nuestro viaje hacia Eurobot 2025! 🚀  
