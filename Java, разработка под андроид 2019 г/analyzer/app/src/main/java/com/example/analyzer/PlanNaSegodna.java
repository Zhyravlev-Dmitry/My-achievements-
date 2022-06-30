package com.example.analyzer;

import android.annotation.SuppressLint;
import android.app.Dialog;
import android.content.ContentValues;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.ExpandableListView;
import android.widget.ImageView;
import android.widget.TextView;
import android.widget.Toast;

public class PlanNaSegodna extends AppCompatActivity {

    private static String err ="";
    protected static int lastNomer;
    protected Button dob, btnClear;
    protected TextView nomer, name, opisanie, ves, srok, rasVrem;
    protected WhatButton whatButton;
    Handler handler;
    ExpandableListView listView;
    SQLiteDatabase database;
    static DBHelper dbHelper;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState); // ПРОДУМАТЬ пересоздание листа при закрытии диалогового окна
        setContentView(R.layout.activity_plan_na_segodna);
        dbHelper = new DBHelper(this);
        database = dbHelper.getWritableDatabase(); //открыли БД для работы

        btnClear = (Button) findViewById(R.id.btnClear);
        btnClear.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {database.delete(DBHelper.TABLE_NAME,null,null); }
        }); //очистка БД (потом поменяется на частичную)

        listView = (ExpandableListView)  findViewById(R.id.listView);
        MyExpandableListAdapter myExpandableListAdapter =new MyExpandableListAdapter(this);
        listView.setAdapter(myExpandableListAdapter);
        listView.setOnChildClickListener(new ExpandableListView.OnChildClickListener() {
            @Override
            public boolean onChildClick(ExpandableListView parent, View v, int groupPosition, int childPosition, long id) {
                return false;
            }
        }); //При клике на дочерний элемент



        dialog();
    }

    public void dialog (){
        ImageView nov =(ImageView) findViewById(R.id.nov);
        final Dialog dopPlan = new Dialog (PlanNaSegodna.this);
        dopPlan.setContentView(R.layout.activity_dop_plan_day);
        dopPlan.setCancelable(false);
        dopPlan.setTitle("Доп план на день");
        nov.setOnClickListener(new View.OnClickListener() {
            @SuppressLint("HandlerLeak")
            @Override
            public void onClick(View v) {
                dopPlan.show();
                handler = new Handler(){
                    @SuppressLint("ResourceAsColor")
                    @Override
                    public void handleMessage(Message msg) {
                        if(msg.what==1){
                            dob.setText("Закрыть");
                        }
                        else {
                            dob.setText("Добавить");
                        }
                    }
                }; //Смена стиля кнопки при вводе
                whatButton=new WhatButton();
                whatButton.start(); //тоже про кнопку
            }
        });

        dob =(Button) dopPlan.findViewById(R.id.butDopPlan);
        nomer = (TextView) dopPlan.findViewById(R.id.nomer);
        name = (TextView) dopPlan.findViewById(R.id.name);
        opisanie = (TextView) dopPlan.findViewById(R.id.opisanie);
        ves = (TextView) dopPlan.findViewById(R.id.ves);
        srok = (TextView) dopPlan.findViewById(R.id.srok);
        rasVrem = (TextView) dopPlan.findViewById(R.id.rasVrem); //определили все поля окна
        dob.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                if (nomer.getText().length() == 0 && name.getText().length() == 0 &&
                    opisanie.getText().length() == 0 && ves.getText().length() == 0 &&
                    srok.getText().length() == 0 && rasVrem.getText().length() == 0){
                    dopPlan.dismiss(); //Закрыть, если в полях все пусто
                    if (whatButton != null) {
                        Thread dummy = whatButton;
                        whatButton = null;
                        dummy.interrupt();
                    } //останавливаем поток изменения кнопки
                } //ЗАКРЫВАЕМ БЕЗ ИЗМЕНЕНИЙ

                else { //Если в полях окна что-то есть
                    err="";
                    if(parseTime(srok.getText().toString())==-1) err ="Неверный формат времени";
                    if (rasVrem.getText().length() == 0)  err = "Не введено рассчетное время";
                    if (srok.getText().length() == 0)  err = "Не введено время начала";
                    if (ves.getText().length() == 0)  err = "Не введен \"вес\" дела";
                    if (name.getText().length() == 0)  err = "Не введено название";
                    if (nomer.getText().length() == 0)  err = "Не введен номер";
                    else if (Integer.parseInt(nomer.getText().toString()) == 0) err = "Неверно введен номер";
                    if (err.length()!=0){
                            Toast.makeText(getApplicationContext(), err, Toast.LENGTH_LONG).show();
                    } //ОШИБКА ЗАПОЛНЕНИЯ
                    else {
                        if (whatButton != null) {
                            Thread dummy = whatButton;
                            whatButton = null;
                            dummy.interrupt();
                        } //останавливаем поток изменения кнопки
                        newEntry();
                        nomer.setText(""); name.setText(""); opisanie.setText(""); ves.setText(""); srok.setText("");
                        rasVrem.setText(""); //Отчистка полей

                        Toast.makeText(getApplicationContext(), "Запись сохранена", Toast.LENGTH_LONG).show(); //Потом убрать или перенести глубже
                        dopPlan.dismiss();
                    } // ЗАКРЫВАЕМ И ДОБАВЛЯЕМ
                }

            }
        });

    } // Диалоговое окно и проверка ввода данных

    public void newEntry (){

        ContentValues contentValues = new ContentValues(); // 1 строка таблицы

        int nomerS = Integer.parseInt(nomer.getText().toString());
        String nameS = name.getText().toString();
        String opisanieS = opisanie.getText().toString();
        int timeStart = parseTime(srok.getText().toString());
        int timeEnd = timeStart + Integer.parseInt(rasVrem.getText().toString());
        int vesS = Integer.parseInt(ves.getText().toString());

        contentValues.put(DBHelper.KEY_NAME, nameS);
        contentValues.put(DBHelper.KEY_OPISANIE, opisanieS);
        contentValues.put(DBHelper.KEY_TIMESTART, timeStart);

        contentValues.put(DBHelper.KEY_TIMEEND, timeEnd);
        contentValues.put(DBHelper.KEY_VES, vesS); //спарсить через функцию в нужный формат (или парсить при выводе)

        Cursor cursor = database.query(DBHelper.TABLE_NAME,null, null, null, null, null, null); // Что за нули?!
        if(cursor.moveToFirst()){
            cursor.moveToLast();
            lastNomer = cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_NOMER));
        } else lastNomer =0;
        cursor.close();

        if (nomerS>lastNomer){
            contentValues.put(DBHelper.KEY_NOMER, lastNomer+1);
            database.insert(DBHelper.DATABASE_NAME, null, contentValues);
        }
        else {
            Cursor cr = database.query(DBHelper.TABLE_NAME, null, null, null, null, null, null);
            if (cr.moveToLast()) {
                do {
                    int n = cr.getInt(cr.getColumnIndex(DBHelper.KEY_NOMER));
                    if (n >= nomerS)
                        database.execSQL("UPDATE " + DBHelper.TABLE_NAME + " SET " + DBHelper.KEY_NOMER + " = " + DBHelper.KEY_NOMER + " + 1" +
                                " WHERE " + DBHelper.KEY_NOMER + " = " + n);
                } while (cr.moveToPrevious()); // смещение nomera
            } else
                Toast.makeText(this, "Ошибка заполнения БД, произведите полную очистку в настройках", Toast.LENGTH_LONG).show();

            contentValues.put(DBHelper.KEY_NOMER, nomerS);
            database.insert(DBHelper.TABLE_NAME, null, contentValues);
            cr.close();
        } //Добавление зписи через смещение номера


        /*---------------------------------------------- Вывод в лог БД-------------------------------------*/

        Cursor crWrite = database.query(DBHelper.TABLE_NAME,null, null, null, null, null, null);
        if (crWrite.moveToFirst()) {
            do {
                Log.d("mLog", "\nID = " + crWrite.getInt(crWrite.getColumnIndex( DBHelper.KEY_ID)) +
                        ", nomer = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_NOMER)) +
                        ", name = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_NAME)) +
                        ", opisanie = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_OPISANIE)) +
                        ", time Start  = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_TIMESTART) ) +
                        ", time End = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_TIMEEND)) +
                        ", ves = " + crWrite.getString(crWrite.getColumnIndex(DBHelper.KEY_VES)));
            } while (crWrite.moveToNext());
        } else
            Log.d("mLog","0 rows");
        /*---------------------------------------------------------------------------------------------------*/
    } //Добавление в БД новой записи

    private int parseTime(String s){
        int ts = -1;
        if(s.length()==4)
            if(s.charAt(0)>47 && s.charAt(0)<58 &&
               s.charAt(1)==58&& s.charAt(2)>47 && s.charAt(2)<54 &&
               s.charAt(3)>47 && s.charAt(3)<58)
                    ts =(s.charAt(0)-48)*60+(s.charAt(2)-48)*10+s.charAt(3)-48;
        if(s.length()==5)
            if(s.charAt(0)>47 && s.charAt(0)<51 &&
               s.charAt(1)>47 && s.charAt(1)<58 &&
               s.charAt(2)==58&& s.charAt(3)>47 && s.charAt(3)<54 &&
               s.charAt(4)>47 && s.charAt(4)<58)
                ts =(s.charAt(0)-48)*600+(s.charAt(1)-48)*60+(s.charAt(3)-48)*10+s.charAt(4)-48;
         if(ts>1439) ts=-1;
     return ts;
    }//возвращает время в минутах от 00:00 или -1 в случае ошибки
    class WhatButton extends Thread {
        @Override
        public void run() {
            int wButton;
            while(true) {
                try{
                    Thread.sleep(200);
                } catch(InterruptedException e){}
                if(nomer.getText().length() == 0 && name.getText().length() == 0 &&
                        opisanie.getText().length() == 0 && ves.getText().length() == 0 &&
                        srok.getText().length() == 0 && rasVrem.getText().length() == 0)
                    wButton =1;
                else wButton =0;
                handler.sendEmptyMessage(wButton);
            }
        }
    }
}
