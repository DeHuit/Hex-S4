import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import java.nio.file.*;
import java.io.File;

public class MainWindow extends JFrame {
  private static int player = 1;
  private static int size;
  private static int beginner;
  private static int botColor;
  private static SettingsWindow set;

  /*******************/
  /* Frame & Friends */
  /******************/
  private static JFrame f = new JFrame("Hex");
  private static JPanel mainPanel = new JPanel();
  /* Menu Bar*/
  private static JMenuBar menuBar = new JMenuBar();
  private static JMenu game = new JMenu("Game");
  private static JMenu options = new JMenu("Options");
  /* Menu Items */
  private static JMenuItem newGame = new JMenuItem("New game");
  private static JMenuItem loadOption = new JMenuItem("Load");
  private static JMenuItem saveOption = new JMenuItem("Save");
  private static JMenuItem stepBack = new JMenuItem("StepBack");
  private static JMenuItem settings = new JMenuItem("Settings");

  /* Center board container */
  private static BoardPanel board;
  /* Red player container */
  private static JPanel redPanel = new JPanel(new FlowLayout());
  private static JButton redB = new JButton("Add");
  private static JTextField redX = new JTextField(2);
  private static JTextField redY = new JTextField(2);
  /* Black player container */
  private static JPanel blackPanel = new JPanel(new FlowLayout());
  private static JButton blackB = new JButton("Add");
  private static JTextField blackX = new JTextField(2);
  private static JTextField blackY = new JTextField(2);

  public MainWindow(int beg, int sizeB, int botC, SettingsWindow s) {
    beginner = beg;
    player = beg;
    size = sizeB;
    board = new BoardPanel(size, botC, beg);
    botColor = botC;
    set = s;
  }

  private static void switchSides(JTextField ea, JTextField eb, JButton ebut,
                                  JTextField da, JTextField db, JButton dbut) {
    ea.setEditable(true);
    eb.setEditable(true);
    ebut.setEnabled(true);
    da.setEditable(false);
    db.setEditable(false);
    dbut.setEnabled(false);
  }

  private static void initInputForm(JTextField a) {
    a.addKeyListener(new KeyAdapter() {
      public void keyTyped(KeyEvent e) {
        if (a.getText().length() > 1 )// limit textfield to 2 characters
            e.consume();
      }
      });
  }

  private static void game_over() {
    redX.setEditable(false);
    redY.setEditable(false);
    blackX.setEditable(false);
    blackY.setEditable(false);
    redB.setEnabled(false);
    blackB.setEnabled(false);
  }

  private static void forceResize(){
    f.setSize( new Dimension(235 + (size * 3/ 2 )*  (2 * (int)(Math.sin(BoardPanel.ANGLE) * (double) BoardPanel.RADIUS)),
                              94 + size * (BoardPanel.RADIUS + (int) (Math.cos(BoardPanel.ANGLE) * (double) BoardPanel.RADIUS)) ));
    board.setSize(new Dimension(2* (int) Math.sin(board.ANGLE)*board.RADIUS * (2*size-1),
                                (board.RADIUS * 2 + (int) Math.cos(board.ANGLE)*board.RADIUS) * size));

  }

