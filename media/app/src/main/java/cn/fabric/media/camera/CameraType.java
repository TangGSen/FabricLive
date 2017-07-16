package cn.fabric.media.camera;

/**
 * 摄像头类型
 * Created by chendingqiang on 2017/7/16.
 */

public enum CameraType {
    AFTER_CAMERA(0),PRE_CAMERA(1);
    private int value;

    CameraType(int value)
    {
        this.value = value;
    }

    public int getValue()
    {
        return this.value;
    }

}
