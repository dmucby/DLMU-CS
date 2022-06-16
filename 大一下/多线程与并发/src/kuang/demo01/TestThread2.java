package kuang.demo01;

import org.apache.commons.io.FileUtils;

import java.io.File;
import java.io.IOException;
import java.net.URL;

public class TestThread2 extends Thread{

    private final String url;

    private final String name;

    public TestThread2(String url, String name) {
        this.url = url;
        this.name = name;
    }

    @Override
    public void run() {
        WebDownLoader webDownLoader = new WebDownLoader();
        webDownLoader.downLoader(url,name);
        System.out.println("下载了文件名为:" + name);
    }

    public static void main(String[] args) {
        //创建三个线程下载
        TestThread2 t1 = new TestThread2("https://www.veer.com/photo/396078940?topicId=7219.jpg","1.jpg");
        TestThread2 t2 = new TestThread2("https://www.veer.com/photo/396078940?topicId=7219.jpg","2.jpg");
        TestThread2 t3 = new TestThread2("https://www.veer.com/photo/396078940?topicId=7219.jpg","3.jpg");

        t1.start();
        t2.start();
        t3.start();

    }
}

class WebDownLoader{
    public void downLoader(String url,String name){
        try{
            FileUtils.copyURLToFile(new URL(url),new File(name));
        }catch (IOException e){
            e.printStackTrace();
            System.out.println("IO异常，downLoader方法异常");
        }
    }
}