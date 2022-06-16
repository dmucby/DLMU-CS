import java.awt.Rectangle;
import javax.swing.Icon;
import javax.swing.JButton;

/**
 * ��ԪͼƬ
 */
public class Cell extends JButton {
    //private static final long serialVersionUID = 718623114650657819L;
    public static final int IMAGEWIDTH = 117;// ͼƬ���
    private int place;// ͼƬλ��
    
    public Cell(Icon icon, int place) {
        this.setSize(IMAGEWIDTH, IMAGEWIDTH);// ��ԪͼƬ�Ĵ�С
        this.setIcon(icon);// ��ԪͼƬ��ͼ��
        this.place = place;// ��ԪͼƬ��λ��
    }
    
    public void move(Direction dir) {// �ƶ���ԪͼƬ�ķ���
        Rectangle rec = this.getBounds();// ��ȡͼƬ��Rectangle����
        switch (dir) {// �жϷ���
            case UP:// �����ƶ�
                this.setLocation(rec.x, rec.y - IMAGEWIDTH);
                break;
            case DOWN:// �����ƶ�
                this.setLocation(rec.x, rec.y + IMAGEWIDTH);
                break;
            case LEFT:// �����ƶ�
                this.setLocation(rec.x - IMAGEWIDTH, rec.y);
                break;
            case RIGHT:// �����ƶ�
                this.setLocation(rec.x + IMAGEWIDTH, rec.y);
                break;
        }
    }
    
    public int getX() {
        return this.getBounds().x;// ��ȡ��ԪͼƬ��x����
    }
    
    public int getY() {
        return this.getBounds().y;// ��ȡ��ԪͼƬ��y����
    }
    
    public int getPlace() {
        return place;// ��ȡ��ԪͼƬ��λ��
    }
}
