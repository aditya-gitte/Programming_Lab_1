import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerMain
{
    public static void main(String[] args) throws IOException
    {
        ServerSocket ss = new ServerSocket(6563);
        while(true)
        {
            Socket s=ss.accept();
            Server myserver = new Server(s);
            myserver.start();
        }

    }
}