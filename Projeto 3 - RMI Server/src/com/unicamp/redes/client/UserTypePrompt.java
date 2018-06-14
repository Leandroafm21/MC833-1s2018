package com.unicamp.redes.client;

import java.awt.*;
import java.awt.event.*;

public class UserTypePrompt extends Frame implements ActionListener {
	private Label userTypeLabel;
	private CheckboxGroup userTypeCheckbox;
	private Button userTypeButton;

	private char userType;

	public UserTypePrompt() {
		setLayout(new FlowLayout());

		userTypeLabel = new Label("userType");
		userTypeLabel.setText("Que tipo de usuario voce e?");
		add(userTypeLabel);

		userTypeCheckbox = new CheckboxGroup();
		add(new Checkbox("Estudante", userTypeCheckbox, true));
		add(new Checkbox("Professor", userTypeCheckbox, false));

		userTypeButton = new Button("Ok");
		userTypeButton.addActionListener(this);
		add(userTypeButton);

		setTitle("Prompt");
		setSize(200, 125);
		setVisible(true);
	}

	public void actionPerformed(ActionEvent e) {
		String selectedOption = userTypeCheckbox.getSelectedCheckbox().getLabel();
		if (selectedOption == "Estudante") {
			userType = 's';
		} else {
			userType = 't';
		}
		setVisible(false);
	}

	public char getUserType() {
		return userType;
	}
}
