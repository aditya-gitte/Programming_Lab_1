import java.io.*;
import java.net.*;
import java.util.Scanner;
public class Client {
    public static void main(String[] args)
    {
        Scanner z = new Scanner(System.in);
        try
        {
            Socket s = new Socket("localhost", 6563);

            DataOutputStream dout = new DataOutputStream(s.getOutputStream());
            DataInputStream din = new DataInputStream(s.getInputStream());

            String str="",str2="";
            while(true)
            {
                System.out.println("Enter the message for the Server");
                str2=z.nextLine();
                dout.writeUTF(str2);
                dout.flush();
                if(str2.equals("stop"))
                {
                    break;
                }

                str=din.readUTF();
                if(str.equals("stop"))
                {
                    break;
                }
                System.out.println("Server says "+str);
            }



            dout.close();
            s.close();
        }
        catch (Exception e)
        {
            System.out.println(e);
        }
    }
}