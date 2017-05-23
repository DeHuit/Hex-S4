import javax.swing.*;
import java.awt.*;

public class BoardPanel extends JPanel {
  public static final double ANGLE = Math.PI/3; //60 degrees in rad
  public static final int RADIUS = 45/2; //Raduis

  private static int size;
  private static int [] cases;
  private static int player;
  private static int botColor;
  private static long board;
  private static long graphRed;
  private static long graphBlack;
  private static long history;
  private static long minimax;

  /* Param: size, bot color, beginner */
  public BoardPanel(int s, int botC, int beg) {
    this.size = s;
    this.player = beg;
    this.botColor = botC;
    this.board =  PartC.new_board(s, botColor);
    this.graphBlack = PartC.new_graph();
    this.graphRed = PartC.new_graph();
    if (botC != -1)
      this.minimax = PartC.new_minimax(board, (botC == 0)?graphRed:graphBlack, (botC == 1)?graphRed:graphBlack);
    this.cases = PartC.board_import(board);
    if (beg == 1)
      PartC.board_set_player(board, 1);
    else
      PartC.board_set_player(board, 0);
    this.history = PartC.new_history();
  }

  public static int getCellState(int pos) {
    return cases[pos];
  }

  public static int getBotColor() {
    return botColor;
  }

  public static long getBoard() {
    return board;
  }

  public static int getPlayer() {
    return player;
  }

  public static long getBotMinMax() {
    return minimax;
  }

  public static long getGraphRed() {
    return graphRed;
  }

  public static long getGraphBlack() {
    return graphBlack;
  }

  public static long getHistory() {
    return history;
  }

  public static int getSizeBoard() {
    return size;
  }

  public void playAt(int pos, int player) {
    cases[pos] = player;
    //System.out.println(" turn " + pos);
    PartC.board_set_case(board, pos, player, history, (player == 1)?graphRed:graphBlack);
    super.revalidate();
    super.repaint();
  }

  public void loadGame(String s) {
    clean();
    this.graphBlack = PartC.new_graph();
    this.graphRed = PartC.new_graph();
    this.board = PartC.board_load(s, graphRed, graphBlack);
    this.size = PartC.board_get_size(board);
    this.player = PartC.board_get_player(board);
    this.botColor = PartC.board_getBotColor(board);
    this.player = PartC.board_get_player(board);
    cases = PartC.board_import(board);
    //PartC.graph_restore(graphBlack, board, 0);
    //PartC.graph_restore(graphRed, board, 0);
    if (botColor != -1)
      this.minimax = PartC.new_minimax(board, (botColor == 0)?graphRed:graphBlack, (botColor == 1)?graphRed:graphBlack);
    this.history = PartC.new_history();

    super.revalidate();
    super.repaint();
  }

  public int stepBack(){
    int check = PartC.history_step_back(history, board, graphRed, graphBlack);
    if (check != -1){
      System.out.println("Rollback case : "+check);
      cases[check] = -1;
      player = PartC.board_get_player(board);
    }
    super.revalidate();
    super.repaint();
    return check;
  }

  public static void clean(){
    PartC.board_dispose(board);
    PartC.graph_dispose(graphRed);
    PartC.graph_dispose(graphBlack);
    PartC.history_dispose(history);
    if (botColor != -1)
      PartC.minimax_dispose(minimax);
  }

  private int offsetX = 2 * (int) (Math.sin(ANGLE)* (double) RADIUS);
  private int offsetY = RADIUS + (int) (Math.cos(ANGLE)* (double) RADIUS);
  private int offset = (int) (Math.sin(ANGLE)* (double) RADIUS);

  public void drawHex(Graphics g, int xC, int yC, int player) {

    int xCc = 0;
    int yCc = 15;

    int x = xC * offsetX + (yC-1)*offset + xCc;
    int y = yC*offsetY + yCc;

    int[] xPts={x, x + (int) (Math.sin(ANGLE)* (double) RADIUS), x + (int) (Math.sin(ANGLE)* (double) RADIUS), x, x - (int) (Math.sin(ANGLE)* (double) RADIUS), x - (int) (Math.sin(ANGLE)* (double) RADIUS)};
    int[] yPts={y - RADIUS, y - (int) (Math.cos(ANGLE)* (double) RADIUS), y + (int) (Math.cos(ANGLE)* (double) RADIUS), y + RADIUS, y + (int) (Math.cos(ANGLE)* (double) RADIUS), y - (int) (Math.cos(ANGLE)* (double) RADIUS)};
    Polygon p = new Polygon(xPts,yPts,6);

    g.setColor(Color.black);
    if (player == -1)
      g.drawPolygon(p);
    else {
      if (player == 1)
        g.setColor(Color.red);
      else
        g.setColor(Color.black);
      g.fillPolygon(p);
    }
  }

  @Override
	public void paintComponent(Graphics g) {
    super.paintComponent(g);
    g.setColor(Color.black);
    g.fillRect(0, 0, (int) this.getSize().getWidth(), 3);
    g.fillRect(0, (int) this.getSize().getHeight() - 3, (int) this.getSize().getWidth() , 3);
    g.setColor(Color.red);
    g.fillRect(0, 0, 3, (int) this.getSize().getHeight());
    g.fillRect((int) this.getSize().getWidth() - 3, 0, 3, (int) this.getSize().getHeight());
    g.setColor(Color.black);
    for (int i = 1; i <= size; i++) {
      StringBuilder sb = new StringBuilder();
      sb.append("");
      sb.append(i - 1);
      String strI = sb.toString();
      g.drawString(strI, i*38 -4, 20);
    }

    for (int y = 1; y <= size; y++){
      g.setColor(Color.black);
      StringBuilder sb = new StringBuilder();
      sb.append("");
      sb.append(y - 1);
      String strI = sb.toString();
      g.drawString(strI, 5, y*34 + 18);
      for (int x = 1; x <= size; x++)
          drawHex(g, x, y, cases[(y - 1)*size + (x-1)]);
      }
  }
}
