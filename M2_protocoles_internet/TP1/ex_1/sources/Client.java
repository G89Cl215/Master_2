import java.net.*;
import java.io.*;
import java.nio.*;
import java.lang.*;
import java.util.*;

class		Client 
{ 
	Socket				socket;

	public Client(String address, int port) throws InterruptedException, IOException
	{
		try {
			socket = new Socket(address, port);
			System.out.println("Connected");
		} catch (UnknownHostException u) {
			System.out.println(u); 
		} catch (IOException i) {
			System.out.println(i);
		}
		int					line; 
		DataInputStream		input = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
		Runtime.getRuntime().addShutdownHook(new Thread()
		{
			@Override
			public void run()
			{
				try {
					input.close();
					socket.close();
				} catch (IOException i) {
					System.out.println(i);
				}
				System.out.println("Connection closed by peer");
				return ;
			}
		});
		while (true)
		{
			try {
				line = input.readInt();
				System.out.println(line + " ");
			} catch (IOException i) {
				return ;
			}
		}
	}

	public static void main(String args[]) throws InterruptedException, IOException
	{
		Client client = new Client("127.0.0.1", 1027);
	}
}
