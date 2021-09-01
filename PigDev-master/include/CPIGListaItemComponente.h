#ifndef _CPIGLISTAITEMCOMPONENTE_
#define _CPIGLISTAITEMCOMPONENTE_

#include "CPIGItemComponente.h"

class CPIGListaItemComponente: public CPIGComponente{

protected:

    int fonteItens;
    int altBaseLista,altMaxima;                     //espa�o vertical entre os itens
    PIG_PosicaoComponente posIcones,posLabels;
    std::vector <PIGItemComponente> itens;
    int itemDestaque;
    int altIcone,largIcone;                           //altura e largura das imagens dos itens

    void IniciaBase(int alturaLinha, int alturaTotal){
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CIMA_CENTRO);//posi��o padr�o do label
        altBaseLista = alturaLinha;
        altMaxima = alturaTotal;
        altIcone = largIcone = alturaLinha;
        posIcones = PIG_COMPONENTE_DIR_CENTRO;//s� pode ser posicionamento � esquerda ou � direita
        itemDestaque = -1;
        fonteItens = 0;
    }

    void CriaItem(int yItem,std::string itemLabel, std::string arqImagemIcone="",std::string arqImagemFundo="",bool itemMarcado = false, bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        PIGItemComponente item;
        if (arqImagemFundo==""){
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),pos.x,yItem,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),pos.x,yItem,altIcone,largIcone,arqImagemIcone,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }
        }else{
            if (arqImagemIcone==""){
                item = new CPIGItemComponente(itens.size(),pos.x,yItem,arqImagemFundo,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }else{
                item = new CPIGItemComponente(itens.size(),pos.x,yItem,altIcone,largIcone,arqImagemIcone,arqImagemFundo,itemLabel,larg,altBaseLista,retiraFundo,idJanela);
            }
        }
        item->SetHint(hintMsg);

        if (audio==-1) audio = audioComponente;//audio padrao do componente

        item->SetAudio(audio);
        item->SetAcionado(itemMarcado);
        item->SetHabilitado(itemHabilitado);
        itens.push_back(item);
    }

public:

    CPIGListaItemComponente(int idComponente, int posX, int posY, int larguraTotal, int alturaLinha, int alturaTotal,std::string nomeArqFundoLista, int retiraFundo=1,int janela = 0):
        CPIGComponente(idComponente,posX,posY,alturaTotal,larguraTotal,nomeArqFundoLista,retiraFundo,janela){
        IniciaBase(alturaLinha,alturaTotal);
    }

    ~CPIGListaItemComponente(){
        for (PIGItemComponente i: itens)
            delete i;
        itens.clear();
    }

    void DefineDimensaoIconeItem(int alturaImagemIcone, int larguraImagemIcone){
        altIcone = alturaImagemIcone;
        largIcone = larguraImagemIcone;
        for (int i=0;i<itens.size();i++){
            itens[i]->SetDimensoesIcone(altIcone,largIcone);
        }
    }

    void AlinhaLabelDireita(){
        if (posLabels!=PIG_COMPONENTE_DIR_CENTRO){//se os labels est�o � direita do bot�es, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelDireita();
            posLabels = PIG_COMPONENTE_DIR_CENTRO;
        }
    }

    void AlinhaLabelEsquerda(){
        if (posLabels!=PIG_COMPONENTE_ESQ_CENTRO){//se os labels est�o � direita do bot�es, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelEsquerda();
            posLabels = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    void AlinhaLabelCentro(){
        if (posLabels!=PIG_COMPONENTE_CENTRO_CENTRO){//se os labels est�o � direita do bot�es, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaLabelCentro();
            posLabels = PIG_COMPONENTE_CENTRO_CENTRO;
        }
    }

    void AlinhaIconeDireita(){
        if (posIcones==PIG_COMPONENTE_ESQ_CENTRO){//se os labels est�o � direita do bot�es, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaIconeDireita();
            posIcones = PIG_COMPONENTE_DIR_CENTRO;
        }
    }

    void AlinhaIconeEsquerda(){
        if (posIcones!=PIG_COMPONENTE_DIR_CENTRO){//se os labels est�o � direita do bot�es, inverte
            for (PIGItemComponente i: itens)
                i->AlinhaIconeEsquerda();
            posIcones = PIG_COMPONENTE_ESQ_CENTRO;
        }
    }

    void SetFonteItensLista(int fonte){
        fonteItens = fonte;
        for(PIGItemComponente item :itens) item->SetFonteLabel(fonte);
    }

    virtual int Desenha()=0;

    int GetAcionadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetAcionado();
    }

    int SetAudioItem(int item, int audio){
        if (item<0||item>=itens.size()) return -1;
        itens[item]->SetAudio(audio);
        return 1;
    }

    int GetHabilitadoItem(int item){
        if (item<0||item>=itens.size()) return -1;
        return itens[item]->GetHabilitado();
    }

    int SetHabilitadoItem(int item, bool valor){
        if (item<0||item>=itens.size()) return -1;
        itens[item]->SetHabilitado(valor);
        return 1;
    }

    void SetHabilitado(bool valor) override{
        habilitado = valor;
        for(PIGItemComponente i: itens)
            i->SetHabilitado(habilitado);
    }

    void SetVisivel(bool valor) override{
        visivel = valor;
        for(PIGItemComponente i: itens)
            i->SetVisivel(visivel);
    }

    void SetFonteHint(int fonte) override{
        for (PIGItemComponente i: itens)
            i->SetFonteHint(fonte);
    }

    void SetAudio(int audio) override{
        audioComponente = audio;
        for (PIGItemComponente i: itens)
            i->SetAudio(audio);
    }

    int GetItemDestaque(){
        return itemDestaque;
    }

    int SetAcionadoItem(int indice, bool marcado){
        if (indice<0||indice>=itens.size()) return 0;
        if (marcado){
            itemDestaque = indice;
            for (PIGItemComponente i: itens)
                i->SetAcionado(false);
        }
        itens[indice]->SetAcionado(marcado);
        return 1;
    }

    void Move(double nx,double ny){
        double dx = nx-pos.x;
        double dy = ny-pos.y;

        CPIGSprite::Desloca(dx,dy);
        PosicionaLabel();

        for(int i=0;i<itens.size();i++)
            itens[i]->Desloca(dx, dy);

        AlinhaLabelEsquerda();
    }

};
typedef CPIGListaItemComponente *PIGListaComponente;
#endif //_CPIGLISTAITEMCOMPONENTE_
