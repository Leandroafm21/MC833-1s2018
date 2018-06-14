package com.unicamp.redes.server;

import java.rmi.*;

public interface SubjectsDatabase extends Remote {
	String HandleCommand(String data) throws RemoteException;
}
