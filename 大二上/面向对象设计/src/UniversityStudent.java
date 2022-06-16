import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.OutputStream;

public class UniversityStudent implements Observer{

    Subject subject;
    File myFile;

    UniversityStudent(Subject subject,String fileName){
        this.subject = subject;
        subject.addObserver(this);
        myFile = new File(fileName);
    }

    public void hearTelephone(String heardMess) {
        try{
            OutputStream outputStream = new OutputStream() {
                @Override
                public void write(int b) throws IOException {

                }
            };
            FileWriter fileWriter = new FileWriter(String.valueOf(outputStream));
            fileWriter.write(heardMess);
        }catch (IOException exp){
            System.out.println(exp.toString());
        }
    }
}
