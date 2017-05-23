import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class SettingsWindow extends JPanel {
  private static MainWindow gameFrame = null;

  private static JFrame body;
  private static JPanel global = new JPanel();
  private static JPanel sizePanel = new JPanel();
  private static JPanel playerPanel = new JPanel();
  private static JPanel botColorPanel = new JPanel();
  private static JPanel modPanel = new JPanel();
  private static ButtonGroup modGroup = new ButtonGroup();
  private static JRadioButton pvp = new JRadioButton("pvp");
  private static JRadioButton pve = new JRadioButton("pve");
  private static JTextField sizeField = new JTextField(2);
  private static ButtonGroup begGroup = new ButtonGroup();
  private static JRadioButton red = new JRadioButton("Red");
  private static JRadioButton black = new JRadioButton("Black");
  private static ButtonGroup botColorGroup = new ButtonGroup();
  private static JRadioButton redB = new JRadioButton("Red");
  private static JRadioButton blackB = new JRadioButton("Black");
  private static JButton confirm = new JButton("OK");

  private static int size = 7;
  private static int beginner = 1;
  private static int botColor = -1;

  public SettingsWindow() {
    //Empty SettingsWindow
  }

  public SettingsWindow(int s, int beg, int botC) {
    size = s;
    beginner = beg;
    botColor = botC;
  }

  public static int getSizeSettings() {
    return size;
  }

  public static int getBeginnerSettings(){
    return beginner;
  }

  public static int getBotColorSettings() {
    return botColor;
  }

  private static void initInputForm(JTextField a) {
    a.addKeyListener(new KeyAdapter() {
      public void keyTyped(KeyEvent e) {
        if (a.getText().length() > 1 )// limit textfield to 2 characters
            e.consume();
      }
      });
  }

  public static void game_setup() {
    /* Craeting new frame */
    body = new JFrame("Settings");

    /* Frame settings */
    body.setVisible(true);
    body.setSize(new Dimension(300, 300));
    body.setResizable(false);
    body.setLocationRelativeTo(null);
    body.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    body.add(global);

    /*Main container*/
    global.add(modPanel);
    global.add(playerPanel);
    global.add(sizePanel);
    global.add(botColorPanel);
    global.add(confirm); //"Confirm" button
    global.setLayout(new BoxLayout(global, BoxLayout.PAGE_AXIS));

    /* Setting up pannels */
    modPanel.setBorder(BorderFactory.createTitledBorder("Game mod"));
    playerPanel.setBorder(BorderFactory.createTitledBorder("Beginner"));
    sizePanel.setBorder(BorderFactory.createTitledBorder("Board size"));
    botColorPanel.setBorder(BorderFactory.createTitledBorder("AI color"));
    modPanel.add(pvp);
    modPanel.add(pve);
    playerPanel.add(red);
    playerPanel.add(black);
    botColorPanel.add(redB);
    botColorPanel.add(blackB);
    sizePanel.add(sizeField);

    /* Radio buttons by groups */
    modGroup.add(pvp);
    modGroup.add(pve);
    begGroup.add(red);
    begGroup.add(black);
    botColorGroup.add(redB);
    botColorGroup.add(blackB);

    /* Activating radio buttons */
    pvp.setSelected(true);
    red.setSelected(true);
    redB.setSelected(true);
    redB.setEnabled(false);
    blackB.setEnabled(false);

    /* Initialising input form */
    initInputForm(sizeField);
    sizeField.setText("7");

    /* Action: Listeners */
    /* Ok = save settings */
    confirm.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        boolean redBeg = red.isSelected();
        boolean modPvp = pvp.isSelected();
        boolean colorBRed = redB.isSelected();
        String strSize = sizeField.getText();
        int sizeA = Integer.parseInt(strSize);
        if (sizeA <= 1 || sizeA >= 50){
          JOptionPane.showMessageDialog(null, "Your size is unplayable! (recommended: 7) ",
          "Wrong size", JOptionPane.ERROR_MESSAGE);
        }
        else { /*Configuration saves only if settings are correct*/
          size = sizeA;
          beginner = (redBeg)?1:0;
          botColor = (modPvp)?-1:(colorBRed)?1:0;
          //Garbage collector will take care of it, beaucause there is no more link on this object
          if (gameFrame != null){
            int confButton = JOptionPane.YES_NO_OPTION;
            int confResult = JOptionPane.showConfirmDialog(null, "Your progress will be erased.\n Are you sure? ",
                                "Confirmation", confButton);
            if (confResult == 1)
              return;
            gameFrame.dispose();
            gameFrame = null;
          }

          gameFrame = new MainWindow(beginner, size, botColor, new SettingsWindow(size, beginner,botColor));
          gameFrame.createGUI();
          body.setVisible(false); //you can't see me!
          body.dispose(); //Destroy the JFrame object
        }
      }
    });

    /* pvp selected -> open bot color choice  */
    pve.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        if (pve.isSelected()) {
          redB.setEnabled(true);
          blackB.setEnabled(true);
        }
        else {
          redB.setEnabled(false);
          blackB.setEnabled(false);
        }
      }
    });
    /* pvp selected -> no more bot color option  */
    pvp.addActionListener(new ActionListener() {
      public void actionPerformed(ActionEvent event) {
        if (pvp.isSelected()) {
          redB.setEnabled(false);
          blackB.setEnabled(false);
        }
      }
    });

  }


}
