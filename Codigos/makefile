. : all # atalho para rodar make .
all: compilar_tudo executar_tudo # executar 3 tarefas, tira a foto, compila e executa a main
compilar_tudo: compilar_tirar_foto compilar_Encontrar_Placa compilar_pre_processamento compilar_OCR 
executar_tudo: executar_tirar_foto executar_Encontrar_Placa executar_pre_processamento executar_OCR
tirar_foto: # esperando comando de tirar foto
	@echo "Tirando a foto e colocando na pasta imagens\n"

compilar_tirar_foto: # compilando o arquivo tirar_foto.cpp para tirar_foto
	g++ tirar_foto.cpp -o tirar_foto -Wall `pkg-config --libs opencv4`

executar_tirar_foto: # execultando programa principal com um caminho de imagem
	./tirar_foto 

compilar_Encontrar_Placa: # compilando o arquivo main.cpp para main
	g++ Encontrar_Placa.cpp -o Encontrar_Placa -Wall `pkg-config --libs opencv4`

executar_Encontrar_Placa: # execultando programa principal com um caminho de imagem
	./Encontrar_Placa 

compilar_pre_processamento: # compilando o arquivo main.cpp para main
	g++ pre_processamento.cpp -o pre_processamento -Wall `pkg-config --libs opencv4`

executar_pre_processamento: # execultando programa principal com um caminho de imagem
	./pre_processamento

compilar_OCR: # compilando o arquivo main.cpp para main
	g++ OCR.cpp -o OCR -Wall `pkg-config --libs tesseract opencv4`

executar_OCR: # execultando programa principal com um caminho de imagem
	./OCR
