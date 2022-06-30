package com.example.analyzer;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Button b1, b2;
        b1 = (Button)findViewById(R.id.an);
        b2 = (Button)findViewById(R.id.ezh);
        View.OnClickListener l = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switch (v.getId()){
                    case R.id.ezh:
                        Intent intent1 = new Intent(MainActivity.this, Ezhednevnik.class);
                        startActivity(intent1); break;
                    case  R.id.an:
                        Intent intent2 = new Intent(MainActivity.this, Analyzer.class);
                        startActivity(intent2); break;
                }
            }
        };
        b1.setOnClickListener(l);
        b2.setOnClickListener(l);
    }
}
