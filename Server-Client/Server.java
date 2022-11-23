import java.io.*;
import java.net.*;
import java.util.Scanner;

public class Server extends Thread
{
    Socket s;
    Server(Socket s)
    {
        this.s=s;
    }
    @Override
    public void run()
    {
        try
        {
            String ip=s.getRemoteSocketAddress().toString();
            System.out.println("Connected to "+ip+"\n---------------------------");

            DataInputStream din = new DataInputStream(s.getInputStream());
            DataOutputStream dout = new DataOutputStream(s.getOutputStream());



            String str="",str2="";
            while(true)
            {

                str= din.readUTF();
                if(str.equals("stop"))
                {
                    System.out.println("Ending Connection with "+ip+"\n---------------------------");
                    break;
                }
                System.out.println("Client "+ip+" says "+str+"\n---------------------------");
                System.out.println("Sent acknowledgement to client "+ip+"\n---------------------------\"");

                str2="==============Received your message: "+str+"==================";
                dout.writeUTF(str2);
                dout.flush();

            }

            din.close();
            s.close();




        } catch (Exception e)
        {
            System.out.println(e);
        }
    }

}