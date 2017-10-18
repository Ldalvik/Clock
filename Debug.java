package root.medfordclock;

import android.content.Context;
import android.widget.Toast;

/**
 * Created by student on 10/16/2017.
 */

public class Debug {

    private static boolean isDebug = false;

    public static void debug(String text, Context c) {
        if(isDebug) {
            Toast.makeText(c, "(DEBUG): " + text, Toast.LENGTH_SHORT).show();
        }
    }
}
