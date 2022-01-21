#include "PIG.h"
#include "Estruturas.h"

#define WIDTH 1000
#define HEIGHT 600
#define DELTA_TIME 0.016

PIG_Evento evento;          //evento ser tratadoi a cada pssada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado

int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Projeto Memoria Cache",0,HEIGHT,WIDTH);

    fonte = CriaFonteNormal("../fontes/arial.ttf", 12,BRANCO);
    fonteAletaMiss = CriaFonteNormal("../fontes/arial.ttf", 16,BRANCO);
    timer = CriaTimer(true);


    //associando o teclado (basta uma única vez) com a variável meuTeclado
    srand(time(NULL));
    bool terminou = false;
    int temporizador = CriaTimer(true);
    meuTeclado = GetTeclado();
    char elementoBuscado[20] =  "";
    int tamanhoElementoBuscado = 0;
    Nivel nivel1 = Nivel(250,400,4,4,200,62);
    nivel1.criarBlocos(4);

    Nivel nivel2 = Nivel(350-192,225,8,16,384,108);
    nivel2.criarBlocos(16);

    Nivel nivel3 = Nivel(350-284,20,12,36,568,154);
    nivel3.criarBlocos(36);

    Nivel memPrincipal = Nivel(780,100,0,0,200,400);

    //Niveis troca ocorrencia miss
    Nivel blocoDeTrocaMiss = Nivel(780,280,1,1,40,40);
    blocoDeTrocaMiss.criarBlocos(1);
    /*Nivel blocoDeTrocaMiss1 = Nivel(780,280,1,1,40,40);
    blocoDeTrocaMiss1.criarBlocos(1);

    Nivel blocoDeTrocaMiss2 = Nivel(780,280,1,1,40,40);
    blocoDeTrocaMiss2.criarBlocos(1);

    Nivel blocoDeTrocaMiss3 = Nivel(780,280,1,1,40,40);
    blocoDeTrocaMiss3.criarBlocos(1);*/

    /*vector<Nivel *> NiveisMiss = {&blocoDeTrocaMiss1,&blocoDeTrocaMiss2,&blocoDeTrocaMiss3};*/
    // --------//

    vector<Nivel *> Niveis = {&nivel1,&nivel2,&nivel3};
    int indiceNivelAtt = Niveis.size()-1;
    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e as coisas devem ser atualizadas

        //será feita aprepação do frame que será exibido na tela
        IniciaDesenho();

        nivel1.desenhaNivel();
        nivel1.desenharElementos();

        nivel2.desenhaNivel();
        nivel2.desenharElementos();

        nivel3.desenhaNivel();
        nivel3.desenharElementos();

        memPrincipal.desenhaNivel();
        memPrincipal.nomeNivel = "Memoria Principal";
        memPrincipal.escreveNomeNivel();

        //Operação teclado escrever numero buscado
        if( evento.tipoEvento == PIG_EVENTO_TECLADO && continuarChecando == false){
            if(evento.teclado.acao == PIG_TECLA_LIBERADA){

                if(evento.teclado.tecla == PIG_TECLA_0){
                    elementoBuscado[tamanhoElementoBuscado] = '0';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_1){
                    elementoBuscado[tamanhoElementoBuscado] = '1';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_2){
                    elementoBuscado[tamanhoElementoBuscado] = '2';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_3){
                    elementoBuscado[tamanhoElementoBuscado] = '3';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_4){
                    elementoBuscado[tamanhoElementoBuscado] = '4';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_5){
                    elementoBuscado[tamanhoElementoBuscado] = '5';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_6){
                    elementoBuscado[tamanhoElementoBuscado] = '6';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_7){
                    elementoBuscado[tamanhoElementoBuscado] = '7';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_8){
                    elementoBuscado[tamanhoElementoBuscado] = '8';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_9){
                    elementoBuscado[tamanhoElementoBuscado] = '9';
                    tamanhoElementoBuscado++;
                }else if(evento.teclado.tecla == PIG_TECLA_BACKSPACE){
                    if(tamanhoElementoBuscado>0){
                        elementoBuscado[tamanhoElementoBuscado-1] = ' ';
                        tamanhoElementoBuscado--;
                    }
                }
            }
        }

        EscreverEsquerda("Valor Buscado:",15,500);
        EscreveInteiroEsquerda(atoi(elementoBuscado),280,500);

        // Reset busca
        if( meuTeclado[PIG_TECLA_ESC]){
            resetBusca();
            memset(elementoBuscado, ' ', 20);
            tamanhoElementoBuscado = 0;
            nivel1.resetBlocos();
            nivel2.resetBlocos();
            nivel3.resetBlocos();
            indiceNivelAtt = Niveis.size()-1;
            terminou = false;
            ReiniciaTimer(temporizador,true);
            blocoDeTrocaMiss.iniX = 780;
            blocoDeTrocaMiss.elementos[0].iniX = 785;
            blocoDeTrocaMiss.iniY = 280;
            blocoDeTrocaMiss.elementos[0].iniY = 285;
        }

        if(meuTeclado[PIG_TECLA_ENTER]){
            continuarChecando = true;
            elementoProcurado = atoi(elementoBuscado);
        }
        if(continuarChecando == true){
            Niveis[indiceNivelAtual%qtdNiveis]->procuraBloco();

            //Ajusta velocidade da busca
            if( evento.tipoEvento == PIG_EVENTO_TECLADO){
                if(evento.teclado.acao == PIG_TECLA_LIBERADA){
                    if(evento.teclado.tecla == PIG_TECLA_ESQUERDA){
                        velocidadeDaBusca*=2;
                    }else if(evento.teclado.tecla == PIG_TECLA_DIREITA){
                        velocidadeDaBusca/=2;
                    }
                }
            }
        }

        for(int i=0;i<qtdNiveis;i++){
            if(Niveis[i]->miss){
                Niveis[i]->escreveAlerta();
            }

            if(missTodosNiveis && !terminou){
                Niveis[indiceNivelAtt]->miss = false;
                if((Niveis[indiceNivelAtt]->iniY + Niveis[indiceNivelAtt]->altura/2)-20 < blocoDeTrocaMiss.iniY){
                    blocoDeTrocaMiss.iniY--;
                    blocoDeTrocaMiss.elementos[0].iniY--;
                }else if((Niveis[indiceNivelAtt]->iniY + Niveis[indiceNivelAtt]->altura/2)-20 > blocoDeTrocaMiss.iniY){
                    blocoDeTrocaMiss.iniY++;
                    blocoDeTrocaMiss.elementos[0].iniY++;
                }else if((Niveis[indiceNivelAtt]->iniX + Niveis[indiceNivelAtt]->largura)+8 < blocoDeTrocaMiss.iniX){
                    blocoDeTrocaMiss.iniX--;
                    blocoDeTrocaMiss.elementos[0].iniX--;
                }else{
                    int indiceAux = rand()%Niveis[indiceNivelAtt]->numElementos;
                    Niveis[indiceNivelAtt]->elementos[indiceAux].numero = elementoProcurado;
                    Niveis[indiceNivelAtt]->elementos[indiceAux].cor = LARANJA;
                    indiceNivelAtt--;
                    if(indiceNivelAtt < 0){
                        //reset a aplicacao
                        terminou = true;
                        DespausaTimer(temporizador);
                    }
                }

                blocoDeTrocaMiss.desenhaNivel();
                blocoDeTrocaMiss.elementos[0].numero = atoi(elementoBuscado);
                blocoDeTrocaMiss.desenharElementos();
            }
            if(terminou){
                if(TempoDecorrido(temporizador) > 15.0){
                    resetBusca();
                    memset(elementoBuscado, ' ', 20);
                    tamanhoElementoBuscado = 0;
                    nivel1.resetBlocos();
                    nivel2.resetBlocos();
                    nivel3.resetBlocos();
                    blocoDeTrocaMiss.iniX = 780;
                    blocoDeTrocaMiss.elementos[0].iniX = 785;
                    blocoDeTrocaMiss.iniY = 280;
                    blocoDeTrocaMiss.elementos[0].iniY = 285;
                    indiceNivelAtt = Niveis.size()-1;
                    ReiniciaTimer(temporizador,true);
                    terminou = false;
                }
            }
        }
        //todas as chamadas de desenho devem ser feitas aqui na ordem desejada
        //o frame totalmente pronto será mostrado na tela
        EncerraDesenho();
    }

    //o jogo será encerrado
    FinalizaJogo();

    return 0;
}

