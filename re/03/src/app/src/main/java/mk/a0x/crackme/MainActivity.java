package mk.a0x.crackme;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Button btn = findViewById(R.id.button2);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                TextView input_flag = findViewById(R.id.input_flag);
                TextView result_text = findViewById(R.id.sample_text);
                boolean result = checkFlag(input_flag.getText().toString());
                if(result) {
                    result_text.setText("Correct");
                } else {
                    result_text.setText("Wrong");
                }
            }
        });
    }

    public native boolean checkFlag(String flag);
}
