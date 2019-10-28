import java.net.*;
import java.io.*;
import java.lang.*;
import java.util.*;


class					Pos_number
{
	static int			nbr = 0;

	static void			incr()
	{
		nbr++;
	}
	static void			decr()
	{
		if (nbr > 0)
			nbr--;
	}
}
class					Serveur
{
	static Pos_number	client_nbr = new Pos_number();

	class				Connection extends Thread
	{
		Socket		socket;

		public			Connection(Socket socket)
		{
			this.socket = socket;
		}

		public void		run()
		{
			OutputStream	client_out;

			try {
				client_out = socket.getOutputStream();
			} catch (IOException e) {
				return ;
			}
			DataOutputStream		outstream = new DataOutputStream(client_out);
			Pos_number.incr();
			System.out.println("New client communication established\nNumber of logged clients :" + Pos_number.nbr);
			while (true)
			{
				try {
					outstream.writeInt(Pos_number.nbr);
				} catch (IOException e) {
					break ;
				}
				try {
					Thread.currentThread().sleep(5);
				} catch (InterruptedException e) {
					e.printStackTrace();
					break ;
				}
			}
			try {
				client_out.close();
				socket.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
			Pos_number.decr();
			System.out.println("Client disconnected.\nNumber of logged clients :" + Pos_number.nbr);
		}
	}

	Serveur (int port) throws IOException
	{
		ServerSocket		serveur = new ServerSocket(port);
		Socket				client;

		while (true)
		{
			try {
				client = serveur.accept();
			} catch (IOException e) {
				e.printStackTrace();
				continue ;
			}
			Connection		new_client = new Connection(client);
			new_client.start();
		}
	}

	public static void	main(String args[])
	{
		try {
			Serveur			serveur = new Serveur(1027);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}
}
