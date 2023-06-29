#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <vector>
#include <iostream>
#include <opencv2/core/mat.hpp>
  
 void Ocr_da_Placa(){
    
    cv::Mat img_ocr = cv::imread("../Imagem/placa_binarizada.jpg");

    std::string config = "-c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWYXZ0123456789 --psm 6";
    // A saida será em inglês para ler melhor a placa em lang = eng

    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetVariable("tessedit_char_whitelist", config.c_str());
    tess.SetImage((uchar*)img_ocr.data, img_ocr.size().width, img_ocr.size().height, img_ocr.channels(), img_ocr.step1());

    std::string saida = tess.GetUTF8Text();
    std::cout << saida << std::endl;
}

int main () {
    Ocr_da_Placa();
    return 0;
}
