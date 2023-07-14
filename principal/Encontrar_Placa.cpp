#include <opencv2/opencv.hpp>
#include <vector>
#include <iostream>
#include <opencv2/core/mat.hpp>

  using namespace cv;
  using namespace std;
  
  void encontrar_a_placa(String imagem_carro) {
    Mat img = imread(imagem_carro);
    
    Mat cinza;
    cvtColor(img, cinza, COLOR_BGR2GRAY);
    
    Mat bin;
    threshold(cinza, bin, 90, 230, THRESH_BINARY);
    
    Mat desfocar;
    GaussianBlur(bin, desfocar, Size(5,5), 0);
    imshow("Imagem_desfocada", desfocar);
    
    vector<vector<Point>> contornos;
    vector<Vec4i> hierarquia;
    findContours(desfocar, contornos, hierarquia, RETR_TREE, CHAIN_APPROX_NONE);
    
    for (int i = 0; i < (int) contornos.size() ; i++) {
      double perimetro = arcLength(contornos[i], true);
      vector<Point> aprox;
      approxPolyDP(contornos[i], aprox, 0.03*perimetro, true);
      
      if (perimetro > 300 ) {
        Rect rect = boundingRect(contornos[i]);
        rectangle(img, rect, Scalar(0,255,0), 2);
        
        Mat temporario = img(rect);
        imwrite("../Imagem/Imagem_temporaria.jpg", temporario);
      }
    }
    
    imshow("Placa_contornada", img);
    waitKey(0);
    destroyAllWindows();
    
  }


int main () {
    encontrar_a_placa("../Imagem/Foto1.jpg");
    return 0;
}
