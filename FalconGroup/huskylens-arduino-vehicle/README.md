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

