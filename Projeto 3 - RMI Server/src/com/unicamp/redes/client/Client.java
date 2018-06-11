package com.unicamp.redes.client;

import java.rmi.registry.LocateRegistry;
import java.rmi.registry.Registry;

import com.unicamp.redes.server.SubjectsDatabase;

public class Client {
	
	private Client() {}

	public static void main(String args[]) throws InterruptedException {
		String host = (args.length < 1) ? null : args[0];
		Registry reg;
		SubjectsDatabase stub = null;
		char userType;
		String teacherPassword;
		String dataToSend;
		String response = null;
		
		try {
			reg = LocateRegistry.getRegistry(host);
			stub = (SubjectsDatabase) reg.lookup("Subjects");
		} catch (Exception e) {
			System.err.println("Client exception: " + e.toString());
            e.printStackTrace();
            System.exit(0);
		}
		
		UserTypePrompt up = new UserTypePrompt();
		while (up.isVisible()) {
			Thread.sleep(1000);
		}
		userType = up.getUserType();
		up.dispose();
		System.out.println("[DEBUG] User Type = " + userType);
		
		ResponseInterface ri = new ResponseInterface();
		
		if (userType == 't') {
			PasswordPrompt pp = new PasswordPrompt();
			while (pp.isVisible()) {
				Thread.sleep(1);
			}
			teacherPassword = pp.getTeacherPassword();
			pp.dispose();
			System.out.println("[DEBUG] Teacher Password = " + teacherPassword);
			try {
				response = stub.HandleAuthentication(userType + teacherPassword);
			} catch (Exception e) {
				System.err.println("Client exception: " + e.toString());
	            e.printStackTrace();
			}
			System.out.println("[DEBUG] Response Received = " + response);
		} else {
			try {
				response = stub.HandleAuthentication(Character.toString(userType));
			} catch (Exception e) {
				System.err.println("Client exception: " + e.toString());
	            e.printStackTrace();
			}
			System.out.println("[DEBUG] Response Received = " + response);
		}
			
		MainInterface mi = new MainInterface(userType);
		for ( ; ; ) {
			while (mi.isVisible()) {
				Thread.sleep(1);
			}
			/* Usuário deu "Ok" */
			dataToSend = mi.getData();
			System.out.println("[DEBUG] Data to Send = " + dataToSend);
			Thread.sleep(2000);
			try {
			    // Começar a contar tempo aqui
				response = stub.HandleCommand(dataToSend);
				// Terminar de contar tempo aqui
			} catch (Exception e) {
				System.err.println("Client exception: " + e.toString());
	            e.printStackTrace();
			}
			System.out.println("[DEBUG] Response Received = " + response);
			ri.showResponse(response);
			ri.setVisible(true);
			while (ri.isVisible()) {
				Thread.sleep(1);
			}
			mi.setVisible(true);
		}
	}
}
