. : all # atalho para rodar make .
all: tirar_foto compilar_main executar_main # executar 3 tarefas, tira a foto, compila e executa a main

tirar_foto: # esperando comando de tirar foto
	@echo "Tirando a foto e colocando na pasta imagens\n"

compilar_main: # compilando o arquivo main.cpp para main
	g++ main.cpp -o main -Wall 'pkg-config --libs opencv4'

executar_main: # execultando programa principal com um caminho de imagem
	./main ./imagens/carro4.jpg


clear: limpar_imagens limpar_main # comando para limpar tudo

limpar_main: 
	rm -rf ./main 

limpar_imagens: 
	rm -rf ./imagens/*
