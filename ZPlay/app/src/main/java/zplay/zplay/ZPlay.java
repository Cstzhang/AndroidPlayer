package zplay.zplay;

import android.content.Context;
import android.opengl.GLSurfaceView;
import android.util.AttributeSet;
import android.view.SurfaceHolder;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

public class ZPlay extends GLSurfaceView implements SurfaceHolder.Callback,GLSurfaceView.Renderer {
    public ZPlay(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

   @Override
    public void surfaceCreated(SurfaceHolder holder)
   {
       //初始化opengl egl显示
       InitView(holder.getSurface());

       //Android 8.0 需要
       setRenderer(this);

       //只有在绘制数据改变时才绘制view，可以防止GLSurfaceView帧重绘
       //setRenderMode(GLSurfaceView.RENDERMODE_WHEN_DIRTY);

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

    @Override
    public void onSurfaceCreated(GL10 gl, EGLConfig config)
    {

    }

    @Override
    public void onSurfaceChanged(GL10 gl, int width, int height){

    }
    @Override
    public void onDrawFrame(GL10 gl)
    {

    }


}
