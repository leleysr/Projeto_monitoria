#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

#define TAM_BLOCO 30
#define DELTA_TIME 0.016

float velocidadeDaBusca = 2;
int fonte, fonteAletaMiss, timer, qtdNiveis = 3, indiceNivelAtual = 0, elementoProcurado = 0;
bool continuarChecando = false, missTodosNiveis = false;

void resetBusca(){
    indiceNivelAtual = 0;
    elementoProcurado = 0;
    continuarChecando = false;
    missTodosNiveis = false;
}

class Bloco{
public:
    int numero;
    int iniX, iniY;
    int tamanho;
    PIG_Cor cor;

    Bloco(int valor, int posicaoX, int posicaoY, int tamanhoBloco=TAM_BLOCO, PIG_Cor color = {0,0,255,255}){
        numero = valor;
        iniX = posicaoX;
        iniY = posicaoY;
        tamanho = tamanhoBloco;
        cor = color;
    }

public:

    void desenhaBloco(){
        DesenhaRetangulo(iniX,iniY,tamanho,tamanho,cor);
        EscreveInteiroCentralizado(numero,(iniX + tamanho/2),(iniY + tamanho/4),BRANCO,fonte);
    }

    void trocaCor(PIG_Cor color){
        cor = color;
    }
};

class Nivel{
public:
    char * nomeNivel;
    int iniX, iniY;
    vector<Bloco> elementos;
    int minElementos, numElementos;
    int largura,altura;
    bool miss = false;
    PIG_Cor cor;

    Nivel(int posicaoX,int posicaoY,int elementosLinha,int qtdBlocos,int larg=200,int alt=100,PIG_Cor color={0,144,144,255}){
        iniX = posicaoX;
        iniY = posicaoY;
        minElementos = elementosLinha;
        numElementos = qtdBlocos;
        largura = larg;
        altura = alt;
        cor = color;
    }

    void desenhaNivel(){
        DesenhaRetangulo(iniX,iniY,altura,largura,cor);
        //EscreveInteiroCentralizado(numero,(iniX + tamanho/2),(iniY + tamanho/4),BRANCO,fonte);
    }

    void criarBlocos(int Qtd){
        for(int i = 0; i<Qtd; i++){
            int espacos = (largura - (TAM_BLOCO*minElementos))/(minElementos+1);

            ////////////////////////ALTERAR O VALOR DO BLOCO
            Bloco auxBloco = Bloco(rand()%999, iniX + (espacos*((i%minElementos)+1)) + (TAM_BLOCO*(i%minElementos)),(iniY+altura) - (espacos*((i/minElementos)+1)) - (TAM_BLOCO*((i/minElementos)+1)),TAM_BLOCO);
            elementos.push_back(auxBloco);
        }
    }

    void resetBlocos(){
        for(int i=0;i<elementos.size();i++){
            elementos[i].trocaCor({0,0,255,255});
        }
        ind = 0;
        tempo = 0;
        ReiniciaTimer(timer,true);
        miss = false;
    }

    void escreveAlerta(){
        EscreverEsquerda("Cache Miss!",iniX+largura+10,iniY+(altura/2)-10,BRANCO,fonteAletaMiss);
    }

    void escreveNomeNivel(){
        EscreverCentralizada(nomeNivel,iniX+(largura/2),iniY+(altura/2),BRANCO,fonteAletaMiss);
    }

    void desenharElementos(){
        for(int i=0;i<elementos.size();i++){
            elementos[i].desenhaBloco();
        }
    }

    float tempo,ind =0;
    void procuraBloco(){
        if(TempoDecorrido(timer)> DELTA_TIME){
            if(tempo > velocidadeDaBusca){
                if(elementos[ind].numero == elementoProcurado){
                    elementos[ind].cor ={0,255,0,255};
                    continuarChecando =  false;
                }else{
                    elementos[ind].cor ={255,0,0,255};
                }
                ReiniciaTimer(timer,true);
                tempo=0;
                ind++;
                if(ind == elementos.size()){
                    ind=0;
                    indiceNivelAtual++;
                    miss = true;
                    //if(indiceNivelAtual%qtdNiveis == 0){
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
            elementos[ind].cor ={255,255,0,255};
        }
    }

};

#endif // ESTRUTURAS_H_INCLUDED
