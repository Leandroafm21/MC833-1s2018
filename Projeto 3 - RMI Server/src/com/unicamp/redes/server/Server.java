package com.unicamp.redes.server;

import java.rmi.registry.Registry;
import java.rmi.registry.LocateRegistry;
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;

public class Server implements SubjectsDatabase {
	
	public Server() {}

	public String HandleAuthentication(String data) throws RemoteException {
		System.out.println("Received data: " + data);
		return "Authentication";
	}
	
	public String HandleCommand(String data) throws RemoteException {
		System.out.println("Received data: " + data);
		String output = null;
		
		char op = data.charAt(0);
		switch (op) {
			case '1':
				output = "Register Subjects";
				break;
			case '2':
				output = "List Subjects";
				break;
			case '3':
				output = "Syllabus Subject";
				break;
			case '4':
				output = "Info Subject";
				break;
			case '5':
				output = "Info All";
				break;
			case '6':
				output = "Message Subject";
				break;
			case '7':
				output = "Next Subject";
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
