// Bloco 3 
void pre_processamento(){
  
    Mat imagem_placa = imread("..\\Imagem\\Imagem_temporaria.jpg");
    
    if(imagem_placa.empty()){
        return;
    }
    
    // Aumentar a imagem para um melhor ajuste no tesseract
    Mat img_aumentada;
    resize(imagem_placa, img_aumentada, Size(), 4, 4, INTER_CUBIC);
    
    // O 50 e o 255 são colocados na placa, é a margem do quanto de branco e cinza serão adicionados na imagem para realçar as letras 
    Mat img_cinza;
    cvtColor(img_aumentada, img_cinza, COLOR_BGR2GRAY);
    
    Mat img_binaria;
    threshold(img_cinza, img_binaria, 65, 200, THRESH_BINARY);
    
    // Salvar a imagem binarizada e em cinza
    imwrite("../Imagem/placa_binarizada.jpg", img_binaria);
    imwrite("../Imagem/placa_binarizada_png.png", img_binaria);
    
    imshow("placa_binaria", img_binaria);
    waitKey(0);
    destroyAllWindows();
  }

// Bloco 4 
void Ocr_da_Placa(){
  
    Mat img_ocr = imread("../Imagem/placa_binarizada.jpg");
    
    string config = "-c tessedit_char_whitelist=ABCDEFGHIJKLMNOPQRSTUVWYXZ0123456789 --psm 6";
    // A saida será em inglês para ler melhor a placa em lang = eng
    
    string saida = pytesseract::image_to_string(img_ocr, "eng", config);
    cout << saida << endl;
  }
