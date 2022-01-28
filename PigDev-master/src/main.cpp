#include "PIG.h"
#include "Estruturas.h"

#define WIDTH 1000
#define HEIGHT 600
#define DELTA_TIME 0.016
#define TEMPO_ESPERA 5.0

PIG_Evento evento;          //evento ser tratadoi a cada pssada do loop principal
PIG_Teclado meuTeclado;     //variável como mapeamento do teclado

int main( int argc, char* args[] ){

    //criando o jogo (aplicação)
    CriaJogo("Projeto Memoria Cache",0,HEIGHT,WIDTH);

    fonte = CriaFonteNormal("../fontes/arial.ttf", 12,BRANCO);
    fonteAletaMiss = CriaFonteNormal("../fontes/arial.ttf", 16,BRANCO);
    timer = CriaTimer(true);
    SetCorFundoJanela({225,230,211,255});


    //associando o teclado (basta uma única vez) com a variável meuTeclado

    //Declaração de variaveis importantes
    srand(time(NULL));
    bool terminou = false;
    int temporizador = CriaTimer(true);
    meuTeclado = GetTeclado();
    char elementoBuscado[20] =  "";
    int tamanhoElementoBuscado = 0;

    //Criação dos niveis e seus blocos que aparecerão na tela.
    Nivel nivel1 = Nivel(250,400,4,4,200,62);
    nivel1.criarBlocos(4);

    Nivel nivel2 = Nivel(350-192,225,8,16,384,108);
    nivel2.criarBlocos(16);

    Nivel nivel3 = Nivel(350-284,20,12,36,568,154);
    nivel3.criarBlocos(36);

    Nivel memPrincipal = Nivel(780,100,0,0,200,400);

    //Nivel usado na atualização dos níveis na ocorrencia de um cache miss
    Nivel blocoDeTrocaMiss = Nivel(780,280,1,1,40,40);
    blocoDeTrocaMiss.criarBlocos(1);

    //Nivel usado na atualização dos níveis na ocorrencia de um cache hit
    Nivel blocoDeTrocaHit = Nivel(780,280,1,1,40,40);
    blocoDeTrocaHit.criarBlocos(1);

    //Array com os niveis desenhados em tela
    vector<Nivel *> Niveis = {&nivel1,&nivel2,&nivel3};
    int indiceNivelAtt = Niveis.size()-1;

    //loop principal do jogo
    while(JogoRodando()){

        //pega um evento que tenha ocorrido desde a última passada do loop
        evento = GetEvento();

        //aqui o evento deve ser tratado e as coisas devem ser atualizadas

        //será feita aprepação do frame que será exibido na tela
        IniciaDesenho();

        //Inicia o desenho dos níveis e blocos na tela
        nivel1.desenhaNivel();
        nivel1.desenharElementos();

        nivel2.desenhaNivel();
        nivel2.desenharElementos();

        nivel3.desenhaNivel();
        nivel3.desenharElementos();

        memPrincipal.desenhaNivel();
        memPrincipal.nomeNivel = "Memoria Principal";
        memPrincipal.escreveNomeNivel();

        //Responsável pelos eventos do teclado.Pega os valores digitados no teclado numero(na parte de cima do teclado).
        //Backspace apaga um valor digitado.
        if( evento.tipoEvento == PIG_EVENTO_TECLADO && continuarChecando == false && terminou == false){
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

        //Escreve na tela o valor que esta sendo digitado.
        EscreverEsquerda("Valor Buscado:",15,500,{78,88,97,255});
        EscreveInteiroEsquerda(atoi(elementoBuscado),280,500,{78,88,97,255});

        // Responsável por resetar todas as variaveis necessarias para o seu estado inicial
        if( meuTeclado[PIG_TECLA_ESC]){
            resetBusca();
            memset(elementoBuscado, 0, 20);
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

        //Responsável por iniciar a busca do elemento
        if(meuTeclado[PIG_TECLA_ENTER]){
            continuarChecando = true;
            elementoProcurado = atoi(elementoBuscado);
        }

        //Responsável por controlar a velocidade da buscar e verificar se a busca deve continuar sendo feita ou não
        if(continuarChecando == true){
            Niveis[indiceNivelAtual%qtdNiveis]->procuraBloco();

            //Ajusta velocidade da busca
            if( evento.tipoEvento == PIG_EVENTO_TECLADO){
                if(evento.teclado.acao == PIG_TECLA_LIBERADA){
                    if(evento.teclado.tecla == PIG_TECLA_ESQUERDA){
                        velocidadeDaBusca = velocidadeDaBusca*2 > 5 ? 5 : velocidadeDaBusca*2;
                    }else if(evento.teclado.tecla == PIG_TECLA_DIREITA){
                        velocidadeDaBusca = velocidadeDaBusca/2 < 0.25 ? 0.25 : velocidadeDaBusca/2;
                    }
                }
            }
        }

        //Percorre todos os niveis verificando pontos importantes.
        for(int i=0;i<qtdNiveis;i++){
            if(Niveis[i]->miss){
                Niveis[i]->escreveAlerta("Cache Miss!");
            }else if(Niveis[i]->hit){
                Niveis[i]->escreveAlerta("Cache Hit!");
            }

            //Caso o bloco de dados não tenha sido encontrado em nenhum nível, um bloco sai da memoria atualizando todos os
            //níveis.
            if( missTodosNiveis && !terminou){
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
                    Niveis[indiceNivelAtt]->elementos[indiceAux].cor = {104,178,248,255};
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

            //Caso tenha ocorrido um cache hit, um bloco saí desse nível atualizando todos os superiores
            }else if(ocorreuHit && !terminou){
                if(indiceNivelAtual>0){
                    if(Niveis[indiceNivelAtual]->auxiliarSetPosicao == false){
                        blocoDeTrocaHit.iniX = (Niveis[indiceNivelAtual]->iniX + Niveis[indiceNivelAtual]->largura)+8;
                        blocoDeTrocaHit.iniY = (Niveis[indiceNivelAtual]->iniY + Niveis[indiceNivelAtual]->altura/2)-20;
                        blocoDeTrocaHit.elementos[0].iniX = blocoDeTrocaHit.iniX + 5;
                        blocoDeTrocaHit.elementos[0].iniY = blocoDeTrocaHit.iniY + 5;
                        Niveis[indiceNivelAtual]->auxiliarSetPosicao = true;
                    }
                    if((Niveis[indiceNivelAtual-1]->iniY + Niveis[indiceNivelAtual-1]->altura/2)-20 > blocoDeTrocaHit.iniY){
                        blocoDeTrocaHit.iniY++;
                        blocoDeTrocaHit.elementos[0].iniY++;
                    }else if((Niveis[indiceNivelAtual-1]->iniX + Niveis[indiceNivelAtual-1]->largura)+8 < blocoDeTrocaHit.iniX){
                        blocoDeTrocaHit.iniX--;
                        blocoDeTrocaHit.elementos[0].iniX--;
                    }else{

                        indiceNivelAtual--;
                        int indiceAux = rand()%Niveis[indiceNivelAtual]->numElementos;
                        Niveis[indiceNivelAtual]->miss = false;
                        Niveis[indiceNivelAtual]->elementos[indiceAux].numero = elementoProcurado;
                        Niveis[indiceNivelAtual]->elementos[indiceAux].cor = {104,178,248,255};
                        if(indiceNivelAtual <= 0){
                            //reset a aplicacao
                            terminou = true;
                            DespausaTimer(temporizador);
                        }
                    }

                    blocoDeTrocaHit.desenhaNivel();
                    blocoDeTrocaHit.elementos[0].numero = atoi(elementoBuscado);
                    blocoDeTrocaHit.desenharElementos();
                }else{
                    terminou = true;
                    DespausaTimer(temporizador);
                }
            }

            //Caso a execução da busca e atualização tenha se encerrado, espera um tempo configurável e depois reseta toda
            //a aplicação, voltando para o seu estado inicial.
            if(terminou){
                if(TempoDecorrido(temporizador) > TEMPO_ESPERA){
                    resetBusca();
                    memset(elementoBuscado, 0, 20);
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
                    //----//
                    elementoProcurado = 0;
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

