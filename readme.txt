README

/*
Nome: Catarina Oliveira Dowsley Fernandes
DRE: 118026011
Disciplina: Sistemas Operacionais - EEL770 
Professor: Rodrigo Couto
Trabalho1: Inicialização de programas e comunicação entre processos
DEL - Escola Politécnica - Universidade Federal do Rio de Janeiro
Versão do Linux: Ubuntu-18.04
OBS: OS LINKS DAS REFERÊNCIAS USADAS PARA O TRABALHO ESTÃO NO ARQUIVO README
*/

Para o usuário usar o programa é simples:
-Abra 2 terminais
-No 1º Terminal:
	Para compilar:
	Digite make

	Para executar:
	Digite ./principal
	
	Logo que executar aparecerá na tela o número do pid para ser usado no 2ºterminal

	Para limpar:
	Digite make clean

-No 2º Terminal:
	
	kill -SIGUSR1 pid
	kill -SIGUSR2 pid
	kill -SIGTERM pid


Tarefa 1: Gera o tempo na era UNIX
Tarefa 2: Se o número for par e diferente de zero: Executa "ping 8.8.8.8 -c 5"
	  Se o número for ímpar e diferente de zero: Executa "ping 8.8.8.8 -c 5" porém dentro do arquivo saidaComando.log
	  Se o número for zero: Imprime "Não há comando a executar" e finaliza


REFERÊNCIAS:
https://pages.cs.wisc.edu/~remzi/OSTEP/
https://github.com/remzi-arpacidusseau/ostep-code/tree/master/cpu-api
https://www.thegeekstuff.com/2012/03/linux-signals-fundamentals/
https://www.thegeekstuff.com/2012/03/catch-signals-sample-c-code/
https://www.geeksforgeeks.org/dup-dup2-linux-system-call/
https://www.geeksforgeeks.org/time-function-in-c/
https://drive.google.com/file/d/1wWEsfPYXpFlcPJZywxCdjW_JX4oEA-aJ/view?usp=sharing.
https://www.inf.pucrs.br/~pinho/PRGSWB/Streams/streams.html
https://stackoverflow.com/questions/30918875/c-error-expected-identifier-before-token
https://www.iteramos.com/pregunta/36029/cc-devuelve-exit_success-o-0-de-principal