#ifndef _CPIGMODOANIMACAO_
#define _CPIGMODOANIMACAO_

//struct com aqs informa��esde cada est�gio (frame) do modo
typedef struct{
    int frame;      //n�mero do frame
    double tempo;   //tempo de exibi��o do frame
    int audio;      //audio a ser tocado quando o frame for exibido
    int altura,largura;
}EstagioAnimacao;

class CPIGModoAnimacao{

private:

int frameAtual;                         //n�mero do frame atual
bool loop;                              //se o modo tem loop ou n�o
bool encerrou;                          //indica se o modo terminou de eibir todos os frames
std::vector<EstagioAnimacao> estagios;  //informa��es dos est�gios (frames) que comp�em o modo

public:

    //construtor do modo
    CPIGModoAnimacao(bool emLoop=true){
        frameAtual = 0;
        loop = emLoop;
        encerrou = false;
    }

    CPIGModoAnimacao(CPIGModoAnimacao *modoBase){
        encerrou = modoBase->encerrou;
        estagios = modoBase->estagios;
        SetLoop(modoBase->loop);
        SetIndiceFrameAtual(modoBase->frameAtual);
    }

    //destrutor
    ~CPIGModoAnimacao(){
        estagios.clear();
    }

    //cria um novo est�gio (frame)
    int InsereEstagio(int idFrame, double tempo, int idAudio, int altura, int largura){
        EstagioAnimacao estagio={idFrame,tempo,idAudio,altura,largura};
        estagios.push_back(estagio);
        return estagios.size()-1;
    }

    //define o tempo de um est�gio (frame) j� criado
    void SetTempo(int idEstagio, double novoTempo){
        estagios[idEstagio].tempo = novoTempo;
    }

    //define o audio de um est�gio (frame) j� criado
    void SetAudio(int idEstagio, int idAudio){
        estagios[idEstagio].audio = idAudio;
    }

    //define se o modo estra�em loop ou n�o
    void SetLoop(bool emLoop){
        loop = emLoop;
    }

    //retorna se o modo est� em loop ou n�o
    bool GetLoop(){
        return loop;
    }

    //muda arbitrariamente o �ndice (posi��o da sequ�ncia de frames) do frame a ser exibido
    void SetIndiceFrameAtual(int indice){
        if (indice<frameAtual)
            encerrou = false;
        frameAtual = indice;
    }

    //retorna o �ndice (posi��od o vetor) do frame atual
    int GetIndiceFrameAtual(){
        return frameAtual;
    }

    //retorna o n�mero do frame atual
    int GetFrameAtual(){
        return estagios[frameAtual].frame;
    }

    //retorna o audio do frame atual
    int GetAudioAtual(){
        return estagios[frameAtual].audio;
    }

    //retorna o tempo de exibi��o do frame atual
    double GetTempoAtual(){
        return estagios[frameAtual].tempo;
    }

    //retorna o audio de um frame j� criado (pelo seu �ndice no vetor)
    int GetAudioFrame(int indiceFrame){
        return estagios[indiceFrame].audio;
    }

    //retorna o tempo de um frame j� criado (pelo seu �ndice no vetor)
    double GetTempoFrame(int indiceFrame){
        return estagios[indiceFrame].tempo;
    }

    void GetDimensoesAtual(int &altura, int &largura){
        //if (estagios[frameAtual].altura < 0) return false;
        altura = estagios[frameAtual].altura;
        largura = estagios[frameAtual].largura;
        //return true;
    }

    //teste se j� passou o tempo necess�rio para mudar de frame
    int TestaTempo(double tempoDecorrido){
        encerrou = false;
        if (estagios.size()==0) return 0;//nao foi criado nenhum estagio nesse modo
        int frameAntigo = frameAtual;//armazena o valor do frameAtual
        if (tempoDecorrido>=estagios[frameAtual].tempo){
            if (frameAtual < estagios.size()-1){//se ainda nao chegou no �ltimo est�gio
                frameAtual++;
            }else{//chegou no �ltimo est�gio
                if (loop)
                    frameAtual = 0;//se est� em loop, volta ao primeiro frame
                else encerrou=true;
            }
        }
        return frameAtual!=frameAntigo;//retorna se alterou o frameAtual
    }

    //retorna se o modo j� exibiu todos os frames (apenas se n�o estiver em loop)
    bool GetEncerrou(){
        return encerrou;
    }

};

typedef CPIGModoAnimacao *PIGModoAnimacao;
#endif // _CPIGMODOANIMACAO_
