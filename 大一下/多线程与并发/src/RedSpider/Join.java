package RedSpider;

public class Join {
    static class ThreadA implements Runnable {
        public void run(){
            try{
                System.out.println("我是子线程,我先睡一秒");
                Thread.sleep(1000);
                System.out.println("我是子线程，我睡完一秒");
            }catch (InterruptedException e){
                e.printStackTrace();
            }
        }
    }

    public static void main(String[] args){
        Thread thread = new Thread(new ThreadA());
        thread.start();
        try {
            thread.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("如果不加join方法，我会先被打出来，加了就不一样了");
    }
}
