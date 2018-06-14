package com.unicamp.redes.client;

import java.awt.*;
import java.awt.event.*;

public class PasswordPrompt extends Frame implements ActionListener {
	private Label passwordLabel;
	private TextField passwordTextField;
	private Button passwordButton;
	
	private String teacherPassword;
	
	public PasswordPrompt(int tryNumber) {
		setLayout(new FlowLayout());
		
		passwordLabel = new Label("password");
		passwordLabel.setText("Entre com sua senha:");
		add(passwordLabel);
		
		passwordTextField = new TextField(22);
		if (tryNumber > 0) {
			passwordTextField.setText("Senha errada, tente novamente!");
		}
		add(passwordTextField);
		
		passwordButton = new Button("Ok");
		passwordButton.addActionListener(this);
		add(passwordButton);
		
		setTitle("Prompt");
		setSize(200, 125);
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		String enteredPassword = passwordTextField.getText();
		teacherPassword = enteredPassword;
		setVisible(false);
	}
	
	public String getTeacherPassword() {
		return teacherPassword;
	}
}
