package com.unicamp.redes.client;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class ResponseInterface extends Frame implements ActionListener {
	private Label responseLabel;
	private JTextArea responseTextArea;
	private Button responseButton;
	
	public ResponseInterface() {
		setLayout(new FlowLayout());
		
		responseLabel = new Label("response");
		responseLabel.setText("Resposta do Servidor:");
		add(responseLabel);
		
		responseTextArea = new JTextArea();
		responseTextArea.setEditable(false);
		responseTextArea.setLineWrap(true);
		responseTextArea.setWrapStyleWord(true);
		responseTextArea.setColumns(40);
		responseTextArea.setRows(20);
		add(responseTextArea);
		
		responseButton = new Button("Ok");
		responseButton.addActionListener(this);
		add(responseButton);
		
		setTitle("Prompt");
		setSize(475, 425);
	}
	
	public void showResponse(String response) {
		responseTextArea.setText(response);
	}
	
	public void actionPerformed(ActionEvent e) {
		responseTextArea.setText("");
		setVisible(false);
	}
}
