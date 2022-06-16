import java.awt.BorderLayout;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainFrame extends JFrame {
    public static void main(String args[]) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    MainFrame frame = new MainFrame();
                    frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
    
    /**
     * Create the frame
     */
    public MainFrame() {
        super();
        getContentPane().setLayout(new BorderLayout());
        setTitle("ƴͼ��Ϸ");
        setBounds(300, 300, 358, 414);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        // ʵ����JPanel
        final JPanel panel = new JPanel();
        // ��ӵ��Ϸ�
        getContentPane().add(panel, BorderLayout.NORTH);
        // ʵ������Ϸ���
        final GamePanel gamePanel = new GamePanel();
        // ��ӵ�����λ��
        getContentPane().add(gamePanel, BorderLayout.CENTER);
        // ʵ������ť
        final JButton button = new JButton();
        // ע���¼�
        button.addActionListener(new ActionListener() {
            public void actionPerformed(final ActionEvent e) {
                // ��ʼ��Ϸ
                gamePanel.random();
            }
        });
        button.setText("��ʼ");
        panel.add(button);
    }
    
}
