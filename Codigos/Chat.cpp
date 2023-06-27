#include <opencv2/opencv.hpp>

void encontrar_a_placa(std::string imagem_carro) {
    cv::Mat img = cv::imread(imagem_carro);
    // cv::Mat img = cv::imread("../Imagem/CARRO4.JPG");
    // cv::imshow("img", img);

    // Escalas de Cinza para o OpenCV identificar
    cv::Mat cinza;
    cv::cvtColor(img, cinza, cv::COLOR_BGR2GRAY);
    // cv::imshow("cinza", cinza);

    // Converter em preto e branco, para binarizar a imagem com as escalas de cores demonstradas com os números
    // indo até 128 na coloração preta e 255 na coloração branca
    cv::Mat bin;
    cv::threshold(cinza, bin, 60, 220, cv::THRESH_BINARY);

    // TRESH_BINARY traz o limite para as cores
    // _, essa variável necessita de um retorno

    // cv::imshow("bin", bin);

    // Desfocar a imagem para identificar melhor as formas geométricas, encontrando melhor os contornos
    cv::Mat desfocar;
    cv::GaussianBlur(bin, desfocar, cv::Size(5, 5), 0);
    cv::imshow("Imagem_desfocada", desfocar);

    // Agora procurar os contornos
    std::vector<std::vector<cv::Point>> contornos;
    std::vector<cv::Vec4i> hierarquia;
    cv::findContours(desfocar, contornos, hierarquia, cv::RETR_TREE, cv::CHAIN_APPROX_NONE);

    // cv::drawContours(img, contornos, -1, cv::Scalar(0, 255, 0), 2);

    // o -1 é o ID dos contornos, como não precisa dessa informação colocamos o -1
    // 0 255 0 ---> Cor do contorno, no caso verde
    // 2 ------> largura da borda do contorno

    // cv::imshow("Contornos", img);
    // cv::waitKey(0);
    // cv::destroyAllWindows();

    // fazer contornos quadrados
    for (auto& c : contornos) {
        double perimetro = cv::arcLength(c, true);
        cv::approxPolyDP(c, c, 0.03 * perimetro, true);

        if (perimetro > 500) {
            cv::approxPolyDP(c, c, 0.03 * perimetro, true);

            // Igualar a quatro cantos e aproximar a um retângulo
            if (c.size() == 4) {
                cv::Rect retangulo = cv::boundingRect(c);
                cv::rectangle(img, retangulo, cv::Scalar(0, 255, 0), 2);

                cv::Mat temporario = img(retangulo);
                cv::imwrite("../Imagem/Imagem_temporaria.jpg", temporario);
            }
        }
    }

    cv::imshow("Placa_contornada", img);
    cv::waitKey(0);
    cv::destroyAllWindows();
}

int main() {
    encontrar_a_placa("caminho_da_imagem_carro.jpg");
    return 0;
}
