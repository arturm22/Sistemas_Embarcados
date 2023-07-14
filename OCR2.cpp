#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <vector>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <fstream>
#include <string>
#include <cstdlib>
#include <wiringPi.h>

std::string remove_nao_alfanumerico(std::string s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](auto const& c)->bool { return !std::isalnum(c); }), s.end());
    return s;
}
std::string Ocr_da_Placa(){
    
    cv::Mat img_ocr = cv::imread("../Imagem/placa_binarizada.jpg");

    std::string config = "-c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWYXZ0123456789 --psm 6";
    // A saida será em inglês para ler melhor a placa em lang = eng

    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng", tesseract::OEM_DEFAULT);
    tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
    tess.SetVariable("tessedit_char_whitelist", config.c_str());
    tess.SetImage((uchar*)img_ocr.data, img_ocr.size().width, img_ocr.size().height, img_ocr.channels(), img_ocr.step1());

    std::string saida = remove_nao_alfanumerico(tess.GetUTF8Text());
    //saida.erase(std::remove_if(saida.begin(), saida.end(), [](auto const& c)->bool { return !std::isalnum(c); }), saida.end());
    std::cout << saida << std::endl;
    return saida;
}

int main () {
    //Ocr_da_Placa();
    int ledPin = 20; // Led Verde 
    int ledPin2 = 21;// Led Vermelho
    
    std::string placa = Ocr_da_Placa();
    //std::cout << extracted_text << std::endl;
    //std::string cmd = "echo " + placa + " > placa.txt";
    //system(cmd.c_str());
    std::string placa2 = placa; 
    std::string line;
    std::ifstream file("../Biblioteca/Moradores.csv", std::ifstream::in);
    std::cout << placa2 << std::endl;
    
    
    
    if(file.is_open()){
        while(getline(file, line)){
            if(line.find(placa2) != std::string::npos){
                std::cout << "Encontrado:  " << line << '\n';
                
            } else{ 
                
                std::cout << "Não encontrado. Permissão de entrada negada." << std::endl;
            }
        }
        file.close();
        
    } else {
        std::cout << "Não foi possível abrir o arquivo\n";
    }    
    //std::string cmd = "grep " + placa + "Moradores.csv";
    
    //system(cmd.c_str());  
    //char var[100];
    //sprintf(var,"grep placa ./Moradores.csv", placa);
    //system(var);
    
     
    return 0;
    
}
