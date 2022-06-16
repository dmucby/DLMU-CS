package OOP_Te_Xing.extendsDemo;

public class constructor {
    private constructor cs;

    public constructor(constructor cs){
        this.cs = cs;
    }

}

class Constructor2 extends constructor{

    public Constructor2(constructor cs) {
        super(cs);
        constructor c = cs;
    }

}