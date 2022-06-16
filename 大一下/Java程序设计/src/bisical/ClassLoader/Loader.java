package bisical.ClassLoader;

class Earth{
    static Sky s=new Sky();
    Earth(){
        System.out.println("earth");
    }
}

class Sky{
    static Earth e=new Earth();
    Sky(){
        System.out.println("sky");
    }
}

public class Loader {

    public static void main(String[] args){
        new Sky();
    }

}

