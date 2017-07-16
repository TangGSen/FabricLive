package cn.fabric.media;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import android.content.Intent;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import cn.fabric.media.camera.CameraType;

public class StartActivity extends AppCompatActivity {
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

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(cn.fabric.media.R.layout.activity_start);
        initView();
        final Intent intent = new Intent(StartActivity.this,MainActivity.class);
        final Bundle bundle=new Bundle();

        btnPreCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = rtmpUrl.getText().toString();

                if(validateUrl(url))
                {
                    bundle.putString("rtmpUrl",url);
                    bundle.putInt("cameraId", CameraType.PRE_CAMERA.getValue());
                    intent.putExtras(bundle);
                    startActivity(intent);
                }

            }
        });

        btnAfterCamera.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = rtmpUrl.getText().toString();

                if(validateUrl(url))
                {
                    bundle.putString("rtmpUrl",url);
                    bundle.putInt("cameraId", CameraType.AFTER_CAMERA.getValue());
                    intent.putExtras(bundle);
                    startActivity(intent);
                }
            }
        });

    }

    private boolean validateUrl(String url)
    {
        if(null == url|| "".equals(url))
        {
            Toast.makeText(StartActivity.this,"推流地址不能为空",Toast.LENGTH_SHORT).show();
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
    }

}
