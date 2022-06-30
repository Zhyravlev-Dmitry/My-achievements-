package com.example.analyzer;

import android.content.Context;
import android.database.sqlite.SQLiteDatabase;
import android.database.sqlite.SQLiteOpenHelper;

public class DBHelper extends SQLiteOpenHelper {

    public static final int DATABASE_VERSION =2;
    public static final String DATABASE_NAME = "plan_of_day";
    public static final String TABLE_NAME = "plan_of_day";

    public static final String KEY_ID = "_id";                //ДОПОЛНИТЬ
    public static final String KEY_NOMER = "nomer";           //ДОПОЛНИТЬ
    public static final String KEY_NAME = "name";             //ДОПОЛНИТЬ
    public static final String KEY_OPISANIE = "opisanie";     //ДОПОЛНИТЬ       БД  на проц выполнения, исходный балл, затрач время, коммент
    public static final String KEY_TIMESTART = "time_startDb";//ДОПОЛНИТЬ
    public static final String KEY_TIMEEND = "time_end";      //ДОПОЛНИТЬ
    public static final String KEY_VES = "ves";               //ДОПОЛНИТЬ

    public DBHelper(Context context) {
        super(context, DATABASE_NAME, null, DATABASE_VERSION);
    }

    @Override
    public void onCreate(SQLiteDatabase db) {
        db.execSQL("create table " + TABLE_NAME + "(" +
                KEY_ID + " integer primary key," + KEY_NOMER + " integer,"
                + KEY_NAME + " text," + KEY_OPISANIE + " text," + KEY_TIMESTART + " integer," + KEY_TIMEEND + " integer," + KEY_VES + " integer"
                + ")");
    } // Создание БД

    @Override
    public void onUpgrade(SQLiteDatabase db, int oldVersion, int newVersion) {
        db.execSQL("drop table if exists " + TABLE_NAME); //Удаление
        onCreate(db); //пересоздание при смене версии
    }

}
