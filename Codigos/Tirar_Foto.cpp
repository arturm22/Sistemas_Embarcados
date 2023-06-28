#include <iostream>
  #include <picamera.h>
  #include <time.h>
  
  void tirar_foto() {
    PiCamera camera;
    camera.resolution = (600,450);
    camera.start_preview();
    for (int i = 0; i < 5; i++) {
        sleep(2);
        camera.capture("../Imagem/Foto%s.jpg", i);
    }
    camera.stop_preview();
  }
