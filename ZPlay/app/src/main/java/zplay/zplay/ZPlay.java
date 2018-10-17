package zplay.zplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

public class ZPlay extends GLSurfaceView implements SurfaceHolder.Callback {
    public ZPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

   @Override
    public void surfaceCreated(SurfaceHolder holder)
   {
       //初始化opengl egl显示
       InitView(holder.getSurface());

   }

    @Override
    public void surfaceDestroyed(SurfaceHolder holder)
    {

    }

    @Override
    public void surfaceChanged(SurfaceHolder holder, int format, int width,
                               int height)
    {

    }

    public native void InitView(Object surface);




}
