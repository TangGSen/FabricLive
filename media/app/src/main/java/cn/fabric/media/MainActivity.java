package cn.fabric.media;

import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.Button;

import cn.fabric.media.camera.BitRateModeType;


public class MainActivity extends AppCompatActivity implements SurfaceHolder.Callback2 {

    private static final String TAG = "MainActivity";

    private SurfaceView mSurfaceView;

    private SurfaceHolder mSurfaceHolder;
    private boolean isPublished;

    private MediaPublisher mMediaPublisher;

    private int cameraId;
    private String rtmpUrl;
    private int mode;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(cn.fabric.media.R.layout.activity_main);
        Log.i(TAG, "onCreate: ");
        initView();

        Bundle bundle = this.getIntent().getExtras();
        rtmpUrl = bundle.getString("rtmpUrl");
        cameraId = bundle.getInt("cameraId");
        mode = bundle.getInt("mode");

        Log.i(TAG,"rtmpUrl:"+rtmpUrl);
        Config.Builder builder = new Config.Builder()
                .setFps(30) // fps
                .setMaxWidth(720) //视频的最大宽度
                .setMinWidth(320) //视频的最小宽度
                .setUrl(rtmpUrl);//推送的url
        if(mode == BitRateModeType.HDMode.getValue())
        {
            builder.setHdBitrate();
        }else
        {
            builder.setSmoothBitrate();
        }
        mMediaPublisher = MediaPublisher.newInstance(builder.build());
        mMediaPublisher.init();
        start();
    }

    private void initView() {
        mSurfaceView = (SurfaceView) findViewById(cn.fabric.media.R.id.surface_view);
        mSurfaceView.setKeepScreenOn(true);
        mSurfaceHolder = mSurfaceView.getHolder();
        mSurfaceHolder.addCallback(this);


    }



    private void start() {

        mMediaPublisher.initVideoGatherer(this, mSurfaceHolder,cameraId);
        //初始化声音采集
        mMediaPublisher.initAudioGatherer();
        //初始化编码器
        mMediaPublisher.initEncoders();
        //开始采集
        mMediaPublisher.startGather();
        //开始编码
        mMediaPublisher.startEncoder();
        //开始推送
        mMediaPublisher.starPublish();
        isPublished = true;
    }

    @Override
    protected void onResume() {
        super.onResume();
        Log.i(TAG, "onResume: ");
        mMediaPublisher.initVideoGatherer(this, mSurfaceHolder,cameraId);


    }

    @Override
    protected void onPause() {
        super.onPause();
        Log.i(TAG, "onPause: ");
        stop();
    }

    private void stop() {
        mMediaPublisher.stopPublish();
        mMediaPublisher.stopGather();
        mMediaPublisher.stopEncoder();
        isPublished = false;
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        mMediaPublisher.release();
    }

    @Override
    public void surfaceRedrawNeeded(SurfaceHolder holder) {

    }

    @Override
    public void surfaceCreated(SurfaceHolder holder) {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {
        Log.i(TAG, "surfaceChanged: ");
        mMediaPublisher.initVideoGatherer(MainActivity.this, holder,cameraId);
    }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder) {

    }

}
