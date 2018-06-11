package com.unicamp.redes.client;

import java.awt.*;
import java.awt.event.*;

public class MainInterface extends Frame implements ActionListener {
	private Label userOptionsLabel;
	private Choice userOptionsChoices;
	private Label subjectLabel;
	private TextField subjectTextField;
	private Button userOptionsButton;
	
	private String data;
	
	public MainInterface(char userType) {
		setLayout(new FlowLayout());
		
		userOptionsLabel = new Label("userOptions");
		if (userType == 't') {
			userOptionsLabel.setText("O que o(a) Sr(a). gostaria de fazer?");
		} else {
			userOptionsLabel.setText("O que você gostaria de fazer?");
		}
		add(userOptionsLabel);
		
		userOptionsChoices = new Choice();
		if (userType == 't') {
			userOptionsChoices.add("1-) Registrar Disciplina");
		}
		userOptionsChoices.add("2-) Listar Disciplinas");
		userOptionsChoices.add("3-) Exibir Ementa de Disciplina");
		userOptionsChoices.add("4-) Exibir Informações de Disciplina");
		userOptionsChoices.add("5-) Exibir Informações de todas as Disciplinas");
		if (userType == 't') {
			userOptionsChoices.add("6-) Escrever uma mensagem para uma Disciplina");
		}
		userOptionsChoices.add("7-) Ver a mensagem de uma Disciplina");
		userOptionsChoices.addItemListener(
			new ItemListener() {
				public void itemStateChanged(ItemEvent ie) {
					if (userOptionsChoices.getSelectedItem().charAt(0) == '3'
						|| userOptionsChoices.getSelectedItem().charAt(0) == '4'
						|| userOptionsChoices.getSelectedItem().charAt(0) == '6'
						|| userOptionsChoices.getSelectedItem().charAt(0) == '7') {
						subjectTextField.setEditable(true);
					}
					else {
						subjectTextField.setEditable(false);
					}
				}
			}
		);
		add(userOptionsChoices);
		
		subjectLabel = new Label("subject");
		subjectLabel.setText("Entre com o código da disciplina:");
		add(subjectLabel);
		
		subjectTextField = new TextField(12);
		subjectTextField.setEditable(false);
		add(subjectTextField);
		
		userOptionsButton = new Button("Ok");
		userOptionsButton.addActionListener(this);
		add(userOptionsButton);
		
		setTitle("Prompt");
		setSize(350, 150);
		setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) {
		if (!subjectTextField.getText().isEmpty()) {
			data = (char) ((int) userOptionsChoices.getSelectedItem().charAt(0)) + subjectTextField.getText();
		} else {
			data = Character.toString(userOptionsChoices.getSelectedItem().charAt(0));
		}
		subjectTextField.setText("");
		setVisible(false);
	}
	
	public String getData() {
		String dataToSend = data;
		data = null;
		return dataToSend;
	}
}
