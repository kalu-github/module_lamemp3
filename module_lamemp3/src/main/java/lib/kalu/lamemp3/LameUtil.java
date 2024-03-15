
package lib.kalu.lamemp3;

public final class LameUtil {

    static {
        System.loadLibrary("lamemp3");
    }

    /**
     * @param inputSampleRate   采样率 -- 录音默认44100
     * @param inputChannelCount 通道数 -- 录音默认双通道2
     * @param outputSampleRate  采样率 -- 录音默认44100
     * @param outputBitrate     码率 -- 采样率 × 采样位数 × 声道数
     * @param quality           MP3音频质量 0~9 其中0是最好，非常慢，9是最差  2=high(高)  5 = medium(中)  7=low(低)
     * @return
     */
    public native static int init(int inputSampleRate, int inputChannelCount, int outputSampleRate, int outputBitrate, int quality);

    /**
     * 启用lame编码
     *
     * @param pcmBuf       ：音频数据源
     * @param mp3BufOutput ：写入MP3数据buffer
     * @param samplesNum   ：采样个数
     */
    public static int encode(short[] pcmBuf, int samplesNum, byte[] mp3BufOutput) {
        return encode(pcmBuf, pcmBuf, samplesNum, mp3BufOutput);
    }

    /**
     * 启用lame编码
     *
     * @param pcmBufL      ：音频数据源
     * @param pcmBufR      ：音频数据源
     * @param mp3BufOutput ：写入MP3数据buffer
     * @param samplesNum   ：采样个数
     */
    public native static int encode(short[] pcmBufL, short[] pcmBufR, int samplesNum, byte[] mp3BufOutput);

    /**
     * 刷新缓冲器
     *
     * @param outputBuf ：MP3编码buffer
     * @return int 返回剩余编码器字节数据,需要写入文件
     */
    public native static int flush(byte[] outputBuf);

    public native static void close();

    public native static String getVersion();

    public native static void pcm2mp3(String pcmPath, String mp3Path, int inSampleRate, int num_channels, int bitrate, int quality);
//    public native static void pcm2wav(String inputPath, String mp3Path, int inSampleRate, int channels);
}
