package cn.fabric.media;

import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.media.audiofx.AcousticEchoCanceler;
import android.util.Log;
import android.widget.Toast;

/**
 * Created by blueberry on 3/6/2017.
 * <p>
 * 音频采集
 */

public class AudioGatherer {

    private static final String TAG = "AudioGatherer";

    private Config mConfig;

    private AudioRecord mAudioRecord;
    private byte[] buffer;
    private Thread workThread;
    private boolean loop;
    private Callback mCallback;
    AcousticEchoCanceler aecSwith;


    public static AudioGatherer newInstance(Config config) {

        return new AudioGatherer(config);

    }
    private AudioGatherer(Config config){
        this.mConfig =config;
    }

    public static class Params {
        public final int sampleRate;
        public final int channelCount;

        public Params(int sampleRate, int channelCount) {
            this.sampleRate = sampleRate;
            this.channelCount = channelCount;
        }
    }

    /**
     * 初始化录音
     */
    public Params initAudioDevice() {
        int[] sampleRates = {44100};
        for (int sampleRate :  sampleRates) {
            //编码制式
            int audioFormat = mConfig.audioFormat;
            // stereo 立体声，
            int channelConfig = mConfig.channelConfig;
            int buffsize = 2 * AudioRecord.getMinBufferSize(sampleRate, channelConfig, audioFormat);
            mAudioRecord = new AudioRecord(MediaRecorder.AudioSource.MIC, sampleRate, channelConfig,
                    audioFormat, buffsize);
            if (mAudioRecord.getState() != AudioRecord.STATE_INITIALIZED) {
                continue;
            }
            this.buffer = new byte[Math.min(4096, buffsize)];

            return new Params(sampleRate,
                    channelConfig == AudioFormat.CHANNEL_CONFIGURATION_STEREO ? 2 : 1);
        }

        return null;
    }

    /**
     * 初始化语言消除
     * @param audioSession
     */
    public void initAEC( int audioSession){
        if(AcousticEchoCanceler.isAvailable())
        {
            Log.i(TAG,"不能做回音消除===========");
            return ;
        }else
        {
            Log.i(TAG,"支持回音消除==========="+audioSession);
        }
        if(aecSwith != null)
        {
            return ;
        }
        aecSwith = AcousticEchoCanceler.create(audioSession);
        if(aecSwith!=null)
        {
            Log.i(TAG,"创建成果了哦===========");
            aecSwith.setEnabled(true);
        }else
        {
            Log.i(TAG,"创建失败了哦===========");
        }

    }

    /**
     * 开始录音
     */
    public void start() {
        workThread = new Thread() {
            @Override
            public void run() {

                mAudioRecord.startRecording();
                int sessionId = mAudioRecord.getAudioSessionId();

                Log.i(TAG,"sessionId = "+sessionId);
                initAEC(sessionId);
                while (loop && !Thread.interrupted()) {
                    int size = mAudioRecord.read(buffer, 0, buffer.length);
                    if (size < 0) {
                        Log.i(TAG, "audio ignore ,no data to read");
                        break;
                    }
                    if (loop) {



                        byte[] audio = new byte[size];
                        System.arraycopy(buffer, 0, audio, 0, size);

                        if (mCallback != null) {
                            mCallback.audioData(audio);
                        }
                    }
                }

            }
        };

        loop = true;
        workThread.start();
    }

    public void stop() {
        loop = false;
        workThread.interrupt();
        Log.i(TAG, "run: 调用stop");
        mAudioRecord.stop();
    }


    public void release() {

        mAudioRecord.release();
        if( null != aecSwith){
            aecSwith.setEnabled(false);
            aecSwith.release();
        }

    }

    public void setCallback(Callback callback) {
        this.mCallback = callback;
    }

    public interface Callback {
        void audioData(byte[] data);
    }
}
