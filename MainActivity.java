package root.medfordclock;

import android.app.*;
import android.content.*;
import android.os.*;
import android.view.*;
import android.widget.*;

import java.util.concurrent.ExecutionException;

import static root.medfordclock.Util.DialogLayout;
import static root.medfordclock.Util.Request;
import static root.medfordclock.Util.handleOnClick;

public class MainActivity extends Activity {

    SeekBar red;
    SeekBar green;
    SeekBar blue;
    int redColor;
    int blueColor;
    int greenColor;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        SharedPreferences onRun = getSharedPreferences("onRun", Context.MODE_PRIVATE);
        SharedPreferences.Editor onRunEditor = onRun.edit();

        if (onRun.getBoolean("firstRun", false)) {
            AsyncTaskDialog message_dialog = new AsyncTaskDialog("https://pastebin.com/raw/GsGK1xcb", MainActivity.this);
            message_dialog.execute();

            onRunEditor.putBoolean("firstRun", true);
            onRunEditor.apply();
        }

        AsyncTaskChangelog changelog = new AsyncTaskChangelog("https://pastebin.com/raw/GsGK1xcb", MainActivity.this);
        changelog.execute();

        red = (SeekBar) findViewById(R.id.red);
        green = (SeekBar) findViewById(R.id.green);
        blue = (SeekBar) findViewById(R.id.blue);

        red.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChangedValue = 0;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChangedValue = progress;
            }
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            public void onStopTrackingTouch(SeekBar seekBar) {
                redColor = progressChangedValue;
            }
        });

        green.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChangedValue = 0;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChangedValue = progress;
            }
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            public void onStopTrackingTouch(SeekBar seekBar) {
                greenColor = progressChangedValue;
            }
        });

        blue.setOnSeekBarChangeListener(new SeekBar.OnSeekBarChangeListener() {
            int progressChangedValue = 0;
            public void onProgressChanged(SeekBar seekBar, int progress, boolean fromUser) {
                progressChangedValue = progress;
            }
            public void onStartTrackingTouch(SeekBar seekBar) {
            }
            public void onStopTrackingTouch(SeekBar seekBar) {
                blueColor = progressChangedValue;
            }
        });

        LinearLayout parentLayout = (LinearLayout)findViewById(R.id.ParentLayout);
        AsyncTaskGetUrlContents getContents = new AsyncTaskGetUrlContents("https://pastebin.com/raw/HEuSpczs");

        String features = null;
        try {
            features = getContents.execute().get();
        } catch (InterruptedException | ExecutionException e) {
            e.printStackTrace();
        }

        String[] button = features.split("--");

        LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT);

        for(int i = 0; i < button.length; i++){
            String[] buttonTextAndParams = button[i].split("::");
            Button btn = new Button(this);
            btn.setLayoutParams(params);
            btn.setGravity(Gravity.CENTER);
            btn.setText(buttonTextAndParams[0]);
            btn.setPadding(20, 20, 20, 20);
            parentLayout.addView(btn);
            btn.setOnClickListener(handleOnClick(buttonTextAndParams[1], this));
        }
    }

    public void rgb(View v) {
        Request("redslide" + String.valueOf(redColor));
        Request("greenslide" + String.valueOf(greenColor));
        Request("blueslide" + String.valueOf(blueColor));
    }

    public void setGradient(View v) {
        DialogLayout(this);
    }

    public void reset(View v) {
        Request("reset");
    }
}
