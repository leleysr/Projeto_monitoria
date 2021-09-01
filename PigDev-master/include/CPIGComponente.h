#ifndef _CPIGCOMPONENTE_
#define _CPIGCOMPONENTE_

#include "CPIGLabel.h"
#include "CPIGMouse.h"

typedef enum{PIG_COMPONENTE_CIMA_CENTRO,PIG_COMPONENTE_CIMA_ESQ,PIG_COMPONENTE_CIMA_DIR,PIG_COMPONENTE_BAIXO_CENTRO,PIG_COMPONENTE_BAIXO_DIR,PIG_COMPONENTE_BAIXO_ESQ,
             PIG_COMPONENTE_DIR_CIMA,PIG_COMPONENTE_DIR_BAIXO,PIG_COMPONENTE_DIR_CENTRO,PIG_COMPONENTE_ESQ_BAIXO,PIG_COMPONENTE_ESQ_CENTRO,PIG_COMPONENTE_ESQ_CIMA,
             PIG_COMPONENTE_CENTRO_CENTRO,PIG_COMPONENTE_PERSONALIZADA} PIG_PosicaoComponente;
typedef enum{PIG_ANCORA_NORTE,PIG_ANCORA_SUL,PIG_ANCORA_LESTE,PIG_ANCORA_OESTE,PIG_ANCORA_NORDESTE,PIG_ANCORA_NOROESTE,PIG_ANCORA_SUDESTE,PIG_ANCORA_SUDOESTE,PIG_ANCORA_CENTRO}PIG_Ancora;
typedef enum{PIG_NAO_SELECIONADO,PIG_SELECIONADO_MOUSEOVER,PIG_SELECIONADO_INVISIVEL,PIG_SELECIONADO_DESABILITADO,PIG_SELECIONADO_TRATADO}PIG_EstadosEventos;

class CPIGComponente: public CPIGSprite{

protected:

    bool temFoco,visivel,habilitado,mouseOver,acionado;
    int audioComponente;
    int id;
    PIG_PosicaoComponente posLabel,posComponente;
    PIGLabel lab,hint;

    //inicializa o componente com valores padr�o
    void IniciaBase(int idComponente, int px, int py){
        id = idComponente;
        lab = new CPIGLabel("",0,BRANCO,idJanela);
        hint = new CPIGLabel("",0,BRANCO,idJanela);
        SetPosicaoPadraoLabel(PIG_COMPONENTE_CENTRO_CENTRO);
        audioComponente = -1;
        pos = {px,py};
        mouseOver = acionado = temFoco = false;
        habilitado = visivel = true;
    }

    //escreve o hint do componente na tela
    void EscreveHint(){
        if (mouseOver&&hint->GetTexto()!=""){
            SDL_Point p;
            if (CPIGGerenciadorJanelas::GetJanela(idJanela)->GetUsandoCameraFixa())
                p = CPIGMouse::PegaXYTela();
            else p = CPIGMouse::PegaXYWorld();
            hint->Move(p.x+16,p.y+5);
            hint->Desenha();
        }
    }

    //detecta se o mouse est� sobre o componente ou n�o
    virtual int ChecaMouseOver(SDL_Point pMouse){
        if (visivel==false||habilitado==false)
            return -1;

        SDL_Rect r={(int)pos.x,(int)pos.y,larg,alt};
        SetMouseOver(SDL_PointInRect(&pMouse,&r));
        return mouseOver;
    }

