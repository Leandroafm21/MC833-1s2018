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
		int tryNumber;
		String teacherPassword;
		String dataToSend;
		String response = "0";

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
			Thread.sleep(1);
		}
		userType = up.getUserType();
		up.dispose();
		System.out.println("[DEBUG] User Type = " + userType);

		ResponseInterface ri = new ResponseInterface();

		tryNumber = 0;
		if (userType == 't') {
			while (Integer.parseInt(response) != 1) {
				System.out.println("Response = " + response);
				System.out.println(response != "SUCCESS");
				PasswordPrompt pp = new PasswordPrompt(tryNumber);
				while (pp.isVisible()) {
					Thread.sleep(1);
				}
				teacherPassword = pp.getTeacherPassword();
				pp.dispose();
				System.out.println("[DEBUG] Teacher Password = " + teacherPassword);
				try {
					response = stub.HandleCommand(userType + teacherPassword);
				} catch (Exception e) {
					System.err.println("Client exception: " + e.toString());
		            e.printStackTrace();
				}
				System.out.println("[DEBUG] Response Received = " + response);
			}
		} else {
			try {
				response = stub.HandleCommand(Character.toString(userType));
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
			dataToSend = mi.getData();
			if (dataToSend.charAt(0) == '1') {
				RegisterPrompt rp = new RegisterPrompt('s');
				while (rp.isVisible()) {
					Thread.sleep(1);
				}
				dataToSend = dataToSend + rp.getRawData();
			} else if (dataToSend.charAt(0) == '6') {
				RegisterPrompt rp = new RegisterPrompt('m');
				while (rp.isVisible()) {
					Thread.sleep(1);
				}
				dataToSend = dataToSend + rp.getRawData();
			} else if (dataToSend.charAt(0) == '8') {
				System.exit(1);
			}
			System.out.println("[DEBUG] Data to Send = " + dataToSend);
			Thread.sleep(2000);
			try {
				long t1 = System.nanoTime();
				response = stub.HandleCommand(dataToSend);
				long t2 = System.nanoTime();
				System.out.println("[DEBUG] Operation Time = " + (t2-t1)/1000 + " microseconds");
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
