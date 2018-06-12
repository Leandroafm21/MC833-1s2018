package com.unicamp.redes.client;

import java.awt.*;
import java.awt.event.*;

public class RegisterPrompt extends Frame implements ActionListener {
	private Label subjectCodeLabel;
	private TextField subjectCodeTextField;
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
			subjectCodeLabel.setText("Código da disciplina:");
			add(subjectCodeLabel);
			subjectCodeTextField = new TextField(22);
			subjectCodeTextField.setEditable(true);
			add(subjectCodeTextField);
			
			subjectSyllabusLabel = new Label("subjectSyllabus");
			subjectSyllabusLabel.setText("Ementa da disciplina:");
			add(subjectSyllabusLabel);
			subjectSyllabusTextField = new TextField(22);
			subjectSyllabusTextField.setEditable(true);
			add(subjectSyllabusTextField);
			
			subjectScheduleLabel = new Label("subjectSchedule");
			subjectScheduleLabel.setText("Horários da disciplina:");
			add(subjectScheduleLabel);
			subjectScheduleTextField = new TextField(22);
			subjectScheduleTextField.setEditable(true);
			add(subjectScheduleTextField);
			
			setSize(225, 240);
		} else {
			subjectMessageLabel = new Label("subjectMessage");
			subjectMessageLabel.setText("Mensagem para a próxima aula:");
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
		if (registerType == 's') {
			rawData = subjectCodeTextField.getText() + '_' + subjectSyllabusTextField.getText() + '_' + subjectScheduleTextField.getText();
			subjectCodeTextField.setText("");
			subjectSyllabusTextField.setText("");
			subjectScheduleTextField.setText("");
		} else {
			rawData = subjectMessageTextField.getText();
			subjectMessageTextField.setText("");
		}
		setVisible(false);
	}
	
	public String getRawData() {
		String rawDataToSend = rawData;
		rawData = null;
		return rawDataToSend;
	}
}
