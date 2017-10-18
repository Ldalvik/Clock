package root.medfordclock;

import android.annotation.TargetApi;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.os.Build;
import android.support.annotation.RequiresApi;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.ProtocolException;
import java.net.URL;
import java.nio.charset.StandardCharsets;

public class AsyncTaskPostRequest extends AsyncTask<String, Void, String> {
    private Context ctx;
    private String arg;

    public AsyncTaskPostRequest(String arg) {
        this.arg=arg;
    }

    @Override
    protected void onPreExecute() {

    }

    @Override
    protected String doInBackground(String... params) {
        final StringBuilder response = new StringBuilder();

                    String url = "https://api.particle.io/v1/devices/2b0035001247353136383631/color?access_token=13603d6d6d0dd75418d22bde371fc0afa4305273";
                    try{
                        URL obj = new URL(url);
                        try {
                            HttpURLConnection con = (HttpURLConnection) obj.openConnection();
                            try {
                                con.setRequestMethod("POST");
                            } catch (ProtocolException e) {
                                e.printStackTrace();
                            }

                            String urlParameters = "arg=" + arg;
                            byte[] postData = new byte[0];
                            if (android.os.Build.VERSION.SDK_INT >= android.os.Build.VERSION_CODES.KITKAT) {
                                postData = urlParameters.getBytes(StandardCharsets.UTF_8);
                            }
                            int    postDataLength = postData.length;
                            con.setDoOutput(true);
                            con.setInstanceFollowRedirects(false);
                            con.setRequestProperty("Content-Type", "application/x-www-form-urlencoded");
                            con.setRequestProperty("charset", "utf-8");
                            con.setRequestProperty("Content-Length", Integer.toString(postDataLength));
                            con.setUseCaches(false);
                            try( DataOutputStream wr = new DataOutputStream(con.getOutputStream())) {
                                wr.write(postData);
                            }
                            BufferedReader in = null;
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
        return arg;
    }

    @Override
    protected void onPostExecute(String result) {
        super.onPostExecute(result);
        if(result!=null) {
            System.out.println("Request sent->" + result);
        } else {
            //Toast.makeText(ctx, "Could not send the request" + result +"; Are you connected to the internet?", Toast.LENGTH_SHORT).show();
        }
    }
}
