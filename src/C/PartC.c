#include "PartC.h"
#include "board.h"  //Board & math
#include "graph.h"  //Graph + method for AI
#include "I_A.h"    //AI
#include "menu.h"   //History

/* Board aka playgraond sector */
JNIEXPORT jlong JNICALL Java_PartC_new_1board (JNIEnv * env, jclass cl, jint size, jint botColor) {
  return (long) new_board(size, botColor);
}

JNIEXPORT void JNICALL Java_PartC_board_1dispose(JNIEnv *env, jclass cl, jlong b){
  board_delete((board) b);
}

JNIEXPORT jint JNICALL Java_PartC_board_1get_1case(JNIEnv * env, jclass cl, jlong b, jint pos) {
  return get_case((board) b, pos);
}

JNIEXPORT void JNICALL Java_PartC_board_1set_1case(JNIEnv * env, jclass cl, jlong b, jint pos,
                                                    jint player, jlong history, jlong player_graph) {
  set_case((board) b, pos, player);
  graph_add_vertice((Graph) player_graph, pos, board_get_size((board) b));
  history_add_turn((List) history, list_size((List) history) + 1, pos);
  next_player((board) b);
}

JNIEXPORT void JNICALL Java_PartC_board_1set_1player(JNIEnv *env, jclass cl, jlong b, jint player){
  set_player((board) b, player);
}

JNIEXPORT jint JNICALL Java_PartC_board_1get_1player(JNIEnv *env, jclass cl, jlong b){
  return get_player((board) b);
}

JNIEXPORT jint JNICALL Java_PartC_board_1get_1size(JNIEnv *env, jclass cl, jlong b){
    return board_get_size((board) b);
}

JNIEXPORT jint JNICALL Java_PartC_board_1getBotColor(JNIEnv *env, jclass cl, jlong b) {
  return get_bot_color((board) b);
}

JNIEXPORT jintArray JNICALL Java_PartC_board_1import(JNIEnv *env, jclass cl, jlong b) {
  int * brd = get_board((board) b);
  int size = board_get_size((board) b);

  /*Creating new Java array and temporal analog */
  jintArray newJavaArray = (*env)->NewIntArray(env, size*size);
	jint *inCArray = (*env)->GetIntArrayElements(env, newJavaArray, NULL);
  /* Copying values */
  for(int i = 0; i < size*size; i++)
    inCArray[i] = brd[i];
  /* Returning int array */
  (*env)->ReleaseIntArrayElements(env, newJavaArray, inCArray, 0);
	return newJavaArray;
}

JNIEXPORT void JNICALL Java_PartC_board_1save(JNIEnv * env, jclass cl, jlong b, jstring file) {
  const char *s = (*env)->GetStringUTFChars(env,file, 0);
  char *res = (char*) malloc(strlen(s) + 1);
  strcpy(res, s);
  board pb = (board) b;
  board_to_file(&pb, res);
  free(res);
}

JNIEXPORT jlong JNICALL Java_PartC_board_1load(JNIEnv * env, jclass cl, jstring file, jlong redG, jlong blackG) {
    const char *s = (*env)->GetStringUTFChars(env,file, 0);
    char *res = (char*) malloc(strlen(s) + 1);
    strcpy(res, s);
    board p = board_from_file_JAVA(res);
    board_to_graph_by_player(p, (Graph) redG, RED);
    board_to_graph_by_player(p, (Graph) blackG, BLACK);
    return (long) (p);
}

  /* Graph sector */
  JNIEXPORT jlong JNICALL Java_PartC_new_1graph(JNIEnv * env, jclass cl) {
    return (long) new_graph();
  }

  JNIEXPORT void JNICALL Java_PartC_graph_1dispose(JNIEnv * env, jclass cl, jlong graph) {
    graph_delete((Graph) graph);
  }

  JNIEXPORT void JNICALL Java_PartC_graph_1restore(JNIEnv *env, jclass cl, jlong g, jlong b, jint player) {

    board_to_graph_by_player((board) b, (Graph) g, player);
  }

  JNIEXPORT jboolean JNICALL Java_PartC_red_1wins(JNIEnv * env, jclass cl, jlong redG, jlong b) {
    return is_red_winner((Graph) redG, board_get_size((board)  b));
  }

  JNIEXPORT jboolean JNICALL Java_PartC_black_1wins(JNIEnv * env, jclass cl, jlong blackG, jlong b) {
    return is_black_winner((Graph) blackG, board_get_size((board) b));
  }

  /* History sector */
  JNIEXPORT jlong JNICALL Java_PartC_new_1history(JNIEnv * env, jclass cl) {
    return (long) new_list();
  }

  JNIEXPORT void JNICALL Java_PartC_history_1add_1turn(JNIEnv * env, jclass cl, jlong history, jint num, jint pos) {
    history_add_turn((List) history, num, pos);
  }

  JNIEXPORT int JNICALL Java_PartC_history_1step_1back(JNIEnv * env, jclass cl, jlong history,
                                                        jlong b, jlong redG, jlong blackG) {
    int pos = history_step_back((List) history, (board) b);
    if (get_player((board) b) == RED)
      graph_remove_vertice((Graph) redG, pos);
    else
      graph_remove_vertice((Graph) blackG, pos);
    return pos;
  }

  JNIEXPORT void JNICALL Java_PartC_history_1clear(JNIEnv * env, jclass cl, jlong history){
    history_clear((List) history);
  }

  JNIEXPORT void JNICALL Java_PartC_history_1dispose(JNIEnv * env, jclass cl, jlong h) {
    history_delete((List) h);
  }

  JNIEXPORT jlong JNICALL Java_PartC_new_1minimax(JNIEnv * env, jclass cl,
                                                  jlong b, jlong grPl, jlong grAI) {
      int s = board_get_size((board) b);
      MinMax t = new_minmax((board) b, s*s, (Graph) grPl, (Graph) grAI, s);
      return (long) t;
  }

  JNIEXPORT void JNICALL Java_PartC_minimax_1dispose(JNIEnv * env, jclass cl, jlong m) {
    minmax_delete((MinMax) m);
  }

  JNIEXPORT jint JNICALL Java_PartC_bot_1get_1turn(JNIEnv * env, jclass cl, jlong m, jlong b, jlong hist) {
    return IA_Jouer((MinMax) m, board_get_size((board) b)* board_get_size((board) b) - list_size((List) hist));
  }
