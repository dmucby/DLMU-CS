package awt;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class test {
    public static  void main(String[] args){
        s3 a = new s3("sb");
    }
}
class s1 extends JFrame{
    s1(String s){
        super(s);
        setVisible(true);
        setSize(500,500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

class s2 extends JFrame{
    JTextField m;
    JTextField n;
    s2(String s){
        super(s);
        setLayout(new FlowLayout());
        m = new JTextField("我不可编辑",10);
        n = new JTextField(10);
        m.setEditable(false);
        add(m);
        add(n);
        setVisible(true);
        setBounds(500,500,500,500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}

class s3 extends JFrame implements ActionListener {
    JTextField m;
    JTextField n;

    s3(String s) {
        super(s);
        setLayout(new FlowLayout());
        m = new JTextField(20);
        n = new JTextField(20);
        n.setEditable(false);
        add(m);
        add(n);
        m.addActionListener(this);
        setVisible(true);
        setBounds(500, 500, 500, 500);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == m) {
            int a,b;
            try {
                a = Integer.parseInt(m.getText());
                b = a * a;
                n.setText(a + "的平方是" + b);
            } catch (Exception ez) {
                m.setText(null);
                n.setText("请输入数字");
            }
        }
    }
}