    //move o label de acordo com a posi��o
    void PosicionaLabel(){
        int altLabel,largLabel;
        lab->GetDimensoes(altLabel,largLabel);
        switch(posLabel){
            case PIG_COMPONENTE_CIMA_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_CIMA_DIR:
                lab->Move(pos.x+larg,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_CIMA_ESQ:
                lab->Move(pos.x-largLabel,pos.y+alt+5);
                break;
            case PIG_COMPONENTE_BAIXO_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_BAIXO_DIR:
                lab->Move(pos.x+larg,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_BAIXO_ESQ:
                lab->Move(pos.x-largLabel,pos.y-altLabel);
                break;
            case PIG_COMPONENTE_ESQ_BAIXO:
                lab->Move(pos.x-5-largLabel,pos.y);
                break;
            case PIG_COMPONENTE_ESQ_CENTRO:
                lab->Move(pos.x-5-largLabel,pos.y+(alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_ESQ_CIMA:
                lab->Move(pos.x-5-largLabel,pos.y + (alt-altLabel));
                break;
            case PIG_COMPONENTE_DIR_BAIXO:
                lab->Move(pos.x+larg+5,pos.y);
                break;
            case PIG_COMPONENTE_DIR_CENTRO:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_DIR_CIMA:
                lab->Move(pos.x+larg+5,pos.y + (alt-altLabel));
                break;
            case PIG_COMPONENTE_CENTRO_CENTRO:
                lab->Move(pos.x+larg/2-largLabel/2,pos.y+(alt-altLabel)/2);
                break;
            case PIG_COMPONENTE_PERSONALIZADA:
                //lab->Move(pos.x+labelX,pos.y+labelY);
                break;
            }
    }

    //desenha o label
    inline void DesenhaLabel(){
        lab->Desenha();
    }

public:

    CPIGComponente(int idComponente,int px,int py, int altura, int largura, int janela=0)
    :CPIGSprite(idComponente,altura, largura, "",janela){
        IniciaBase(idComponente,px,py);
    }

    CPIGComponente(int idComponente,int px,int py, int altura, int largura, std::string nomeArq,int retiraFundo=1,int janela=0)
    :CPIGSprite(idComponente,nomeArq,retiraFundo,NULL,janela){
        IniciaBase(idComponente,px,py);
        CPIGSprite::SetDimensoes(altura,largura);
    }

    ~CPIGComponente(){
        if (lab) delete lab;
        if (hint) delete hint;
    }

    //recupera o id do componente
    int GetId(){
        return id;
    }

    //desenha o componente, cada subclasse precisa implementar como fazer isso
    virtual int Desenha()=0;

    virtual int TrataEventoMouse(PIG_Evento evento)=0;
    virtual int TrataEventoTeclado(PIG_Evento evento)=0;

    //define a mensagem de hint do componente
    void SetHint(std::string novoHint){
        hint->SetTexto(novoHint);
    }

    //define o label do componente
    virtual void SetLabel(std::string novoLabel){
        lab->SetTexto(novoLabel);
        PosicionaLabel();
    }

    //define a cor do label
    virtual void SetCorLabel(PIG_Cor corLabel){
        lab->SetCor(corLabel);
    }

    //recupera a cor do label
    virtual PIG_Cor GetCorLabel(){
        return lab->GetCor();
    }

    //define o audio padr�o do componentePIG_COMPONENTE_CENTRO_CENTRO
    virtual void SetAudio(int idAudio){
        audioComponente = idAudio;
    }

    //define a fonte do hint
    virtual void SetFonteHint(int fonte){
        hint->SetFonte(fonte);
    }

    //define a cor do hint
    virtual void SetCorHint(PIG_Cor cor){
        hint->SetCor(cor);
    }

    //recupera o hint
    std::string GetHint(){
        return hint->GetTexto();
    }

    //recupera a fonte do hint
    int GetFonteHint(){
        return hint->GetFonte();
    }

    //define a fonte do label
    virtual void SetFonteLabel(int fonte){
        lab->SetFonte(fonte);
        PosicionaLabel();
    }

    //recupera o label
    std::string GetLabel(){
        return lab->GetTexto();
    }

    //define a posi��o do label (dentre posi��es pr�-estabelecidas)
    virtual void SetPosicaoPadraoLabel(PIG_PosicaoComponente pos){
        posLabel = pos;
        PosicionaLabel();
    }

    //define a posi��o do label (posi��o arbiraria, relativa � posi��o do componente)
    virtual void SetPosicaoPersonalizadaLabel(int rx, int ry){
        lab->Move(pos.x+rx,pos.y+ry);
        posLabel = PIG_COMPONENTE_PERSONALIZADA;//evitar que o usu�rio esque�a de chamar tamb�m a SetPosicaoPadraoLabel
        PosicionaLabel();
    }

    virtual void SetVisivel(bool valor){
        visivel = valor;
    }

    virtual void SetFoco(bool valor)=0;

    virtual void SetHabilitado(bool valor)=0;

    virtual void SetMouseOver(bool valor)=0;

    virtual void SetAcionado(bool valor)=0;

    bool GetFoco(){
        return temFoco;
    }

    bool GetVisivel(){
        return visivel;
    }

    bool GetHabilitado(){
        return habilitado;
    }

    bool GetAcionado(){
        return acionado;
    }

    bool GetMouseOver(){
        return mouseOver;
    }

    PIG_PosicaoComponente GetPosComponente(){
        return posComponente;
    }

    void SetPosPadraoExternaComponente(PIG_PosicaoComponente pos,CPIGComponente *componenteAssociado){
        int altComponente,largComponente;
        PIGPonto2D p = componenteAssociado->GetXY();

        posComponente = pos;
        componenteAssociado->GetDimensoes(altComponente,largComponente);


        switch(pos){
        case PIG_COMPONENTE_CIMA_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_ESQ:
            Move(p.x,p.y+altComponente);
            break;
        case PIG_COMPONENTE_CIMA_DIR:
            Move(p.x + largComponente - larg,p.y+altComponente);
            break;
        case PIG_COMPONENTE_BAIXO_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y - alt);
            break;
        case PIG_COMPONENTE_BAIXO_ESQ:
            Move(p.x,p.y - alt);
            break;
        case PIG_COMPONENTE_BAIXO_DIR:
            Move(p.x + largComponente - larg,p.y - alt);
            break;
        case PIG_COMPONENTE_DIR_BAIXO:
            Move(p.x + largComponente,p.y);
            break;
        case PIG_COMPONENTE_DIR_CENTRO:
            Move(p.x + largComponente,p.y + (altComponente - alt)/2);
            break;
        case PIG_COMPONENTE_DIR_CIMA:
            Move(p.x + largComponente,p.y + altComponente - alt);
            break;
        case PIG_COMPONENTE_ESQ_BAIXO:
            Move(p.x - larg,p.y);
            break;
        case PIG_COMPONENTE_ESQ_CIMA:
            Move(p.x - larg,p.y + altComponente - alt);
            break;
        case PIG_COMPONENTE_ESQ_CENTRO:
            Move(p.x - larg,p.y + (altComponente - alt)/2);
            break;
        case PIG_COMPONENTE_CENTRO_CENTRO:
            Move(p.x + (largComponente - larg)/2,p.y + (altComponente - alt)/2);
            break;
        }

    }

    void SetPosPadraoComponenteNaTela(PIG_Ancora ancora){
        int largJanela;

        largJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetLargura();
        altJanela = CPIGGerenciadorJanelas::GetJanela(idJanela)->GetAltura();

        switch(ancora){
        case PIG_ANCORA_SUL:
            Move((largJanela - larg)/2,0);
            break;
        case PIG_ANCORA_SUDOESTE:
            Move(0,0);
            break;
        case PIG_ANCORA_SUDESTE:
            Move(largJanela - larg,0);
            break;
        case PIG_ANCORA_NORTE:
            Move((largJanela - larg)/2,*altJanela - alt);
            break;
        case PIG_ANCORA_NOROESTE:
            Move(0,*altJanela - alt);
            break;
        case PIG_ANCORA_NORDESTE:
            Move(largJanela - larg,*altJanela - alt);
            break;
        case PIG_ANCORA_CENTRO:
            Move((largJanela - larg)/2,(*altJanela - alt)/2);
            break;
        case PIG_ANCORA_OESTE:
            Move(0,(*altJanela - alt)/2);
            break;
        case PIG_ANCORA_LESTE:
            Move(largJanela - larg,(*altJanela - alt)/2);
            break;
        }

    }

    void Move(double nx, double ny)override{
        CPIGSprite::Desloca(nx-pos.x,ny-pos.y);
        PosicionaLabel();
    }

    void SetDimensoes(int altura,int largura)override{
        CPIGSprite::SetDimensoes(altura,largura);
        PosicionaLabel();
    }

};

typedef CPIGComponente *PIGComponente;
#endif // _CPIGCOMPONENTE_
