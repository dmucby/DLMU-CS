package awt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class 考试重点 {
    public static void main(String[] args){

        文本框 A = new 文本框("wo ai cai");
    }
}

class swi extends JFrame{
    swi(String s){
        super(s);
        setSize(400,800);
        setVisible(true);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    }
}

class 文本框 extends JFrame{
    JTextField text1,text2;
    文本框(String s){
        super(s);
        super.setLayout(new FlowLayout());
        text1 = new JTextField("我不可编辑",50);
        text1.setEditable(false);
        text1.setHorizontalAlignment(JTextField.CENTER);
        text2 = new JTextField(10);
        text2.setEditable(true);
        super.add(text1);
        super.add(text2);
        super.setBounds(500,500,500,500);
        super.setVisible(true);
        super.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

/*
class jianting extends JFrame implements ActionListener {

    JTextField textInput,textShow;
    jianting(String s){
        super(s);
        super.setLayout(new FlowLayout());
        textInput = new JTextField(10);
        textShow  = new JTextField(10);
        textShow.setEditable(false);
        add(textInput);
        add(textShow);
        textInput.addActionListener(this);
        super.setVisible(true);
        super.setBounds(500,500,500,500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent e){
        if(e.getSource()==textInput){
            int n=0,m=0;
            try{
                n=Integer.parseInt(textInput.getText());
                m=n*n;
                textShow.setText(n+"的平方是"+m);
            }catch (Exception ee){
                textShow.setText("请输入数字");
                textInput.setText(null);
            }
        }
    }
}
*/

class Event extends JFrame implements ActionListener{
    JTextField textInput,textShow;
    Event(String s){
        super(s);
        super.setLayout(new FlowLayout());
        textInput = new JTextField(10);
        textShow  = new JTextField(10);
        textShow.setEditable(false);
        add(textInput);
        add(textShow);
        textInput.addActionListener(this);//本身就是监听器
        setVisible(true);
        super.setBounds(400,400,400,400);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
    public void actionPerformed(ActionEvent e){
        if(e.getSource()==textInput){
            int n,m;
            try{
                n = Integer.parseInt(textInput.getText());
                m=n*n;
                textShow.setText(n+"的平方是"+m);
            }catch (Exception ee){
                textShow.setText("请输入数字");
                textInput.setText(null);
            }
        }
    }
}
