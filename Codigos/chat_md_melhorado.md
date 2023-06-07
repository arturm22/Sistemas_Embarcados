```c
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>

using namespace cv;

int main() {
    // Carregar a imagem
    Mat img = imread("4.jpg", IMREAD_COLOR);
    resize(img, img, Size(620, 480));

    // Converter a imagem para escala de cinza
    Mat gray;
    cvtColor(img, gray, COLOR_BGR2GRAY);

    // Aplicar filtro bilateral para reduzir o ruído
    bilateralFilter(gray, gray, 11, 17, 17);

    // Detectar as bordas na imagem usando o algoritmo de Canny
    Mat edged;
    Canny(gray, edged, 30, 200);

    // Encontrar os contornos na imagem
    vector<vector<Point>> cnts;
    findContours(edged.clone(), cnts, RETR_TREE, CHAIN_APPROX_SIMPLE);

    // Ordenar os contornos em ordem decrescente de área
    sort(cnts.begin(), cnts.end(), [](const vector<Point>& a, const vector<Point>& b) {
        return contourArea(a) > contourArea(b);
    });

    // Encontrar o contorno com aproximadamente 4 pontos, que representa a placa do carro
    vector<Point> screenCnt;

    for (const auto& c : cnts) {
        double peri = arcLength(c, true);
        vector<Point> approx;
        approxPolyDP(c, approx, 0.018 * peri, true);

        if (approx.size() == 4) {
            screenCnt = approx;
            break;
        }
    }

    int detected = 0;
    if (!screenCnt.empty()) {
        detected = 1;

        // Desenhar o contorno da placa na imagem original
        drawContours(img, vector<vector<Point>>{screenCnt}, -1, Scalar(0, 255, 0), 3);

        // Criar uma máscara para isolar a placa do carro na imagem original
        Mat mask = Mat::zeros(gray.size(), CV_8UC1);
        drawContours(mask, vector<vector<Point>>{screenCnt}, 0, Scalar(255), -1);
        Mat newImage;
        bitwise_and(img, img, newImage, mask);

        // Recortar a região da placa da imagem em escala de cinza
        Rect cropRect = boundingRect(screenCnt);
        Mat cropped = gray(cropRect);

        // Pré-processamento adicional na imagem recortada para melhorar o reconhecimento de letras
        Mat blurred;
        GaussianBlur(cropped, blurred, Size(5, 5), 0);
        Mat thresholded;
        threshold(blurred, thresholded, 0, 255, THRESH_BINARY_INV | THRESH_OTSU);

        // Configurar e executar o Tesseract para reconhecimento de texto
        tesseract::TessBaseAPI tess;
        tess.Init(NULL, "eng", tesseract::OEM_LSTM_ONLY);
        tess.SetPageSegMode(tesseract::PSM_SINGLE_BLOCK);
        tess.SetImage((uchar*)thresholded.data, thresholded.cols, thresholded.rows, 1, thresholded.cols);

        char* outText = tess.GetUTF8Text();
        printf("Detected Number is: %s\n", outText);

        // Exibir as imagens processadas
        imshow("image", img);
        imshow("Cropped", cropped);
        imshow("Thresholded", thresholded);
    } else {
        printf("No contour detected\n");
    }

    waitKey(0);
    destroyAllWindows();

    return 0;
}
```
