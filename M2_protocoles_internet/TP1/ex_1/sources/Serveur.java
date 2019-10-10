import java.net.*;
import java.io.*;
import java.lang.*;


class Pos_number
{
	int			nbr = 0;

	void			incr()
	{
		this.nbr++;
	}
	void			decr()
	{
		if (this.nbr > 0)
			this.nbr--;
	}
}

class Serveur
{

	Pos_number	client_nbr = new Pos_number();

	class Connection extends Thread
	{
		Socket		socket;

		public Connection(Socket socket)
		{
			this.socket = socket;
		}
		public void run()
		{
			OutputStream	client_out;

			client_out = socket.getOutputStream();
			Pos_number.incr();
			while (socket.isConnected())	
			{
				Thread.currentThread.sleep(5);
				client_out.println(Pos_number.nbr);
			}
			Pos_number.decr();
			socket.close();
		}
	}

	public static void	main(String[] args)
	{
		ServerSocket	serveur = new ServerSocket(1027);
		Socket 		client;


		while (1)
		{
			client = serveur.accept();
			Connection	new_client = new Connection(client);
			new_client.run();
		}
	}
}
