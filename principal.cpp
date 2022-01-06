/*
Nome: Catarina Oliveira Dowsley Fernandes
DRE: 118026011
Disciplina: Sistemas Operacionais - EEL770 
Professor: Rodrigo Couto
Trabalho1: Inicialização de programas e comunicação entre processos
DEL - Escola Politécnica - Universidade Federal do Rio de Janeiro
Versão do Linux: Ubunto-18.04
OBS: OS LINKS DAS REFERÊNCIAS USADAS PARA O TRABALHO ESTÃO NO ARQUIVO README
*/


//Biblioteca de entrada e saída
#include <iostream>
//Biblioteca que nos permite usar a função time
#include <time.h>
//Blibiotecas relacionadas ao sinal
#include<stdio.h>
#include<signal.h>
#include<unistd.h>
//Definições para as funções WRITE e READ
#define READ                            0
#define WRITE                           1
//Biblioteca para função WAIT
#include<wait.h>
//Biblioteca pra usar o dup2
#include <fcntl.h>
#include <stdlib.h>
#include <cstdlib>
#include <sys/types.h>

//Aqui vamos definir  as variaveis e o tipo bool para usarmos nas tarefas

bool tarefa1 = false;
bool tarefa2 =false;
bool finalizar = false;

using namespace std;

/*Ao iniciar a execução, o programa imprimirá na tela seu pid e inicializará com o valor zero uma variável
denominada comandoParaExecutar.*/

//Aqui vamos definir o signal handler -> controle dos sinais
//Usei como referência o codigo disponivel no documento do trabalho
void sig_handler (int sinal){
    if(sinal == SIGUSR1){
        cout<<"Recebido: SIGUSR1\n"<<endl;
        tarefa1=true;
    }else if (sinal ==SIGUSR2){
        cout<<"Recebido: SIGUSR2\n"<<endl;
        tarefa2 = true;
    }else if (sinal == SIGTERM ){
        cout<<"Recebido: SIGTERM\n"<<endl;
        finalizar = true;
    }
}

//Para função void usei o código  sobre sinais que o professor colocou no trabalho

int main(void){

    //Incializando variáveis
    int comandoParaExecutar = 0;   
    pid_t pidFilho;
    time_t tempo;
    //Variável onde vai ficar 0 ou 1 dependendo do uso do write ou read. Essencial para passar dados do filho pro pai.
    int pipeTarefa1Pai[2];
   
    cout<<"Olá, sou o o processo pai. Meu pid é: "<<(int) getpid()<<endl;

    //Tratando possíveis erros
    if (signal(SIGUSR1, sig_handler) == SIG_ERR){
        cout<<"Erro ao receber sinal SIGUSR1\n"<<endl;
    }
    if (signal(SIGUSR2, sig_handler) == SIG_ERR){
        cout<<"Erro ao receber sinal SIGUSR2\n"<<endl;
    }
    if (signal(SIGTERM, sig_handler) == SIG_ERR){
        cout<<"Erro ao receber sinal SIGTERM\n"<<endl;
    }
        
    //Loop infinito para que possamos receber e tratar todos os sinais.
    while(1) {
        //Tarefa 1
        if(tarefa1){
            //1. O pai cria um pipe;
            if(pipe(pipeTarefa1Pai)== -3)
                cout<<"Falha em obter Pipe"<<endl;//Uma vez que por ser uma ID não pode ter um algarismo negativo;
            //2. O pai cria um processo filho; Aqui eu adaptei pra C++ o código que está no livro;
            pidFilho = fork();
            if(pidFilho <0){
                //Saída para falha no fork
                cout<< "Falha na criação do processo filho (fork)."<<endl;
                exit(1);


             }else if (pidFilho >0) {
                //3. O pai fica esperando a finalização do filho;
                wait(NULL);
                //7. O pai lê o valor recebido e guarda a resposta do filho na variável denominada comandoParaExecutar;
                read(pipeTarefa1Pai[READ], &comandoParaExecutar, sizeof(comandoParaExecutar));
                
                //8. O pai fecha qualquer ponta aberta do pipe;
                close(pipeTarefa1Pai[READ]);
                
                
             }
            else {
                //4. O filho obtém o tempo na era UNIX (veja Seção 6), em segundos;//Aqui usei a função time de acordo com um guia para c++ que achei na internet.
                tempo = time(NULL);
                //5. O filho imprime o número na tela e envia esse número para o pai. Esse envio deverá ser realizado via pipe.
                
                cout<<"Olá, sou filho e meu pid é: "<<(int) getpid()<<endl;
                write(pipeTarefa1Pai[WRITE], &tempo, sizeof(tempo));
                
                //6. O filho fecha qualquer ponta aberta do pipe e finaliza;
                
                close(pipeTarefa1Pai[WRITE]);
                return 0;
                
        
            }
            tarefa1 = false;

        }

        if (tarefa2){
             //1. O pai cria um processo filho;
            pidFilho = fork();

            //2. O pai envia ao filho o conteúdo da variável comandoParaExecutar;

            
            if(pidFilho <0){
                //Saída para falha no fork
                cout<< "Falha na criação do processo filho (fork)."<<endl;
                exit(1);


            }else if(pidFilho>0) {
                //3. O pai fica esperando a finalização do filho;
                wait(NULL);
  
            }
            else{

                //4. O filho verifica o número recebido. Dependendo do valor do número, o filho executa uma das seguintes ações:
                //Se o número for zero (ou seja, a Tarefa 1 nunca foi chamada) o filho imprime “Não há comando a executar” e finaliza;
                if (comandoParaExecutar == 0){
                    cout<<"Não há comando a executar"<<endl;
                    
                 }
                // Se o número for diferente de zero e par, o filho executa o comando “ping 8.8.8.8 -c 5”, por meio de uma chamada exec, e a saída do comando deverá ser impressa na tela;
                if((comandoParaExecutar !=0) && (comandoParaExecutar % 2 ==0)){
                    //Usei a referência de exec do código que o professor disponibilizou no drive
                    //Ao executar o ping, a saída do comando será, por padrão, impressa na tela.(retirei do documento do trabalho)
                    execlp("/bin/ping","ping","8.8.8.8","-c","50",NULL);
                    return 0;

                }/*Se o número for ímpar, o filho executa o comando “ping 8.8.8.8 -c 5”, por meio de uma chamada exec, e a saída do comando deverá ser escrita no arquivo “saidaComando.log”. Para facilitar a
                correção, o arquivo “saidaComando.log” deve estar escrito no mesmo diretório no qual o executável do seu programa se encontra. Essa escrita deverá ser realizada por meio da chamada dup2.
                Não é permitido usar operadores do shell de redirecionamento de arquivo, como “>”.*/
                else if ((comandoParaExecutar !=0) && (comandoParaExecutar %2 ==1)){
                    int file_desc = open("./saidaComando.log", O_CREAT | O_WRONLY | O_APPEND, 0666);
      
                    // here the newfd is the file descriptor of stdout (i.e. 1)
                    dup2(file_desc, 1) ; 

                    execlp("/bin/ping","ping","8.8.8.8","-c","50",NULL);
        
         
                }
                return 0;
                                    
  
            }
            tarefa2 = false;
            
        }
        if(finalizar){
            cout<<"Finalizando o disparador...\n"<<endl;
            return 0;
        }
  
           
        sleep(1);
    }
    return 0;

        

}



