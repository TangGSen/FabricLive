package com.fabric.live;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.content.Intent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.Toast;

import cn.fabric.media.camera.BitRateModeType;
import cn.fabric.media.camera.CameraType;

public class CameraStartActivity extends AppCompatActivity {
    /**
     * 前置镜头
     */
    Button btnPreCamera;
    /**
     * 后置镜头
     */
    Button btnAfterCamera;

    /**
     * 推流地址
     */
    private EditText rtmpUrl;

    /**
     * 清晰模式
     */
    private RadioGroup radioGroupMode;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(com.fabric.live.R.layout.activity_camerastart);
        initView();
        final Intent intent = new Intent(CameraStartActivity.this, CameraActivity.class);

        btnPreCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startIntent(intent,CameraType.PRE_CAMERA.getValue());
            }
        });

        btnAfterCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                startIntent(intent,CameraType.AFTER_CAMERA.getValue());
            }
        });

    }

    private void startIntent(Intent intent,int cameraType)
    {
        Bundle bundle=new Bundle();
        String url = rtmpUrl.getText().toString();
        RadioButton radioButton = (RadioButton)findViewById(radioGroupMode.getCheckedRadioButtonId());
        String mode = radioButton.getText().toString();


        if(validateUrl(url))
        {
            bundle.putString("rtmpUrl",url);
            bundle.putInt("cameraId", cameraType);
            if (mode.equals("高清")){
                bundle.putInt("mode", BitRateModeType.HDMode.getValue());
            }else
            {
                bundle.putInt("mode", BitRateModeType.SmoothMode.getValue());
            }
            intent.putExtras(bundle);
            startActivity(intent);

        }
    }

    private boolean validateUrl(String url)
    {
        if(null == url|| "".equals(url))
        {
            Toast.makeText(CameraStartActivity.this,"推流地址不能为空",Toast.LENGTH_SHORT).show();
            return false;
        }else
        {
            return true;
        }
    }

    private void initView()
    {
        btnPreCamera = (Button)findViewById(R.id.btnPreCamera);
        btnAfterCamera = (Button)findViewById(R.id.btnAfterCamera);
        rtmpUrl = (EditText)findViewById(R.id.rtmpUrl);
        radioGroupMode = (RadioGroup)findViewById(R.id.radioGroupMode);
    }

}
