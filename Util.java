package root.medfordclock;
 import android.app.*;
 import android.content.*;
 import android.view.View;
 import android.widget.Button;
 import android.widget.SeekBar;

 import static root.medfordclock.Debug.debug;

public class Util {

    private static String responseStart;
    private static String responseEnd;

    private static String r;
    private static String g;
    private static String b;
    private static String rfrac;
    private static String gfrac;
    private static String bfrac;
    private static int color;


    public static void DialogLayout(final Context c) {
        final String[] choices = new String[]{"None", "Red->Green", "Red->Blue", "Green->Red", "Green->Blue", "Blue->Red", "Blue->Green"};
        final AlertDialog.Builder dialog = new AlertDialog.Builder(c);
        dialog.setInverseBackgroundForced(true);
        dialog.setTitle("Pick start and end gradient");
        dialog.setSingleChoiceItems(choices, 0, new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                if (which == 0) {
                    debug("Choice: " + choices[which], c);
                }
                if (which == 1) {
                    responseStart = "red";
                    responseEnd = "green";
                    debug("Choice: " + choices[which], c);
                }
                if (which == 2) {
                    responseEnd = "red";
                    responseStart = "blue";
                    debug("Choice: " + choices[which], c);
                }
                if (which == 3) {
                    responseStart = "green";
                    responseEnd = "red";
                    debug("Choice: " + choices[which], c);
                }
                if (which == 4) {
                    responseStart = "green";
                    responseEnd = "blue";
                    debug("Choice: " + choices[which], c);
                }
                if (which == 5) {
                    responseStart = "blue";
                    responseEnd = "red";
                    debug("Choice: " + choices[which], c);
                }
                if (which == 6) {
                    responseStart = "blue";
                    responseEnd = "green";
                    debug("Choice: " + choices[which], c);
                }
            }
        });
        dialog.setNegativeButton("Cancel", null);
        dialog.setPositiveButton("Send", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int id) {
                String[] color = {responseStart, responseEnd};

                debug("Gradient: " + color[0] + " fade to " + color[1], c);

                if (color[0] == "red") {
                    r = "149";
                    g = "0";
                    b = "0";

                    rfrac = "1.7";
                    gfrac = "0";
                    bfrac = "0";
                }

                if (color[0] == "green") {
                    r = "0";
                    g = "149";
                    b = "0";

                    rfrac = "0";
                    gfrac = "1.7";
                    bfrac = "0";
                }

                if (color[0] == "blue") {
                    r = "0";
                    g = "0";
                    b = "149";

                    rfrac = "0";
                    gfrac = "0";
                    bfrac = "1.7";
                }

                if (color[1] == "red") {
                    r = "0";
                    rfrac = "1.7";
                }

                if (color[1] == "green") {
                    g = "0";
                    gfrac = "1.7";
                }

                if (color[1] == "blue") {
                    b = "0";
                    bfrac = "1.7";
                }

                debug("Variables: 'r'=" + r + "'g'=" + g + "'b'=" + b + "'rfrac'=" + rfrac + "'gfrac'=" + gfrac + "'bfrac'=" + bfrac, c);

                Request("gradientRed=" + r);
                Request("gradientGreen=" + g);
                Request("gradientBlue=" + b);
                Request("redFraction=" + rfrac);
                Request("greenFraction=" + gfrac);
                Request("blueFraction=" + bfrac);

                debug("Process: all parameters sent", c);
            }

            ;
        });
        dialog.show();
    }
    public static void IntroDialog(Context c, String message){

        AlertDialog.Builder dialog = new AlertDialog.Builder(c);
        dialog.setInverseBackgroundForced(true);
        dialog.setTitle("Changelog");
        dialog.setMessage(message);
        dialog.setNegativeButton("Cancel",null);
        dialog.setPositiveButton("OK",null);
        dialog.show();
}

    public static void Request(String arg) {
        AsyncTaskPostRequest request = new AsyncTaskPostRequest(arg);
        request.execute();
    }

    public static View.OnClickListener handleOnClick(final String params, final Context c) {
        return new View.OnClickListener() {
            public void onClick(View v) {
                Request(params);
                debug("Param: " + params, c);
            }
        };
    }

}
