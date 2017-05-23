public class PartC {

  static {
    System.loadLibrary("partc");
  }

  /* Board aka playgraond sector */
  public static native long new_board(int size, int mod);
  public static native void board_dispose(long board);
  public static native int board_get_case(long board, int pos);
  public static native void board_set_case(long board, int pos, int player, long history, long player_graph);
  public static native void board_set_player(long board, int player);
  public static native int board_get_player(long board);
  public static native int board_get_size(long board);
  public static native int board_getBotColor(long board);
  public static native int [] board_import(long board);
  public static native void board_save(long board, String s);
  public static native long board_load(String s, long redGr, long blackGr);

  /* Graph sector */
  public static native long new_graph();
  public static native void graph_dispose(long graph);
  public static native void graph_restore(long graph, long board, int player);
  public static native boolean red_wins(long graph, long board);
  public static native boolean black_wins(long graph, long board);

  /* History sector */
  public static native long new_history();
  public static native void history_add_turn(long history, int num, int pos);
  public static native int history_step_back(long history, long board, long redGr, long blackGr);
  public static native void history_clear(long history);
  public static native void history_dispose(long board);

  /* AI sector */
  public static native long new_minimax(long board, long grPl, long grAI);
  public static native void minimax_dispose(long minimax);
  public static native int bot_get_turn(long minimax, long board, long history);
}
