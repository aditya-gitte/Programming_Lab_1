import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Server
{

    public static void main(String[] args)
    {
        try
        {
            Scanner z = new Scanner(System.in);

            ServerSocket ss = new ServerSocket(6563);
            Socket s = ss.accept();// establishes connection
            String ip=s.getRemoteSocketAddress().toString();
            System.out.println("connected to "+ip);

            DataInputStream din = new DataInputStream(s.getInputStream());
            DataOutputStream dout = new DataOutputStream(s.getOutputStream());



            String str="",str2="";
            while(true)
            {

                str= din.readUTF();
                if(str.equals("stop"))
                {
                    break;
                }
                System.out.println("Client "+ip+" says "+str);

                System.out.println("Enter the message for the client "+ ip);
                str2=z.nextLine();
                dout.writeUTF(str2);
                dout.flush();
                if(str2.equals("stop"))
                {
                    break;
                }
            }

            din.close();
            s.close();
            ss.close();



        } catch (Exception e)
        {
            System.out.println(e);
        }
    }
}