package com.unicamp.redes.server;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Server implements SubjectsDatabase {
	private static final String password = "1234";
	private Boolean isAuthenticated;

	public Server() { isAuthenticated = false; }


	public String HandleCommand(String data) throws RemoteException {
		String[] splitter;
		System.out.println("Received data: " + data);
		String output = null;
		char op = data.charAt(0);
		System.out.println("OP: " + op);
		switch (op) {
			case '1':
				if (!isAuthenticated)
				{
					output = "FAILED";
				} else {
					splitter = data.substring(1).split("_");
					Disciplina disc = new Disciplina(splitter[0], splitter[1], splitter[2]);
					Disciplina.AddToList(disc);
					output = "SUCCESS";
				}
				break;
			case '2':
				output = Disciplina.ListSubjects();
				break;
			case '3':
				output = Disciplina.GetByCodigo(data.substring(1)).getEmenta();
				break;
			case '4':
				Disciplina disc = Disciplina.GetByCodigo(data.substring(1));
				output = disc.getInfo();
				break;
			case '5':
				output = Disciplina.GetInfoAll();
				break;
			case '6':
				if (!isAuthenticated)
				{
						output = "FAILED";
				} else {
						Disciplina.GetByCodigo(data.substring(1,6)).AtualizaTextoAula(data.substring(6));
						output = "SUCCESS";
				}
				break;
			case '7':
				output = Disciplina.GetByCodigo(data.substring(1)).getTextoAula();
				break;
			case 't':
				if (!data.substring(1).equals(password)) {
					output = "FAILED";
				}
				else
				{
					output = "SUCCESS";
					isAuthenticated = true;
				}
				break;
		}

		return output;
	}

	public static void main(String args[]) {
		try {
			Server obj = new Server();
			SubjectsDatabase stub = (SubjectsDatabase) UnicastRemoteObject.exportObject(obj, 0);

			Registry reg = LocateRegistry.getRegistry();
			reg.bind("Subjects", stub);
			System.out.println("Server ready");
		} catch (Exception e) {
			System.err.println("Server exception: " + e.toString());
            e.printStackTrace();
		}
	}
}
