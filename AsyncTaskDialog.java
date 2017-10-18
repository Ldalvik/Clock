package root.medfordclock;

import android.app.ProgressDialog;
import android.content.Context;
import android.content.SharedPreferences;
import android.os.AsyncTask;
import android.preference.PreferenceManager;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;

import static root.medfordclock.Util.IntroDialog;

/**
 * Created by student on 10/17/2017.
 */
public class AsyncTaskDialog extends AsyncTask<Void, Void, String> {
    private Context ctx;
    private String url;
    private ProgressDialog p;

    public AsyncTaskDialog(String url, Context ctx) {
        this.url=url;
        this.ctx=ctx;
        this.p=new ProgressDialog(ctx);
    }

    @Override
    protected void onPreExecute() {
        super.onPreExecute();
        p.setMessage("Loading...");
        p.setIndeterminate(false);
        p.setProgressStyle(ProgressDialog.STYLE_SPINNER);
        p.setCancelable(false);
        p.show();
    }

    @Override
    protected String doInBackground(Void... params) {
            final StringBuilder response = new StringBuilder();
                        try{
                            URL obj = new URL(url);

                            try {
                                HttpURLConnection con = (HttpURLConnection) obj.openConnection();
                                try {
                                    con.setRequestMethod("GET");
                                } catch (ProtocolException e) {
                                    e.printStackTrace();
                                }
                                BufferedReader in;
                                try {
                                    in = new BufferedReader(
                                            new InputStreamReader(con.getInputStream()));
                                    String inputLine;
                                    try {
                                        while ((inputLine = in.readLine()) != null) {
                                            response.append(inputLine);
                                        }
                                        in.close();
                                    } catch (IOException e) {
                                        e.printStackTrace();
                                    }
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                            } catch (IOException e) {
                                e.printStackTrace();
                            }
                        } catch (MalformedURLException e) {
                            e.printStackTrace();
                        }
        return response.toString();
    }

    @Override
    protected void onPostExecute(String result) {
        super.onPostExecute(result);
        p.dismiss();
        if (result != null) {
            IntroDialog(ctx, result);
        }
    }
}
