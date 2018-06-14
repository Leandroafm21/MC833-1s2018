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
			userOptionsLabel.setText("O que voce gostaria de fazer?");
		}
		add(userOptionsLabel);

		userOptionsChoices = new Choice();
		if (userType == 't') {
			userOptionsChoices.add("1-) Registrar Disciplina");
		}
		userOptionsChoices.add("2-) Listar Disciplinas");
		userOptionsChoices.add("3-) Exibir Ementa de Disciplina");
		userOptionsChoices.add("4-) Exibir Informacoes de Disciplina");
		userOptionsChoices.add("5-) Exibir Informacoes de todas as Disciplinas");
		if (userType == 't') {
			userOptionsChoices.add("6-) Escrever uma mensagem para uma Disciplina");
		}
		userOptionsChoices.add("7-) Ver a mensagem de uma Disciplina");
		userOptionsChoices.add("8-) Sair");
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
		subjectLabel.setText("Entre com o codigo da disciplina:");
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
		boolean keepOpened = false;
		if (!subjectTextField.getText().isEmpty()) {
			if (subjectTextField.getText().length() != 5
				|| Character.isDigit(subjectTextField.getText().charAt(2)) == false
				|| Character.isDigit(subjectTextField.getText().charAt(3)) == false
				|| Character.isDigit(subjectTextField.getText().charAt(4)) == false) {
				subjectLabel.setText("Erro na formatacao!");
				subjectLabel.setForeground(Color.RED);
				subjectTextField.setText("CCDDD");
				try {
					Thread.sleep(5000);
				} catch (InterruptedException e2) {
					System.err.println("Main Interface exception: " + e2.toString());
					e2.printStackTrace();
				}
				subjectLabel.setText("Entre com o codigo da disciplina:");
				subjectLabel.setForeground(Color.BLACK);
				keepOpened = true;
			} else {
				data = (char) ((int) userOptionsChoices.getSelectedItem().charAt(0)) + subjectTextField.getText();
			}
		} else {
			data = Character.toString(userOptionsChoices.getSelectedItem().charAt(0));
		}
		subjectTextField.setText("");
		setVisible(keepOpened);
	}

	public String getData() {
		String dataToSend = data;
		data = null;
		return dataToSend;
	}
}
