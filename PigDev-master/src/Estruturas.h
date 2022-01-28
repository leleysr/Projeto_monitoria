#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#define TAM_BLOCO 30
#define DELTA_TIME 0.016

//Declara��o de variaveis importantes
float velocidadeDaBusca = 2;
int fonte, fonteAletaMiss, timer, qtdNiveis = 3, indiceNivelAtual = 0, elementoProcurado = 0;
bool continuarChecando = false, missTodosNiveis = false, ocorreuHit = false;

//Fun��o respons�vel por resetar elementos para o seu estado inicial.
void resetBusca(){
    indiceNivelAtual = 0;
    elementoProcurado = 0;
    continuarChecando = false;
    missTodosNiveis = false;
    ocorreuHit = false;
}

//Classe que representa os blocos pequenos que ficam dentro dos n�veis.
//Possui variaveis importantes como valor do bloco, sua posi��o, o seu tamanho e sua cor.
class Bloco{
public:
    int numero;
    int iniX, iniY;
    int tamanho;
    PIG_Cor cor;

    Bloco(int valor, int posicaoX, int posicaoY, int tamanhoBloco=TAM_BLOCO, PIG_Cor color = {78,88,97,255}){
        numero = valor;
        iniX = posicaoX;
        iniY = posicaoY;
        tamanho = tamanhoBloco;
        cor = color;
    }

public:
    //Fun��o respons�vel por desenhar o bloco em tela.
    void desenhaBloco(){
        DesenhaRetangulo(iniX,iniY,tamanho,tamanho,cor);
        EscreveInteiroCentralizado(numero,(iniX + tamanho/2),(iniY + tamanho/4),BRANCO,fonte);
    }

    //Fun��o respons�vel por alterar a cor do bloco.
    void trocaCor(PIG_Cor color){
        cor = color;
    }
};

//Classe que representa um n�vel( Parte grande que armazena um conjunto de blocos).
// Possui campos importantes no seu construtor, como:
//Sua posi��o, quantos elementos devem ter em uma linha, a quantidade de blocos que um n�vel tem, sua cor, etc.
class Nivel{
public:
    char * nomeNivel;
    int iniX, iniY;
    vector<Bloco> elementos;
    int minElementos, numElementos;
    int largura,altura;
    bool miss = false;
    bool hit = false;
    bool auxiliarSetPosicao = false;

    PIG_Cor cor;

    Nivel(int posicaoX,int posicaoY,int elementosLinha,int qtdBlocos,int larg=200,int alt=100,PIG_Cor color={158,205,191,255}){
        iniX = posicaoX;
        iniY = posicaoY;
        minElementos = elementosLinha;
        numElementos = qtdBlocos;
        largura = larg;
        altura = alt;
        cor = color;
    }

    //Fun��o respons�vel por desenha o n�vel em tela
    void desenhaNivel(){
        DesenhaRetangulo(iniX,iniY,altura,largura,cor);
    }

    //Fun��o respons�vel por verificar que blocos n�o sejam iniciados com valores iguais.
    bool validaValor(int valor){
        for(int i=0;i<elementos.size();i++){
            if(elementos[i].numero == valor){
                return false;
            }
        }
        return true;
    }

    //Fun��o respons�vel por criar os blocos, gerando valores aleatorios e setando as duas posi��es.
    void criarBlocos(int Qtd){
        for(int i = 0; i<Qtd; i++){
            int espacos = (largura - (TAM_BLOCO*minElementos))/(minElementos+1);
            int auxValor = 0;

            do{
                auxValor = (rand()%998)+1;
            }while(validaValor(auxValor) == false);

            Bloco auxBloco = Bloco(auxValor, iniX + (espacos*((i%minElementos)+1)) + (TAM_BLOCO*(i%minElementos)),(iniY+altura) - (espacos*((i/minElementos)+1)) - (TAM_BLOCO*((i/minElementos)+1)),TAM_BLOCO);
            elementos.push_back(auxBloco);
        }
    }

    //Fun��o respons�vel por resetar variaveis dos blocos e niveis importantes.
    void resetBlocos(){
        for(int i=0;i<elementos.size();i++){
            elementos[i].trocaCor({78,88,97,255});
        }
        ind = 0;
        tempo = 0;
        ReiniciaTimer(timer,true);
        miss = false;
        hit = false;
        auxiliarSetPosicao = false;
    }

    //Fun��o respons�vel por escrever um alerta ao lado do n�vel.
    void escreveAlerta(char * alerta){
        EscreverEsquerda(alerta,iniX+largura+10,iniY+(altura/2)-10,{78,88,97,255},fonteAletaMiss);
    }

    //Fun��o respons�vel por escrever uma string no centro do n�vel.
    void escreveNomeNivel(){
        EscreverCentralizada(nomeNivel,iniX+(largura/2),iniY+(altura/2),{78,88,97,255},fonteAletaMiss);
    }

    //Fun��o respons�vel por desenhar os elementos(blocos) do n�vel.
    void desenharElementos(){
        for(int i=0;i<elementos.size();i++){
            elementos[i].desenhaBloco();
        }
    }

    float tempo,ind =0;

    //Fun��o respons�vel por geranciar a busca. Ela que verifica se o valor foi procurado, se a busca deve ir para outro nivel,
    //se ocorreu cache hit ou miss. Gerencia a busca em geral.
    void procuraBloco(){
        if(TempoDecorrido(timer)> DELTA_TIME && ocorreuHit == false){
            if(tempo > velocidadeDaBusca){
                if(elementos[ind].numero == elementoProcurado){
                    elementos[ind].cor ={68,170,72,255};
                    ocorreuHit = true;
                    hit = true;
                    continuarChecando =  false;
                }else{
                    elementos[ind].cor ={239,73,65,255};
                }
                ReiniciaTimer(timer,true);
                tempo=0;
                ind++;
                if(ind == elementos.size() && ocorreuHit == false){
                    ind=0;
                    indiceNivelAtual++;
                    miss = true;
                    if(indiceNivelAtual == qtdNiveis){
                        continuarChecando = false;
                        missTodosNiveis = true;
                    }

                }
            }else{
                tempo+=DELTA_TIME;
            }
        }else{
            DespausaTimer(timer);
            tempo = 0;
            elementos[ind].cor ={246,167,33,255};
        }
    }

};

#endif // ESTRUTURAS_H_INCLUDED
