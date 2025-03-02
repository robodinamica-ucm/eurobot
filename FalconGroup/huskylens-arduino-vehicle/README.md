#1 Potencia
https://forum.arduino.cc/t/max-current-draw-mega-2560/680799/4
https://docs.arduino.cc/resources/datasheets/A000067-datasheet.pdf
Huskylens has a power consumption of: 310mA@3.3V or 220mA@5V

Connect the 5V and ground from the supply to the 5V and ground of the Mega. Connect any peripherals that need 5V to the power supply 5V and ground, not the Mega 5V and ground. Do not run high currents through the Mega ground. That will provide protection to the Mega.
The Mega chip s rated for 200mA on its VCC and Gnd pins. So the chip could in theory draw 800A to source as High signals, o or to sink as Low signals, across it's IO pins.

The 5V regulator is rated for 800 or 1000mA. It wont achieve that without overheating and shutting down, or failing.
For best results, feed no more than 7.5V into the barrel jack, and don't expect to get more than 300, 400mA before it overheats.

If you connect a 5V, 2A or more regulated to the 5V/Gnd on the power header, the board will be fine.

#2 Instalación Arduino IDE en Linux
Hemos descargado el archivo tar, ejecutado el instalador y todo se ha hecho automatico(proceso completo en installed.txt)
Hemos creado el archivo de prueba print_1 que imprime una string correctamente cuando en el serial monitor ajustamos los baudios de forma acorde.

#3 Libreria HUSKYLENS
La libreria la encontramos en el github y en el tutorial: https://wiki.dfrobot.com/HUSKYLENS_V1.0_SKU_SEN0305_SEN0336#target_28
	La del tutorial es otra version mas grande, ambas estan descargadas, hemos hecho include library en el IDE e importado HUSKYLENS.zip
	Ya esta incluido, podemos ver las librerias en: cesar@asus:~/Arduino/libraries
	Con sketch > include library > huskylens; podemos poner los include <...h> automaticamente
#4 Huskylens Connection
El programa gpt con Serial1 ha compilado pero no ha funcionado(conexion no establecida, fallo en la transmision); el codigo de la web con softwareSerial
ha funcionado prefectamente con excelentes resultados demostrando la reliability del arduino y su gran capacidad de computo programa: huskylens1.ino
Hemos visto que GPT indica que en la mega el RX1 es el 19 y el TX1 es el 18, curiosamente nuestra placa los tiene alreves.
Parece natural pensar que es un error de impresion porque para el Serial, Serial2 ... tiene primero el TX y luego el RX por lo que no tiene sentido que sea alreves en el Serial1
Hemos hecho las conexiones al reves en Serial1 y obtenemos funcionamiento perfecto, confirmamos que la impresion tiene esa errata.

#5 TESTS:
Los programas funcionan bien, hemos podido cambiar el algoritmo facilmente: huskylens.writeAlgorithm(ALGORITHM_OBJECT_TRACKING)
La documentacion de github es buena y clara.
https://github.com/HuskyLens/HUSKYLENSArduino

#6 Autonomus CAR:
Vamos a hacer la revision del mitshubishi para controlarlo y posteriormente incorporarle la camara.
Trataremos de conectar las huskylens en la fuente de alimentacion(salida de 5V para no forzar la potencia del arduino)

