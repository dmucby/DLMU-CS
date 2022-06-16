package RedSpider;

import sun.awt.windows.ThemeReader;

public class ThreadLocalDemo {
    static class ThreadA implements Runnable{
        private ThreadLocal<String> threadLocal;

        public ThreadA(ThreadLocal<String> threadLocal){
            this.threadLocal = threadLocal;
        }

        public void run(){
            threadLocal.set("A");
            try {
                Thread.sleep(1000);
            }catch (InterruptedException e){
                e.printStackTrace();
            }
            System.out.println("ThreadA输出:"+threadLocal.get());
        }
    }
    public static void main(String[] args){
        ThreadLocal<String> threadLocal = new ThreadLocal<>();
        new Thread(new ThreadA(threadLocal)).start();
    }
}
