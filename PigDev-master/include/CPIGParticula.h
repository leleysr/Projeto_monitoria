#ifndef _CPIGPARTICULA_
#define _CPIGPARTICULA_

#include "CPIGAnimacao.h"

class CPIGParticula: public CPIGAnimacao{

private:

SDL_Rect espacoVida;
double hp;
double tempoVida;
int timer;

double ModificaHP(double valor){
    hp += valor;
    viva = hp>0;
}

public:
    bool viva;

    CPIGParticula(int idParticula,PIGAnimacao base,int vida,int retiraFundo=1,PIG_Cor *corFundo=NULL,int idJanela=0):
        CPIGAnimacao(idParticula,base,retiraFundo,corFundo,idJanela){
        hp = vida;
        espacoVida = {INT_MIN,INT_MIN,INT_MAX,INT_MAX};
        tempoVida = 9999999;
        viva = true;
        timer = CPIGGerenciadorTimers::CriaTimer();
    }

    void DefineLimites(SDL_Rect espacoMax, double tempoMax){
        espacoVida = espacoMax;
        tempoVida = tempoMax;
    }

    ~CPIGParticula(){
        CPIGGerenciadorTimers::DestroiTimer(timer);
    }

    inline void ChecaTempoVida(){
        viva = viva&&CPIGGerenciadorTimers::GetTimer(timer)->GetTempoDecorrido()<=tempoVida;
        //if (!viva) PRINTF("%d morri por tempo\n",id);
    }

    void Move(double nx, double ny) override{
        if (!viva) return;
        CPIGObjeto::Move(nx,ny);
        //printf("rect %d,%d, %d,%d,%d,%d\n",pos.x,pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        viva = (pos.x>espacoVida.x)&&(pos.x<espacoVida.w)&&(pos.y>espacoVida.y)&&(pos.y<espacoVida.h);
        //printf("movendo %d,%d %d\n",nx,ny,viva);
        //if (!viva) {
        //    printf("morri espaco %.2f %.2f %d,%d %d,%d\n",pos.x,pos.y,espacoVida.x,espacoVida.y,espacoVida.w,espacoVida.h);
        //}
    }

    bool Colisao(PIGObjeto outro) override{
        bool resp = CPIGObjeto::Colisao(outro);
        if (resp){
            ModificaHP(-1);
        }
        return resp;
    }

    bool Colisao(CPIGParticula *outra){
        bool resp = CPIGObjeto::Colisao(outra);
        if (resp){
            ModificaHP(-1);
            outra->ModificaHP(-1);
        }
        return resp;
    }
};

typedef CPIGParticula* PIGParticula;
#endif //_CPIGPARTICULA_
