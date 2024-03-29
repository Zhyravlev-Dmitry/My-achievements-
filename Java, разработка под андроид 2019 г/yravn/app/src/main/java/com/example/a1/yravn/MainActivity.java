package com.example.a1.yravn;

import android.app.Activity;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends Activity {
    // Вызывается при создании Активности
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // Инициализирует Активность.
        setContentView(R.layout.activity_main);
    }

    /** Вызывается при нажатии пользователем на кнопку Решить */
    public void solveEquation(View view) {
        // ax+b=c
        double a = Double.parseDouble( ((EditText)
                findViewById(R.id.coefficient_a)).getText().toString());
        double b = Double.parseDouble( ((EditText)
                findViewById(R.id.coefficient_b)).getText().toString());
        double c = Double.parseDouble( ((EditText)
                findViewById(R.id.coefficient_c)).getText().toString());
        TextView result = (TextView) findViewById(R.id.result);
        if (a!=0&&b*b-4*a*c<0) result.setText("Иррациональное число");
        if (a!=0&&b*b-4*a*c>0)  result.setText("" + String.valueOf((-b+Math.sqrt(b*b-4*a*c)) / (2*a))+"; "+ String.valueOf((-b-Math.sqrt(b*b-4*a*c)) / (2*a)));
        if (a!=0&&b*b==4*a*c)  result.setText("" + String.valueOf((-b+Math.sqrt(b*b-4*a*c))/2*a));
        if (a==0) result.setText("" + String.valueOf(-c / b));
    }

}