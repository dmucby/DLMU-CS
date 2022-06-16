import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;

import javax.imageio.ImageIO;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
/**
 * ��Ϸ���2012-6-19
 */
public class GamePanel extends JPanel implements MouseListener {
    private Cell[] cells = new Cell[9];// ������ԪͼƬ����
    private Cell cellBlank = null;// �հ�
    
    // ���췽��
    public GamePanel() {
        super();
        setLayout(null);// ���ÿղ���
        init();// ��ʼ��
    }
    
    // ��ʼ����Ϸ
    public void init() {
    	//Image image = imageIcon.getImage();    // �����ͼƬ̫���ʺ���Icon
    	int x=0;
    	int y=0;
    	int w=110;
    	int h=110;
    	BufferedImage src=null;
    	BufferedImage newpic=null;
    	try{
    		 src = ImageIO.read(new File("pic\\woman.jpg"));
    	}
    	catch(Exception e)
    	{
    		System.out.println(e);
    	}
    	newpic=src.getSubimage(x, y, w, h);
    	
        int num = 0;// ͼƬ���
        Icon icon = null;// ͼ�����
        Cell cell = null;// ��ԪͼƬ����
        for (int i = 0; i < 3; i++) {// ѭ����
            for (int j = 0; j < 3; j++) {// ѭ����
                num = i * 3 + j;// ����ͼƬ���
                icon = new ImageIcon("pic\\"+ (num + 1) + ".jpg");// ��ȡͼƬ
                x=j*100;
                y=i*100;
                newpic=src.getSubimage(x, y, w, h);
                if(num+1==9)
                	icon = new ImageIcon("pic\\"+ (num + 1) + ".jpg");// ��ȡͼƬ
                else
                	icon=new   ImageIcon(newpic);
                cell = new Cell(icon, num);// ʵ������ԪͼƬ����
                cell.setLocation(j * Cell.IMAGEWIDTH, i * Cell.IMAGEWIDTH);// ���õ�ԪͼƬ������
                cells[num] = cell;// ����ԪͼƬ�洢����ԪͼƬ������
            }
        }
        for (int i = 0; i < cells.length; i++) {
            this.add(cells[i]);// �������������е�ԪͼƬ
        }
    }
    
    /**
     * ��ͼƬ�����������
     */
    public void random() {
        Random rand = new Random();// ʵ����Random
        int m, n, x, y;
        if (cellBlank == null) {// �жϿհ׵�ͼƬλ���Ƿ�Ϊ��
            cellBlank = cells[cells.length - 1];// ȡ���հ׵�ͼƬ
            for (int i = 0; i < cells.length; i++) {// �������е�ԪͼƬ
                if (i != cells.length - 1) {
                    cells[i].addMouseListener(this);// �Էǿհ�ͼƬע��������
                }
            }
        }
        for (int i = 0; i < cells.length; i++) {// �������е�ԪͼƬ
            m = rand.nextInt(cells.length);// ���������
            n = rand.nextInt(cells.length);// ���������
            x = cells[m].getX();// ��ȡx����
            y = cells[m].getY();// ��ȡy����
            // �Ե�ԪͼƬ����
            cells[m].setLocation(cells[n].getX(), cells[n].getY());
            cells[n].setLocation(x, y);
        }
    }

    public void mousePressed(MouseEvent e) {

    }
    
    public void mouseReleased(MouseEvent e) {
    }
    

    public void mouseClicked(MouseEvent e) {
        Cell cell = (Cell) e.getSource();// ��ȡ����ʱ��Ķ���
        int x = cellBlank.getX();// ��ȡx����
        int y = cellBlank.getY();// ��ȡy����
        if ((x - cell.getX()) == Cell.IMAGEWIDTH && cell.getY() == y) {
            cell.move(Direction.RIGHT);// �����ƶ�
            cellBlank.move(Direction.LEFT);
        } else if ((x - cell.getX()) == -Cell.IMAGEWIDTH && cell.getY() == y) {
            cell.move(Direction.LEFT);// �����ƶ�
            cellBlank.move(Direction.RIGHT);
        } else if (cell.getX() == x && (cell.getY() - y) == Cell.IMAGEWIDTH) {
            cell.move(Direction.UP);// �����ƶ�
            cellBlank.move(Direction.DOWN);
        } else if (cell.getX() == x && (cell.getY() - y) == -Cell.IMAGEWIDTH) {
            cell.move(Direction.DOWN);// �����ƶ�
            cellBlank.move(Direction.UP);
        }
        if (isSuccess()) {// �ж��Ƿ�ƴͼ�ɹ�
            int i = JOptionPane.showConfirmDialog(this, "�ɹ�������һ�֣�", "ƴͼ�ɹ�",
                    JOptionPane.YES_NO_OPTION);// ��ʾ�ɹ�
            if (i == JOptionPane.YES_OPTION) {
                random();// ��ʼ��һ��
            }
        }
    }

    public void mouseEntered(MouseEvent e) {
    }

    public void mouseExited(MouseEvent e) {
    }
    
    /**
     * �ж��Ƿ�ƴͼ�ɹ�
     * 
     * @return ����ֵ
     */
    public boolean isSuccess() {
        for (int i = 0; i < cells.length; i++) {// �������е�ԪͼƬ
            int x = cells[i].getX();// ��ȡx����
            int y = cells[i].getY();// ��ȡy����
            if (i != 0) {
                if (y / Cell.IMAGEWIDTH * 3 + x / Cell.IMAGEWIDTH != cells[i]
                        .getPlace()) {// �жϵ�ԪͼƬλ���Ƿ���ȷ
                    return false;// ֻҪ��һ����ԪͼƬ��λ�ò���ȷ���ͷ���false
                }
            }
        }
        return true;// ���е�ԪͼƬ��λ�ö���ȷ����true
    }
}
