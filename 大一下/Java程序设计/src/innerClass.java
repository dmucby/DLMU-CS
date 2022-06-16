abstract class Speak
{ public abstract void speakHello();
}
class Student
{
    void f(Speak sp)
{
    sp.speakHello();
}
}

public class innerClass {
    public static void main(String args[]){
        Student st=new Student();
        st.f( new Speak()
        {
            public void speakHello(){
                System.out.println("I am a student, how are you");
            }
        } );
        Speak speak= new Speak()
        {
            public void speakHello(){
                System.out.println("大家好，祝工作顺利！");
            }
        };
        speak.speakHello();
    }
}

