package Exception;

public class ExceptionDemo{
    static int avg(int a,int b) throws MyException{
        if(a<0||b<0)
            throw new MyException("负值不可");
	    else if(a>100||b>100)
            throw new MyException("数值过大");
        return(a+b)/2;
    }
    public static void main (String[] args){
        try{
            System.out.println(avg(-10,20));
        }catch(MyException e){
            System.out.println(e);
        }
    }
}
class MyException extends Exception{
    MyException(String ErrorMessage){
        super(ErrorMessage);
    }
}