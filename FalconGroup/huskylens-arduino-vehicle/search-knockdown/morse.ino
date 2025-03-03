#define NOTE_A4 440
int dotLen = 100;          // Duración de un punto en código Morse
int dashLen = dotLen * 3;  // Duración de una raya en código Morse


void Play3Char(char myWord[]){
  for(int i=0; i<3; i++){
    PlayChar(myWord[i]);
  }
  delay(dotLen*4);
}
void Play7Char(char myWord[]){
  for(int i=0; i<7; i++){
    PlayChar(myWord[i]);
  }
  delay(dotLen*4);
}


void MorseDot() {
  tone(pinTone, NOTE_A4);  // Encender el tono
  delay(dotLen);           // Duración del punto
  noTone(pinTone);         // Apagar el tono
  delay(dotLen);           // Espacio entre símbolos
}

//void MorseDashno() {
//  tone(pinTone, NOTE_A4);  // Encender el tono
//  delay(dashLen);          // Duración de la raya
//  noTone(pinTone);         // Apagar el tono
//  delay(dotLen);           // Espacio entre símbolos
//}

void MorseDash()
{
  tone(pinTone, NOTE_A4, dashLen);  // start playing a tone
  delay(dotLen*4);               // hold in this position
}

void PlayChar(char tmpChar) {
  // Tomar el carácter pasado y usar un switch case para encontrar el código Morse correspondiente
  switch (tmpChar) {
    case 'a':
      MorseDot();
      MorseDash();
      break;
    case 'b':
      MorseDash();
      MorseDot();
      MorseDot();
      MorseDot();
      break;
    case 'c':
      MorseDash();
      MorseDot();
      MorseDash();
      MorseDot();
      break;
    case 'd':
      MorseDash();
      MorseDash();
      MorseDot();
      break;
    case 'e':
      MorseDot();
      break;
    case 'f':
      MorseDot();
      MorseDot();
      MorseDash();
      MorseDot();
      break;
    case 'g':
      MorseDash();
      MorseDash();
      MorseDot();
      break;
    case 'h':
      MorseDot();
      MorseDot();
      MorseDot();
      MorseDot();
      break;
    case 'i':
      MorseDot();
      MorseDot();
      break;
    case 'j':
      MorseDot();
      MorseDash();
      MorseDash();
      MorseDash();
      break;
    case 'k':
      MorseDash();
      MorseDot();
      MorseDash();
      break;
    case 'l':
      MorseDot();
      MorseDash();
      MorseDot();
      MorseDot();
      break;
    case 'm':
      MorseDash();
      MorseDash();
      break;
    case 'n':
      MorseDash();
      MorseDot();
      break;
    case 'o':
      MorseDash();
      MorseDash();
      MorseDash();
      break;
    case 'p':
      MorseDot();
      MorseDash();
      MorseDash();
      MorseDot();
      break;
    case 'q':
      MorseDash();
      MorseDash();
      MorseDot();
      MorseDash();
      break;
    case 'r':
      MorseDot();
      MorseDash();
      MorseDot();
      break;
    case 's':
      MorseDot();
      MorseDot();
      MorseDot();
      break;
    case 't':
      MorseDash();
      break;
    case 'u':
      MorseDot();
      MorseDot();
      MorseDash();
      break;
    case 'v':
      MorseDot();
      MorseDot();
      MorseDot();
      MorseDash();
      break;
    case 'w':
      MorseDot();
      MorseDash();
      MorseDash();
      break;
    case 'x':
      MorseDash();
      MorseDot();
      MorseDot();
      MorseDash();
      break;
    case 'y':
      MorseDash();
      MorseDot();
      MorseDash();
      MorseDash();
      break;
    case 'z':
      MorseDash();
      MorseDash();
      MorseDot();
      MorseDot();
      break;
  }
  delay(dotLen * 2);  // Espacio entre letras
}
