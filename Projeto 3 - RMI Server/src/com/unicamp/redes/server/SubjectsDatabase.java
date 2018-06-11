package com.unicamp.redes.server;

import java.rmi.*;

public interface SubjectsDatabase extends Remote {
	String HandleAuthentication(String data) throws RemoteException;
	String HandleCommand(String data) throws RemoteException;
}
