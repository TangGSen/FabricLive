package cn.fabric.media.camera;

/**
 * 高清模式
 * Created by chendingqiang on 2017/7/16.
 */

public enum BitRateModeType {
    HDMode(0),SmoothMode(1);
    private int value;

    BitRateModeType(int value)
    {
        this.value = value;
    }

    public int getValue()
    {
        return this.value;
    }

}
