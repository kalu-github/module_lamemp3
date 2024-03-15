#include <jni.h>
#ifndef _Included_lib_kalu_lamemp3_LameUtil
#define _Included_lib_kalu_lamemp3_LameUtil
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Signature: (IIIII)I
 */
JNIEXPORT jint JNICALL Java_lib_kalu_lamemp3_LameUtil_init
  (JNIEnv *, jclass, jint, jint, jint, jint, jint);

/*
 * Signature: ([S[SI[B)I
 */
JNIEXPORT jint JNICALL Java_lib_kalu_lamemp3_LameUtil_encode
  (JNIEnv *, jclass, jshortArray, jshortArray, jint, jbyteArray);

/*
 * Signature: ([B)I
 */
JNIEXPORT jint JNICALL Java_lib_kalu_lamemp3_LameUtil_flush
  (JNIEnv *, jclass, jbyteArray);

/*
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_lib_kalu_lamemp3_LameUtil_close
  (JNIEnv *, jclass);

/*
 * Signature: ()Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_lib_kalu_lamemp3_LameUtil_getVersion
  (JNIEnv *, jclass);

/*
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_lib_kalu_lamemp3_LameUtil_pcm2mp3
  (JNIEnv *, jclass, jstring, jstring, jint, jint, jint, jint);

#ifdef __cplusplus
}
#endif
#endif
