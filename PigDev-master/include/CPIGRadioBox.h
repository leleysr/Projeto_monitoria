#ifndef _CPIGRADIOBOX_
#define _CPIGRADIOBOX_

#include "CPIGListaItemComponente.h"

class CPIGRadioBox: public CPIGListaItemComponente{

protected:
    std::string arqImagemIcone;

    void SetFoco(bool valor){
        temFoco = valor;
    }

    void SetAcionado(bool valor){
    }

    void SetMouseOver(bool valor){
        mouseOver = valor;
    }

    static void AjustaFrame(PIGItemComponente item){
        int resp;
        if (item->GetHabilitado()==false){
            if (item->GetAcionado()) resp = 4;
            else resp = 3;
        }else if (item->GetMouseOver()){
            if (item->GetAcionado()) resp = 6;
            else resp = 5;
        }else{
            if (item->GetAcionado()) resp = 2;
            else resp = 1;
        }
        item->GetIcone()->MudaFrameAtual(resp);
    }

public:

    CPIGRadioBox(int idComponente, int posX, int posY, int larguraTotal,int alturaLinha, int alturaMaxima,std::string imgIcone, int alturaIcone, int larguraIcone,std::string imgFundo, int retiraFundo=1,int janela = 0):
        CPIGListaItemComponente(idComponente,posX,posY,larguraTotal,alturaLinha,alturaMaxima,imgFundo,retiraFundo,janela){
            arqImagemIcone = imgIcone;
        }

    CPIGRadioBox(std::string nomeArqParam):CPIGRadioBox(LeArquivoParametros(nomeArqParam)){}

    static CPIGRadioBox LeArquivoParametros(std::string nomeArqParam){
        std::ifstream arquivo;
        int idComponente,px,py,alturaItem,larguraItem,larguraTotal,alturaLinha,alturaMaxima,retiraFundo=1,janela=0;
        std::string imgFundo = "",imgItem = "",variavel;

        arquivo.open(nomeArqParam);

        if(!arquivo.is_open()) throw CPIGErroArquivo(nomeArqParam);
        //formato "x valor"
        while(!arquivo.eof()){
           arquivo >> variavel;
            if(variavel == "idComponente") arquivo >> idComponente;
            if(variavel == "px") arquivo >> px;
            if(variavel == "py") arquivo >> py;
            if(variavel == "larguraTotal") arquivo >> larguraTotal;
            if(variavel == "alturaItem") arquivo >> alturaItem;
            if(variavel == "larguraItem") arquivo >> larguraItem;
            if(variavel == "imgFundo") arquivo >> imgFundo;
            if(variavel == "imgItem") arquivo >> imgItem;
            if(variavel == "alturaLinha") arquivo >> alturaLinha;
            if(variavel == "alturaMaxima") arquivo >> alturaMaxima;
            if(variavel == "retiraFundo") arquivo >> retiraFundo;
            if(variavel == "janela") arquivo >> janela;
        }

        arquivo.close();

       // std::cout<<idComponente<<" "<<px<<" "<<py<<" "<<altura<<" "<<largura<<" "<<nomeArq<<" "<<retiraFundo<<" "<<janela<<std::endl;

        if(imgItem == "") throw CPIGErroParametro("imgItem",imgItem);

        return CPIGRadioBox(idComponente,px,py,larguraTotal,alturaLinha,alturaMaxima,imgItem,alturaItem,larguraItem,imgFundo,retiraFundo,janela);
    }

    void CriaItem(std::string itemLabel, std::string arqImagemFundoItem="",bool itemHabilitado = true, int audio=-1, std::string hintMsg="", int retiraFundo=1){
        int yItem = pos.y+alt-(altBaseLista)*(itens.size()+1);
        CPIGListaItemComponente::CriaItem(yItem,itemLabel,arqImagemIcone,arqImagemFundoItem,false,itemHabilitado,audioComponente,hintMsg,retiraFundo);
        itens[itens.size()-1]->DefineFuncaoAjusteFrame(AjustaFrame);
        PIGSprite icone = itens[itens.size()-1]->GetIcone();
        icone->CriaFramesAutomaticosPorLinha(1,1,6);
        icone->MudaFrameAtual(1);
    }

    int Desenha(){
        if (visivel==false) return 0;

        DesenhaLabel();

        SDL_Rect r = {(int)pos.x,*altJanela-((int)pos.y)-alt,larg,alt};
        SDL_RenderSetClipRect(renderer,&r);

        if (text)//se tiver imagem de fundo
            CPIGSprite::Desenha();

        for (PIGItemComponente i: itens)
            i->Desenha();

        SDL_RenderSetClipRect(renderer,NULL);

        return 1;
    }

    int TrataEventoMouse(PIG_Evento evento){
        int resp = -1;
        bool mouseOverAntes = mouseOver;

        SDL_Point p;
        if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
            p = CPIGMouse::PegaXYTela();
        else p = CPIGMouse::PegaXYWorld();

        if (ChecaMouseOver(p)>0){
            for (int i=0;i<itens.size();i++){
                if (itens[i]->TrataEventoMouse(evento) == PIG_SELECIONADO_TRATADO){
                    if (itens[i]->GetAcionado())
                        resp = i;
                }
            }
            SetAcionadoItem(resp,resp!=-1);
            if (resp>0)
                return PIG_SELECIONADO_TRATADO;
            else return PIG_SELECIONADO_MOUSEOVER;
        }else if (mouseOverAntes){               //mouse estava antes, mas saiu
            for (int i=0;i<itens.size();i++){
                itens[i]->SetMouseOver(false);
            }
        }

        return PIG_NAO_SELECIONADO;
    }

    int TrataEventoTeclado(PIG_Evento evento){
        return 0;
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGComponente::SetDimensoes(altura,largura);
        altMaxima = altura;

        for(PIGItemComponente i : itens){
            i->SetDimensoes(altIcone,largura);
        }

        Move(pos.x,pos.y);
    }

};

typedef CPIGRadioBox *PIGRadioBox;
#endif // _CPIGRADIOBOX_
