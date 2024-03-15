#include "libmp3lame/lame.h"
#include "lame_util.h"
#include <jni.h>

static lame_global_flags *glf = NULL;

JNIEXPORT jint
JNICALL Java_lib_kalu_lamemp3_LameUtil_init(JNIEnv *env, jclass cls, jint in_samplerate, jint num_channels, jint out_samplerat, jint bitrate, jint quality) {
	if (glf != NULL) {
		lame_close(glf);
		glf = NULL;
	}
	glf = lame_init();
	lame_set_in_samplerate(glf, in_samplerate);
	lame_set_num_channels(glf, num_channels);
	lame_set_out_samplerate(glf, out_samplerat);
    //位宽
	lame_set_brate(glf, bitrate);
	lame_set_quality(glf, quality);
	int ret_code = lame_init_params(glf);

	return ret_code;
}

JNIEXPORT jint
JNICALL Java_lib_kalu_lamemp3_LameUtil_encode(JNIEnv *env, jclass cls, jshortArray buffer_l, jshortArray buffer_r, jint samples, jbyteArray mp3buf) {

    if (glf == NULL) {
		glf = lame_init();
	}

    // 双声道
    if (lame_get_num_channels(glf) == 2) {
        jshort* j_buffer_l = (*env)->GetShortArrayElements(env, buffer_l, NULL);
        jshort* j_buffer_r = (*env)->GetShortArrayElements(env, buffer_r, NULL);
        const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf);
        jbyte* j_mp3buf = (*env)->GetByteArrayElements(env, mp3buf, NULL);
        int result = lame_encode_buffer(glf, j_buffer_l, j_buffer_r, samples, j_mp3buf, mp3buf_size);
        (*env)->ReleaseShortArrayElements(env, buffer_l, j_buffer_l, 0);
        (*env)->ReleaseShortArrayElements(env, buffer_r, j_buffer_r, 0);
        (*env)->ReleaseByteArrayElements(env, mp3buf, j_mp3buf, 0);
        return result;
    }
    // 单声道
    else {
        jshort* j_buffer_l = (*env)->GetShortArrayElements(env, buffer_l, NULL);
        const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf);
        jbyte* j_mp3buf = (*env)->GetByteArrayElements(env, mp3buf, NULL);
        int result = lame_encode_buffer(glf, j_buffer_l, j_buffer_l, samples, j_mp3buf, mp3buf_size);
        (*env)->ReleaseShortArrayElements(env, buffer_l, j_buffer_l, 0);
        (*env)->ReleaseByteArrayElements(env, mp3buf, j_mp3buf, 0);
         return result;
    }
}

JNIEXPORT jint
JNICALL Java_lib_kalu_lamemp3_LameUtil_flush(JNIEnv *env, jclass cls, jbyteArray mp3buf) {

    if (glf == NULL) {
		glf = lame_init();
	}

    const jsize mp3buf_size = (*env)->GetArrayLength(env, mp3buf);
	jbyte* j_mp3buf = (*env)->GetByteArrayElements(env, mp3buf, NULL);

    int result = lame_encode_flush(glf, j_mp3buf, mp3buf_size);

	(*env)->ReleaseByteArrayElements(env, mp3buf, j_mp3buf, 0);

	return result;
}

JNIEXPORT void
JNICALL Java_lib_kalu_lamemp3_LameUtil_close(JNIEnv *env, jclass cls) {
    if (glf != NULL) {
		lame_close(glf);
        glf = NULL;
	}
}

JNIEXPORT jstring JNICALL
JNICALL Java_lib_kalu_lamemp3_LameUtil_getVersion(JNIEnv *env, jclass clazz) {
    return (*env)->NewStringUTF(env, get_lame_version());
}

JNIEXPORT void
JNICALL Java_lib_kalu_lamemp3_LameUtil_pcm2mp3(JNIEnv *env, jclass cls, jstring pcm_path, jstring mp3_path, jint sampleRate, jint channels, jint bitrate, jint quality){

    const char *pcmFilePath = (*env)->GetStringUTFChars(env, pcm_path, NULL);
    const char *mp3FilePath = (*env)->GetStringUTFChars(env, mp3_path, NULL);

    FILE *pcmFile;
    if((pcmFile=fopen(pcmFilePath, "rb")) == NULL ){
        return;
    }

    FILE *mp3File;
    if((mp3File=fopen(mp3FilePath, "wb")) == NULL ){
        return;
    }

    if (glf == NULL) {
		glf = lame_init();
	}

    lame_set_in_samplerate(glf, sampleRate);
    lame_set_out_samplerate(glf, sampleRate);
    lame_set_num_channels(glf, channels);
    lame_set_brate(glf, bitrate);
    lame_set_quality(glf, quality);
    lame_init_params(glf);

    // 双声道
    if (lame_get_num_channels(glf) == 2) {
        int bufferSize = 1024 * 256;
        short buffer[bufferSize / 2];
        short leftBuffer[bufferSize / 4];
        short rightBuffer[bufferSize / 4];
        char mp3_buffer[bufferSize];
        size_t readBufferSize = 0;
        while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {
            for (int i = 0; i < readBufferSize; i++) {
                if (i % 2 == 0) {
                    leftBuffer[i / 2] = buffer[i];
                } else {
                    rightBuffer[i / 2] = buffer[i];
                }
            }
            size_t writeSize = lame_encode_buffer(glf, leftBuffer, rightBuffer, (readBufferSize / 2), mp3_buffer, bufferSize);
            int result = lame_encode_flush(glf, mp3_buffer, readBufferSize);
            fwrite(mp3_buffer, 1, writeSize, mp3File);
        }
//
//        free(buffer);
//        free(leftBuffer);
//        free(rightBuffer);
//        free(mp3_buffer);
    }
    // 单声道
    else {
        int bufferSize = 1024 * 256;
        short buffer[bufferSize / 2];
        short leftBuffer[bufferSize / 2];
        char mp3_buffer[bufferSize];
        size_t readBufferSize = 0;
        while ((readBufferSize = fread(buffer, 2, bufferSize / 2, pcmFile)) > 0) {
            for (int i = 0; i < readBufferSize; i++) {
                leftBuffer[i] = buffer[i];
            }
            size_t writeSize = lame_encode_buffer(glf,  leftBuffer, leftBuffer, readBufferSize, mp3_buffer, bufferSize);
            int result = lame_encode_flush(glf, mp3_buffer, readBufferSize);
            fwrite(mp3_buffer, 1, writeSize, mp3File);
        }
//
//        free(buffer);
//        free(leftBuffer);
//        free(mp3_buffer);
    }
}