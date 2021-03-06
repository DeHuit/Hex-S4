/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class PartC */

#ifndef _Included_PartC
#define _Included_PartC
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     PartC
 * Method:    new_board
 * Signature: (II)J
 */
JNIEXPORT jlong JNICALL Java_PartC_new_1board
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     PartC
 * Method:    board_dispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_PartC_board_1dispose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    board_get_case
 * Signature: (JI)I
 */
JNIEXPORT jint JNICALL Java_PartC_board_1get_1case
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     PartC
 * Method:    board_set_case
 * Signature: (JIIJJ)V
 */
JNIEXPORT void JNICALL Java_PartC_board_1set_1case
  (JNIEnv *, jclass, jlong, jint, jint, jlong, jlong);

/*
 * Class:     PartC
 * Method:    board_set_player
 * Signature: (JI)V
 */
JNIEXPORT void JNICALL Java_PartC_board_1set_1player
  (JNIEnv *, jclass, jlong, jint);

/*
 * Class:     PartC
 * Method:    board_get_player
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PartC_board_1get_1player
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    board_get_size
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PartC_board_1get_1size
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    board_getBotColor
 * Signature: (J)I
 */
JNIEXPORT jint JNICALL Java_PartC_board_1getBotColor
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    board_import
 * Signature: (J)[I
 */
JNIEXPORT jintArray JNICALL Java_PartC_board_1import
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    board_save
 * Signature: (JLjava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_PartC_board_1save
  (JNIEnv *, jclass, jlong, jstring);

/*
 * Class:     PartC
 * Method:    board_load
 * Signature: (Ljava/lang/String;JJ)J
 */
JNIEXPORT jlong JNICALL Java_PartC_board_1load
  (JNIEnv *, jclass, jstring, jlong, jlong);

/*
 * Class:     PartC
 * Method:    new_graph
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_PartC_new_1graph
  (JNIEnv *, jclass);

/*
 * Class:     PartC
 * Method:    graph_dispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_PartC_graph_1dispose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    graph_restore
 * Signature: (JJI)V
 */
JNIEXPORT void JNICALL Java_PartC_graph_1restore
  (JNIEnv *, jclass, jlong, jlong, jint);

/*
 * Class:     PartC
 * Method:    red_wins
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_PartC_red_1wins
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     PartC
 * Method:    black_wins
 * Signature: (JJ)Z
 */
JNIEXPORT jboolean JNICALL Java_PartC_black_1wins
  (JNIEnv *, jclass, jlong, jlong);

/*
 * Class:     PartC
 * Method:    new_history
 * Signature: ()J
 */
JNIEXPORT jlong JNICALL Java_PartC_new_1history
  (JNIEnv *, jclass);

/*
 * Class:     PartC
 * Method:    history_add_turn
 * Signature: (JII)V
 */
JNIEXPORT void JNICALL Java_PartC_history_1add_1turn
  (JNIEnv *, jclass, jlong, jint, jint);

/*
 * Class:     PartC
 * Method:    history_step_back
 * Signature: (JJJJ)I
 */
JNIEXPORT jint JNICALL Java_PartC_history_1step_1back
  (JNIEnv *, jclass, jlong, jlong, jlong, jlong);

/*
 * Class:     PartC
 * Method:    history_clear
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_PartC_history_1clear
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    history_dispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_PartC_history_1dispose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    new_minimax
 * Signature: (JJJ)J
 */
JNIEXPORT jlong JNICALL Java_PartC_new_1minimax
  (JNIEnv *, jclass, jlong, jlong, jlong);

/*
 * Class:     PartC
 * Method:    minimax_dispose
 * Signature: (J)V
 */
JNIEXPORT void JNICALL Java_PartC_minimax_1dispose
  (JNIEnv *, jclass, jlong);

/*
 * Class:     PartC
 * Method:    bot_get_turn
 * Signature: (JJJ)I
 */
JNIEXPORT jint JNICALL Java_PartC_bot_1get_1turn
  (JNIEnv *, jclass, jlong, jlong, jlong);

#ifdef __cplusplus
}
#endif
#endif
