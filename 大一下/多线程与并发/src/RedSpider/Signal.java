package RedSpider;

import kotlin.jvm.Synchronized;

public class Signal {
    private static volatile int signal = 0;

    static class ThreadA implements Runnable{
        public void run(){
            while(signal<5){
                if(signal %2 == 0){
                    System.out.println("ThreadA:"+signal);
                    synchronized(this){
                        signal++;
                    }
                }
            }
        }
    }

    static class ThreadB implements Runnable{
        public void run(){
            while(signal<5){
                if(signal %2 == 1) {
                    System.out.println("ThreadB:" + signal);
                    synchronized(this){
                        signal = signal + 1;
                    }
                }
            }
        }
    }

    public static void main(String[] args){
        new Thread(new ThreadA()).start();
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        new Thread(new ThreadB()).start();
    }
}