  public static void createGUI() {
    /*Main Frame settings */

    f.setLocationRelativeTo(null);
    f.setVisible(true);
    forceResize();
    f.setResizable(false);
    f.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
    forceResize();
    //f.setSize( new Dimension(224 + (size * 3/ 2 )*  (2 * (int)(Math.sin(BoardPanel.ANGLE) * (double) BoardPanel.RADIUS)),
    //                          54 + size * (BoardPanel.RADIUS + (int) (Math.cos(BoardPanel.ANGLE) * (double) BoardPanel.RADIUS)) ));
    /* Close dialog */
    f.addWindowListener(new WindowListener() {
        /* Some overrided methodes (no idea why are they here, but it doesnt work without em) */
        public void windowActivated(WindowEvent event) {}
        public void windowClosed(WindowEvent event) {}
        public void windowDeactivated(WindowEvent event) {}
        public void windowDeiconified(WindowEvent event) {}
        public void windowIconified(WindowEvent event) {}
        public void windowOpened(WindowEvent event) {}
        public void windowClosing(WindowEvent event) {
            Object[] opt = { "Yes", "No" };
            int n = JOptionPane.showOptionDialog(event.getWindow(),
                    "Are you sure you want to quit?", "Confirmation",
                    JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null, opt, opt[0]);
            if (n == 0){
              event.getWindow().setVisible(false);
              System.exit(0);
            }
            return;
        }
    });

    /* Main container */
    mainPanel.setLayout(new BorderLayout());

    /* Menu Bar */
    menuBar.add(game);
    menuBar.add(options);
      /* Menu "Game" Items */
    game.add(newGame);
    game.add(loadOption);
    game.add(saveOption);

    /* Menu "Setting" items*/
    options.add(settings);
    options.add(stepBack);

    /* Center board container */
    board.setLayout(new FlowLayout());
    board.setBorder(null);
    board.setSize(new Dimension(2* (int) Math.sin(board.ANGLE)*board.RADIUS * (2*size-1),
                                (board.RADIUS * 2 + (int) Math.cos(board.ANGLE)*board.RADIUS) * size));

    /* Red player container */
    redPanel.setBorder(BorderFactory.createTitledBorder("RED"));
    redPanel.setPreferredSize(new Dimension(100,30));
    redB.setSize(new Dimension(20, 10));
    initInputForm(redX);
    initInputForm(redY);
    redPanel.add(redX);
    redPanel.add(redY);
    redPanel.add(redB);

    /* Black player container */
    blackPanel.setBorder(BorderFactory.createTitledBorder("BLACK"));
    blackPanel.setPreferredSize(new Dimension(100, 30));
    blackB.setSize(new Dimension(20, 10));
    initInputForm(blackX);
    initInputForm(blackY);
    blackPanel.add(blackX);
    blackPanel.add(blackY);
    blackPanel.add(blackB);

    /* Action: Listeners */
    /*When player sets coordinates, we have to transmit all info and disactivate field */
    /* Pressing "add" on the red side causes red player's turn */
    redB.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        int x = Integer.parseInt(redX.getText());
        int y = Integer.parseInt(redY.getText());
        boolean played = false;
        if (0 <= x && x < size && 0 <= y && y < size){
          if (board.getCellState(x*size + y) == -1){
            played = played;
            board.playAt(x*size + y, 1);
            switchSides(blackX, blackY, blackB, redX, redY, redB);
          }
          else
            JOptionPane.showMessageDialog(null, "Case " + x + "," + y + " is already played!",
                                          "Wrong coordinates", JOptionPane.ERROR_MESSAGE);
        }
        else
          JOptionPane.showMessageDialog(null, x + " or " + y + " are out of board!",
                                      "Wrong coordinates", JOptionPane.ERROR_MESSAGE);
        redX.setText("");
        redY.setText("");
        if (played) {
          if (PartC.red_wins(board.getGraphRed(), board.getBoard())) {
            JOptionPane.showMessageDialog(null, "Red wins! " + " Fatality.");
            game_over();
          }
          else{
            /* Bot join the game */
            if (board.getBotColor() == 0) {
              board.playAt(PartC.bot_get_turn(board.getBotMinMax(), board.getBoard(), board.getHistory()), 0);
              switchSides(redX, redY, redB, blackX, blackY, blackB);
              if (PartC.black_wins(board.getGraphBlack(), board.getBoard())) { //black bot wins
                JOptionPane.showMessageDialog(null, "OMG, AI playing BLACK just kicked your ass!");
                game_over();
              }
            }
          }
        }
      }
    });
    /* Pressing "add" on the black side causes black player's turn */
    blackB.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        int x = Integer.parseInt(blackX.getText());
        int y = Integer.parseInt(blackY.getText());
        boolean played = false;
        if (0 <= x && x < size && 0 <= y && y < size){
          if (board.getCellState(x*size + y) == -1){
            board.playAt(x*size + y, 0);
            switchSides(redX, redY, redB, blackX, blackY, blackB);
            played = true;
          }
          else
            JOptionPane.showMessageDialog(null, "Case " + x + "," + y + " is already played!",
                                        "Wrong coordinates", JOptionPane.ERROR_MESSAGE);
        }
        else
          JOptionPane.showMessageDialog(null, x + " or " + y + " are out of board!",
                                    "Wrong coordinates", JOptionPane.ERROR_MESSAGE);
        blackX.setText("");
        blackY.setText("");
        /* Bot join the game */
        if (played) {
          if (PartC.black_wins(board.getGraphBlack(), board.getBoard())) {
            JOptionPane.showMessageDialog(null, "Black wins!" + " Fatality");
            game_over();
          }
          else{
            if (board.getBotColor() == 1) {
              board.playAt(PartC.bot_get_turn(board.getBotMinMax(), board.getBoard(), board.getHistory()), 1);
              switchSides(blackX, blackY, blackB, redX, redY, redB);
              if (PartC.red_wins(board.getGraphRed(), board.getBoard())) { //Red bot wins
                JOptionPane.showMessageDialog(null, "OMG, AI playing RED just kicked your ass!");
                game_over();
              }
            }
          }
        }
      }
    });

    /* Menu actions */
    /* Launch new game (no settings required)*/
    newGame.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        int confButton = JOptionPane.YES_NO_OPTION;
        int confResult = JOptionPane.showConfirmDialog(null, "Launching new game you erase your progress.\n Are you sure? ",
                            "Confirmation", confButton);

        if (confResult == 1)
          return;

        game_over();
        board.clean();
        board.setVisible(false);
        mainPanel.remove(board);
        board = new BoardPanel(size, botColor, beginner);
        mainPanel.add(board, BorderLayout.CENTER);
        player = beginner;
        if (beginner == 1)
          switchSides(redX, redY, redB, blackX, blackY, blackB);
        else
          switchSides(blackX, blackY, blackB, redX, redY, redB);
        board.revalidate();
        board.repaint();

      }
    });
    /*Saving dialog*/
    saveOption.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        /* Looking for save folder */
        File f = new File("./save");
        if (!f.isDirectory()) {
          boolean success = (new File("save")).mkdirs();
          if (!success){
            JOptionPane.showMessageDialog(null, "There is a problem with ./save folder!",
                                          "Can't create directory", JOptionPane.ERROR_MESSAGE);
            System.exit(1);
          }
        }
        /* Saving */
        String s = JOptionPane.showInputDialog(null, "New save file name");
        if(!s.equals("")){
        s = "./save/" + s;
        File save_file =  new File(s + ".txt");
        if (save_file.exists()) {
          int confButton = JOptionPane.YES_NO_OPTION;
          int confResult = JOptionPane.showConfirmDialog(null, "File " + s +" exists.\n" + "Overwrite it?",
                              "Confirmation", confButton);
          if (confResult == 1)
            return;
          }
        PartC.board_save(board.getBoard(), s);
        }
      }
    });

    /* Load dialog */
    loadOption.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        /* Saving */
        String s = JOptionPane.showInputDialog(null, "Load from file...");
        if (!s.equals("")){
        s = "./save/" + s;

        File load_file =  new File(s + ".txt");
        if (!load_file.exists())
          JOptionPane.showMessageDialog(null, "File " + s + " does not exist",
                                        "Error", JOptionPane.ERROR_MESSAGE);
        else {
          game_over();
          board.loadGame(s);
          player = board.getPlayer();
          if (player == 1)
            switchSides(redX, redY, redB, blackX, blackY, blackB);
          else
            switchSides(blackX, blackY, blackB, redX, redY, redB);
          size = board.getSizeBoard();
          forceResize();

          board.revalidate();
          board.repaint();
        }
      }
      }
    });

    stepBack.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        if (board.stepBack() != -1){
          if (board.getBotColor() != -1);
            board.stepBack();
          player = board.getPlayer();
          if (player == 1)
            switchSides(redX, redY, redB, blackX, blackY, blackB);
          else
          switchSides(blackX, blackY, blackB, redX, redY, redB);
        board.revalidate();
        board.repaint();
        }
      }
    });

    /*Option dialog*/
    settings.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        set.game_setup();
        board.revalidate();
        board.repaint();
      }
    });

    if (beginner == 0)
      switchSides(blackX, blackY, blackB, redX, redY, redB);
    else
      switchSides(redX, redY, redB, blackX, blackY, blackB);
    if (beginner == botColor) {
      if (botColor == 1) {
        int t = PartC.bot_get_turn(board.getBotMinMax(), board.getBoard(), board.getHistory());
        board.playAt(t, 1);
        switchSides(blackX, blackY, blackB, redX, redY, redB);
      }
      else {
        if (board.getBotColor() == 0) {
          int t = PartC.bot_get_turn(board.getBotMinMax(), board.getBoard(), board.getHistory());
          board.playAt(t, 0);
          switchSides(blackX, blackY, blackB, redX, redY, redB);
        }
      }

    }

    /* Adding elements */
    mainPanel.add(redPanel, BorderLayout.WEST);
    mainPanel.add(blackPanel, BorderLayout.EAST);
    mainPanel.add(board, BorderLayout.CENTER);
    f.setJMenuBar(menuBar);
    f.add(mainPanel);
  }


  /* Main process */
  public static void main(String[] args) {
      javax.swing.SwingUtilities.invokeLater(new Runnable() {
        public void run() {
          set.game_setup();
          }});
      }
}
