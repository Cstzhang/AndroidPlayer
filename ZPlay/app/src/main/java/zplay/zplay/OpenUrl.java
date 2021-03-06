package zplay.zplay;

import android.content.pm.ActivityInfo;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import static zplay.zplay.PermisionUtils.verifyStoragePermissions;

public class OpenUrl extends AppCompatActivity {
    private Button btfile;
    private Button btrtmp;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        setContentView(R.layout.openurl);
        btfile = findViewById( R.id.playvideo );
        btfile.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        EditText t = findViewById( R.id.fileurl );
                        //用户输入的URL，打开视频
                        Open(t.getText().toString());
                        //关闭当前窗口
                        finish();
                    }
                }
        );


        btrtmp = findViewById( R.id.playrtmp );
        btrtmp.setOnClickListener(
                new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        EditText t = findViewById( R.id.rtmpurl );
                        //用户输入的URL，打开视频
                        Open(t.getText().toString());

                        //关闭当前窗口
                        finish();
                    }
                }
        );



    }
    public native void Open(String url);
}
