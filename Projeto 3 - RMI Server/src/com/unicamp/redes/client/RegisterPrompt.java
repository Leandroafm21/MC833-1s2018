package com.unicamp.redes.client;

import java.awt.*;
import java.awt.event.*;

public class RegisterPrompt extends Frame implements ActionListener {
	private Label subjectCodeLabel;
	private TextField subjectCodeTextField;
	private Label subjectTitleLabel;
	private TextField subjectTitleTextField;
	private Label subjectSyllabusLabel;
	private TextField subjectSyllabusTextField;
	private Label subjectScheduleLabel;
	private TextField subjectScheduleTextField;
	private Label subjectMessageLabel;
	private TextField subjectMessageTextField;
	private Button submitButton;

	private char registerType;
	private String rawData;

	public RegisterPrompt(char type) {
		this.registerType = type;
		setLayout(new FlowLayout());

		if (registerType == 's') {
			subjectCodeLabel = new Label("subjectCode");
			subjectCodeLabel.setText("Codigo da disciplina:");
			add(subjectCodeLabel);
			subjectCodeTextField = new TextField(22);
			subjectCodeTextField.setEditable(true);
			add(subjectCodeTextField);
			
			subjectTitleLabel = new Label("subjectTitle");
			subjectTitleLabel.setText("Titulo da disciplina:");
			add(subjectTitleLabel);
			subjectTitleTextField = new TextField(22);
			subjectTitleTextField.setEditable(true);
			add(subjectTitleTextField);

			subjectSyllabusLabel = new Label("subjectSyllabus");
			subjectSyllabusLabel.setText("Ementa da disciplina:");
			add(subjectSyllabusLabel);
			subjectSyllabusTextField = new TextField(22);
			subjectSyllabusTextField.setEditable(true);
			add(subjectSyllabusTextField);

			subjectScheduleLabel = new Label("subjectSchedule");
			subjectScheduleLabel.setText("Horarios da disciplina:");
			add(subjectScheduleLabel);
			subjectScheduleTextField = new TextField(22);
			subjectScheduleTextField.setEditable(true);
			add(subjectScheduleTextField);

			setSize(225, 295);
		} else {
			subjectMessageLabel = new Label("subjectMessage");
			subjectMessageLabel.setText("Mensagem para a proxima aula:");
			add(subjectMessageLabel);
			subjectMessageTextField = new TextField(35);
			subjectMessageTextField.setEditable(true);
			add(subjectMessageTextField);

			setSize(300, 125);
		}

		submitButton = new Button("Ok");
		submitButton.addActionListener(this);
		add(submitButton);

		setTitle("Prompt");
		setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		boolean keepOpened = false;
		if (registerType == 's') {
			if (subjectCodeTextField.getText().length() != 5
				|| Character.isDigit(subjectCodeTextField.getText().charAt(2)) == false
				|| Character.isDigit(subjectCodeTextField.getText().charAt(3)) == false
				|| Character.isDigit(subjectCodeTextField.getText().charAt(4)) == false) {
				subjectCodeLabel.setText("Erro na formatacao!!!");
				subjectCodeLabel.setForeground(Color.RED);
				subjectCodeTextField.setText("CCDDD");
				try {
					Thread.sleep(5000);
				} catch (InterruptedException e2) {
					System.err.println("Main Interface exception: " + e2.toString());
					e2.printStackTrace();
				}
				subjectCodeLabel.setText("Entre com o codigo da disciplina:");
				subjectCodeLabel.setForeground(Color.BLACK);
				keepOpened = true;
			} else {
				rawData = subjectCodeTextField.getText() + '_' + subjectTitleTextField.getText() + '_' + subjectSyllabusTextField.getText() + '_' + subjectScheduleTextField.getText();
				subjectCodeTextField.setText("");
				subjectTitleTextField.setText("");
				subjectSyllabusTextField.setText("");
				subjectScheduleTextField.setText("");
			}
		} else {
			rawData = subjectMessageTextField.getText();
			subjectMessageTextField.setText("");
		}
		setVisible(keepOpened);
	}

	public String getRawData() {
		String rawDataToSend = rawData;
		rawData = null;
		return rawDataToSend;
	}
}
