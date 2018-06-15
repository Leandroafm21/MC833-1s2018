package com.unicamp.redes.server;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Server implements SubjectsDatabase {
	private static final String password = "1234";
	private Boolean isAuthenticated;

	public Server() {
		isAuthenticated = false;
	}

	public String HandleCommand(String data) throws RemoteException {
		String[] splitter;
		System.out.println("[DEBUG] Received data: " + data);
		String output = null;
		Disciplina disc;
		char op = data.charAt(0);
		System.out.println("[DEBUG] OP: " + op);
		
		long t1 = System.nanoTime();
		switch (op) {
			case '1':
				if (!isAuthenticated)
				{
					output = "Erro: Voce precisa estar autenticado para realizar esta operacao.";
				} else {
					splitter = data.substring(1).split("_");
					disc = new Disciplina(splitter[0], splitter[1], splitter[2]);
					Disciplina.AddToList(disc);
					output = "Disciplina adicionada com sucesso.";
				}
				break;
			case '2':
				output = Disciplina.ListSubjects();
				break;
			case '3':
				disc = Disciplina.GetByCodigo(data.substring(1));
				if (disc == null)
					output = "Erro: Codigo de disciplina invalido ou disciplina nao encontrada.";
				else
					output = disc.getEmenta();
				break;
			case '4':
				disc = Disciplina.GetByCodigo(data.substring(1));
				if (disc == null)
					output = "Erro: Codigo de disciplina invalido ou disciplina nao encontrada.";
				else
					output = disc.getInfo();
				break;
			case '5':
				output = Disciplina.GetInfoAll();
				break;
			case '6':
				if (!isAuthenticated)
				{
						output = "Erro: Voce precisa estar autenticado para realizar esta operacao.";
				} else {
						disc = Disciplina.GetByCodigo(data.substring(1,6));
						if (disc == null)
							output = "Erro: Codigo de disciplina invalido ou disciplina nao encontrada.";
						else {
							disc.AtualizaTextoAula(data.substring(6));
							output = "Mensagem inserida com sucesso.";
						}
				}
				break;
			case '7':
				disc = Disciplina.GetByCodigo(data.substring(1));
				if (disc == null)
					output = "Erro: Codigo de disciplina invalido ou disciplina nao encontrada.";
				else
					output = disc.getTextoAula();
				break;
			case 't':
				if (!data.substring(1).equals(password)) {
					output = "0";
				}
				else
				{
					output = "1";
					isAuthenticated = true;
				}
				break;
		}
		long t2 = System.nanoTime();
		System.out.println("[DEBUG] Database acessing time = " + (t2-t1)/1000 + " microseconds");

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
