import java.awt.Rectangle;
import javax.swing.Icon;
import javax.swing.JButton;

/**
 * 单元图片
 */
public class Cell extends JButton {
    //private static final long serialVersionUID = 718623114650657819L;
    public static final int IMAGEWIDTH = 117;// 图片宽度
    private int place;// 图片位置
    
    public Cell(Icon icon, int place) {
        this.setSize(IMAGEWIDTH, IMAGEWIDTH);// 单元图片的大小
        this.setIcon(icon);// 单元图片的图标
        this.place = place;// 单元图片的位置
    }
    
    public void move(Direction dir) {// 移动单元图片的方法
        Rectangle rec = this.getBounds();// 获取图片的Rectangle对象
        switch (dir) {// 判断方向
            case UP:// 向上移动
                this.setLocation(rec.x, rec.y - IMAGEWIDTH);
                break;
            case DOWN:// 向下移动
                this.setLocation(rec.x, rec.y + IMAGEWIDTH);
                break;
            case LEFT:// 向左移动
                this.setLocation(rec.x - IMAGEWIDTH, rec.y);
                break;
            case RIGHT:// 向右移动
                this.setLocation(rec.x + IMAGEWIDTH, rec.y);
                break;
        }
    }
    
    public int getX() {
        return this.getBounds().x;// 获取单元图片的x坐标
    }
    
    public int getY() {
        return this.getBounds().y;// 获取单元图片的y坐标
    }
    
    public int getPlace() {
        return place;// 获取单元图片的位置
    }
}
