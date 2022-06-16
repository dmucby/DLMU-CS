package extendsDemo;

class Art{
    Art(){
        System.out.println("Art constructor");
    }
}


class Drawing extends Art{
    Drawing(){
        System.out.println("Drawing constructor");
    }
}

public class Cartoon extends Drawing{
    public Cartoon(){
        System.out.println("Cartoon constructor");
    }

    public static void main(String[] args){
        System.out.println("extends constructor queue");
        System.out.println("-------------------------");
        Cartoon x= new Cartoon();
    }
}
