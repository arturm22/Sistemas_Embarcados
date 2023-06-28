#include <opencv2/opencv.hpp>
  #include <pytesseract/pytesseract.h>
  #include <pandas/pandas.h>
  
  void Ocr_da_Placa() {
    cv::Mat img_ocr = cv::imread("../Imagem/placa_binarizada.jpg");
    
    std::string config = "-c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWYXZ0123456789 --psm 6";
    // A saida será em inglês para ler melhor a placa em lang = eng
    
    std::string saida = pytesseract::image_to_string(img_ocr, "eng", config);
    std::cout << saida << std::endl;
  }
