package com.example.analyzer;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

public class Ezhednevnik extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_ezhednevnik);

        Button b1, b2, b3, b4;
        b1 = (Button)findViewById(R.id.planseg);
//        b2 = (Button)findViewById(R.id.planzav);
        View.OnClickListener l = new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                switch (v.getId()){
//                    case R.id.planzav:
//                        Intent intent1 = new Intent(Ezhednevnik.this, PlanNaZavtra.class);
//                        startActivity(intent1); break;
                    case R.id.planseg:
                        Intent intent2 = new Intent(Ezhednevnik.this, PlanNaSegodna.class);
                        startActivity(intent2); break;

                }
            }
        };
        b1.setOnClickListener(l);
//        b2.setOnClickListener(l);
    }
}
