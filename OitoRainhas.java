//<html><pre>
//--------------------------------------------------------------
// Problema das 8 (oito) rainhas 
// Utilizando Threads
// Escrito por Alexsander da Rosa <alexsand@urcamp.tche.br>
//--------------------------------------------------------------
import java.awt.*;
import java.awt.event.*;

//--------------------------------------------------------------
//--------------------------------------------------------------
// CLASSE Tabuleiro
//--------------------------------------------------------------
//--------------------------------------------------------------
class Tabuleiro extends Canvas {

  public byte N = 8; //--- prevendo possivel extensao...
  public byte[] board = null;
  public void desenha(byte[] b) {
    board = b;
    repaint();
    }

  public Tabuleiro() {
    setSize(256,256);
    setVisible(true);
    repaint();
    }

  public void update(Graphics g) {
    paint(g);
    }

  public void paint(Graphics g) {
    int stepx, stepy, xp, yp, sx, sy, ptx[]=null, pty[]=null;

    stepx = 32; //----- calcula o tamanho do tabuleiro
    stepy = stepx;
    for (int x = 0 ; x < N ; x++) {
      for (int y = 0 ; y < N ; y++) {
        if ( ((x+y)%2) == 0 ) //----- testa se a casa e' branca ou preta
          g.setColor(Color.white);
        else
          g.setColor(Color.black);
        g.fillRect(x*stepx, y*stepy, stepx, stepy); //--- pinta
        if (board!=null && board[x]==y) { //----- desenha uma rainha
          g.setColor(Color.blue);
          sx = stepx/8; //--- calcula o tamanho
          sy = stepy/8;
          xp = x*stepx+sx;
          yp = y*stepy+sy;
          ptx = new int[7]; //--- aloca os vertices
          pty = new int[7];
          ptx[0] = xp;      pty[0] = yp; //--- coordenadas
          ptx[1] = xp+sx;   pty[1] = yp+sy*6;
          ptx[2] = xp+sx*5; pty[2] = yp+sy*6;
          ptx[3] = xp+sx*6; pty[3] = yp;
          ptx[4] = xp+sx*4; pty[4] = yp+sy*4;
          ptx[5] = xp+sx*3; pty[5] = yp;
          ptx[6] = xp+sx*2; pty[6] = yp+sy*4;
          g.fillPolygon(ptx,pty,7);
          }
        }
      }
    g.setColor(Color.black); //--- deixa a cor preta
    }

  }



//--------------------------------------------------------------
//--------------------------------------------------------------
// CLASSE OitoRainhas (principal)
//--------------------------------------------------------------
//--------------------------------------------------------------
public class OitoRainhas
  extends java.applet.Applet
  implements Runnable, ActionListener {

  Thread q1, q2, q3, q4, q5, q6, q7, q8;

  private int linha_atual;
  Tabuleiro tabuleiro = new Tabuleiro();

  Label contador = new Label();
  Button botao1 = new Button("Parar");
  Button botao2 = new Button("Ver");
  List lista = new List(15,false);

  //------------------------------------
  //------------------------------------
  public void init() {
    GridBagLayout gridbag = new GridBagLayout();
    GridBagConstraints c = new GridBagConstraints();
    setLayout(gridbag);

    c.gridx = 0;
    c.gridy = 0;
    gridbag.setConstraints(tabuleiro,c);
    add(tabuleiro);

    c.gridx = 1;
    c.gridy = 0;
    gridbag.setConstraints(lista,c);
    add(lista);

    c.gridx = 1;
    c.gridy = 1;
    gridbag.setConstraints(contador,c);
    add(contador);

    c.gridx = 0;
    c.gridy = 2;
    gridbag.setConstraints(botao1,c);
    add(botao1);
    botao1.addActionListener(this);

    c.gridx = 1;
    c.gridy = 2;
    gridbag.setConstraints(botao2,c);
    add(botao2);
    botao2.addActionListener(this);

    linha_atual = 0;
    }

  //------------------------------------
  //------------------------------------
  public void start() {
    if ( q1 == null ) {
      q1 = new Thread(this);
      q1.start();
      }
    q2 = new Thread(this);
    q2.start();
    q3 = new Thread(this);
    q3.start();
    q4 = new Thread(this);
    q4.start();
    q5 = new Thread(this);
    q5.start();
    q6 = new Thread(this);
    q6.start();
    q7 = new Thread(this);
    q7.start();
    q8 = new Thread(this);
    q8.start();
    }

  //------------------------------------
  // Desenha a tela
  //------------------------------------
  public void paint(Graphics g) {
    }

  //------------------------------------
  // Run()
  //------------------------------------
  public void run () {
    byte[] arr = new byte[8];
      for(int i = 0;i<arr.length;i++)
        arr[i] = 0;
      procura8rainhas(arr,linha_atual++); //---- cada Thread vai pegar uma linha
    }

  //------------------------------------
  // Procura as 8 rainhas
  //------------------------------------
  public void procura8rainhas (byte[] estado, int lin) {
    int col=0; 
    estado[col] = (byte)(lin-1);
    while ( col >= 0 ) {
      estado[col]++;
/*      try { //----- faz uma pausa 
        Thread.sleep(15); 
        } catch(InterruptedException e) { } */
      while ( estado[col] < 8 && atacada(estado,col) ) //--- nao deu
        {
        estado[col]++; //--- incrementa 
        tabuleiro.desenha(estado);
        //tabuleiro=estado;
        repaint();
        try { //----- faz uma pausa 
          Thread.sleep(15); 
          } catch(InterruptedException e) { }
        }

      if ( estado[col] < 8)
        if ( col == 7)
          solucao(lin,estado);
        else
          estado[++col] = -1;
      else {
        col--;
        if ( col==0 ) break;
        }
      }
    this.stop();
    }

  //------------------------------------
  // Verifica se uma rainha esta' sendo atacada
  //------------------------------------
  public boolean atacada(byte[] linha,int col) {
    int diferenca = linha[col] - col;
    int soma = linha[col] + col;
    for (int i=0;i<col;i++)
      if(linha[i] == linha[col])
        return true;
      else if((linha[i] - i) == diferenca)
             return true;
           else if((linha[i] + i) == soma)
                  return true;

    return false;
    }

  //------------------------------------
  // Encontrou uma solucao e a coloca na lista
  //------------------------------------
  public void solucao(int nome, byte[] sol){
    String s = new String(); 
    s = "[t"+nome+"] ";
    for(int i = 0;i<sol.length;i++)
      s += sol[i];
    //tabuleiro.desenha(sol);
    //tabuleiro=sol;
    lista.add(s); 
    contador.setText(lista.getItemCount()+" ");
    }

  //------------------------------------
  // Apertou o botao
  //------------------------------------
  public void actionPerformed(ActionEvent e){
    if ( e.getActionCommand() == "Parar") {
      if (q1 != null) q1.stop();
      if (q2 != null) q2.stop();
      if (q3 != null) q3.stop();
      if (q4 != null) q4.stop();
      if (q5 != null) q5.stop();
      if (q6 != null) q6.stop();
      if (q7 != null) q7.stop();
      if (q8 != null) q8.stop();
      }
    else if (e.getActionCommand() == "Ver") {
        String selection = lista.getSelectedItem();
        if(selection != null){ 
          byte[] arr = new byte[8];
          for(int i=0;i<8;i++)
            arr[i] = (byte)(Integer.parseInt(""+selection.charAt(i+5)));
          tabuleiro.desenha(arr);
        }
      }
    }

  //------------------------------------

  }
//</pre></html>
