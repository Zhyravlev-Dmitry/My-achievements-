package com.example.analyzer;

import android.content.Context;
import android.database.Cursor;
import android.database.sqlite.SQLiteDatabase;
import android.graphics.Typeface;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseExpandableListAdapter;
import android.widget.TextView;
import android.widget.Toast;
import java.util.HashMap;
import java.util.List;

public class MyExpandableListAdapter extends BaseExpandableListAdapter {

    private class Group{
        int listNomer;
        String  listName;
        int listStart;//время начала
        int listEnd; //время конца
        int listVes;

        public Group(int listNomer, String listName, int listStart, int listEnd, int listVes) {
            this.listNomer = listNomer;
            this.listName = listName;
            this.listStart = listStart;
            this.listEnd = listEnd;
            this.listVes = listVes;
        }
    }

    private class Children{
        String listOpisanie;
        boolean listFlag;
        int listPercent;
        int listBall;
        int listRasVrem;
        String  listComment;

        public Children(String listOpisanie, boolean listFlag, int listPercent, int listBall, int listRasVrem, String  listComment) {
            this.listOpisanie = listOpisanie;
            this.listFlag = listFlag;
            this.listPercent = listPercent;
            this.listBall = listBall;
            this.listRasVrem = listRasVrem;
            this.listComment = listComment;
        }
    }

    private Context context;
    private List<Group> listGroup;
    private HashMap <Integer, Children> listChildren;

    private int lastNomer;


    public MyExpandableListAdapter (Context context) {
        this.context = context;
        try {
            SQLiteDatabase database = PlanNaSegodna.dbHelper.getWritableDatabase();
            Cursor cursor = database.query(DBHelper.TABLE_NAME, null, null, null, null, null, null);
            if (cursor.moveToLast())
                lastNomer = cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_NOMER)); //Подключили БД и считали последний номер

            if (cursor.moveToFirst()) {
                int i = 0;
                do {
                    if (cursor.getString(cursor.getColumnIndex(DBHelper.KEY_NOMER)).equals("")) {//если строка не пустая (номер есть), то добавлять в лист
                        listGroup.add(new Group(cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_NOMER)),
                                cursor.getString(cursor.getColumnIndex(DBHelper.KEY_NAME)),
                                cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_TIMESTART)),
                                cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_TIMEEND)),
                                cursor.getInt(cursor.getColumnIndex(DBHelper.KEY_VES))));


                        listChildren.put(listGroup.get(i).listNomer, new Children(
                                cursor.getString(cursor.getColumnIndex(DBHelper.KEY_OPISANIE)),
                                false, 0, 0, 0, ""
                        )); //ДОПИСАТЬ ИЗ БД -----------------
                        i++;
                    }
                } while (cursor.moveToNext()); // смещение nomera
            } // Добавление группы из БД
            else Toast.makeText(context, "Список дел пуст", Toast.LENGTH_LONG).show();

            cursor.close(); //Считывания количества View из БД
        } catch (Exception e) {Toast.makeText(context, "Ошибка создания MyExpandableListAdapter", Toast.LENGTH_LONG).show();}
    }


    @Override
    public int getGroupCount() {
        return lastNomer;
    } //количество групп списка

    @Override
    public int getChildrenCount(int groupPosition) {
        return 1;
    } //количество детей списка

    @Override
    public Object getGroup(int groupPosition) {
        return this.listGroup.get(groupPosition);
    }

    @Override
    public Object getChild(int groupPosition, int childPosition) {
        return this.listChildren.get(this.listGroup.get(groupPosition));
    }

    @Override
    public long getGroupId(int groupPosition) {
        return groupPosition;
    }

    @Override
    public long getChildId(int groupPosition, int childPosition) {
        return groupPosition;
    }

    @Override
    public boolean hasStableIds() {
        return false;
    }

    @Override
    public View getGroupView(int groupPosition, boolean isExpanded, View convertView, ViewGroup parent) {
     try {
        if (convertView == null) {
            LayoutInflater infalInflater = (LayoutInflater) this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            convertView = infalInflater.inflate(R.layout.listview_groupview, null);
        }

        TextView listNomer = (TextView) convertView.findViewById(R.id.listNomer);
        TextView listName = (TextView) convertView.findViewById(R.id.listName);
        TextView listTime = (TextView) convertView.findViewById(R.id.listTime);
        TextView listVes = (TextView) convertView.findViewById(R.id.listVes);

        listNomer.setTypeface(null, Typeface.BOLD); // ????????? Сомнительная строчка ???????????
        listNomer.setText(String.valueOf(this.listGroup.get(groupPosition).listNomer));
        listName.setText((String) this.listGroup.get(groupPosition).listName);
        listVes.setText(String.valueOf(this.listGroup.get(groupPosition).listVes));
        listTime.setText(String.valueOf(this.listGroup.get(groupPosition).listStart) + ":" + String.valueOf(this.listGroup.get(groupPosition).listEnd)); //НЕ забудь конвертировать в нужный формат ---------------------------------------
     } catch (Exception e) {Toast.makeText(context, "Ошибка GETGROUP", Toast.LENGTH_LONG).show();}
        return convertView;
    } //МЕТОД СОЗДАНИЯ самого раскрывающегося списка

    @Override
    public View getChildView(int groupPosition, int childPosition, boolean isLastChild, View childView, ViewGroup parent) {
     try {
        if (childView == null) {
            LayoutInflater infalInflater = (LayoutInflater) this.context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
            childView = infalInflater.inflate(R.layout.listview_groupview_childview, null);
        }
        TextView listOpisanie = (TextView) childView.findViewById(R.id.listOpisanie);
        TextView listFlag = (TextView) childView.findViewById(R.id.listFlag);
        TextView listPercent = (TextView) childView.findViewById(R.id.listPercent);
        TextView listBall = (TextView) childView.findViewById(R.id.listBall);
        TextView listRasVrem = (TextView) childView.findViewById(R.id.listRasVrem);
        TextView listComment = (TextView) childView.findViewById(R.id.listComment);

        listOpisanie.setText((String) this.listChildren.get(this.listGroup.get(groupPosition)).listOpisanie); // Доделать взаимодействие с Main.Activity ---------------------------------------
     } catch (Exception e) {Toast.makeText(context, "Ошибка getChildView", Toast.LENGTH_LONG).show();}
        return childView;
    }


    @Override
    public boolean isChildSelectable(int groupPosition, int childPosition) {
        return false;
    }
}
