package kuang.better;

public class testPC2 {
    public static void main(String[] args) {
        television tv = new television();
        new actor(tv).start();
        new audience(tv).start();
    }
}

class actor extends Thread{
    television tv;
    public actor(television tv){
        this.tv = tv;
    }

    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            if(i%2 == 0){
                this.tv.play("快乐大本营播放中");
            }else {
                this.tv.play("刷抖音");
            }
        }
    }
}

class audience extends Thread{
    television tv;
    public audience(television tv){
        this.tv = tv;
    }

    @Override
    public void run() {
        for (int i = 0; i < 20; i++) {
            this.tv.enjoy();
        }
    }
}

class television{
    String perform;
    boolean flag = true; // 标志位

    public synchronized   void play(String perform){
        if (!flag){
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("演员表演了 " + perform);
        // 通知观看
        this.notifyAll();
        this.perform = perform;
        this.flag = !this.flag;
    }

    public synchronized void enjoy(){
        if (flag) {
            try {
                this.wait();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        System.out.println("观众观看了 " + perform);
        //通知
        this.notifyAll();
        this.flag = !this.flag;
    }
}