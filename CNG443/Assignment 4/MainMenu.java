import javax.swing.*;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.Map;
import java.util.Vector;

public class MainMenu extends JFrame {
    private static JFrame getUserDetailsFrame;
    private static JTextField userIdTextField;
    private static DefaultTableModel tableModel;
    private static JFrame getPropertyDetailsFrame;
    private static JFrame frame;
    private static JPanel radioPanel;

    public MainMenu() {
        createAndShowGUI();
    }

    public static void createAndShowGUI() {
        frame = new JFrame("BASIC");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());
        frame.getContentPane().setBackground(Color.MAGENTA);

        // Create and set up the menu bar
        JMenuBar menuBar = new JMenuBar();
        frame.setJMenuBar(menuBar);

        // Create the Color menu
        JMenu colorMenu = new JMenu("Color");
        menuBar.add(colorMenu);

        // Create menu items for different colors
        JMenuItem pinkMenuItem = new JMenuItem("Pink");
        pinkMenuItem.addActionListener(e -> setPanelColor(Color.MAGENTA));

        JMenuItem blueMenuItem = new JMenuItem("Blue");
        blueMenuItem.addActionListener(e -> setPanelColor(Color.BLUE));

        JMenuItem yellowMenuItem = new JMenuItem("Yellow");
        yellowMenuItem.addActionListener(e -> setPanelColor(Color.YELLOW));

        // Add menu items to the Color menu
        colorMenu.add(pinkMenuItem);
        colorMenu.add(blueMenuItem);
        colorMenu.add(yellowMenuItem);

        // Create the File menu
        JMenu fileMenu = new JMenu("File");
        menuBar.add(fileMenu);

        // Create menu item for choosing a file
        JMenuItem chooseFileMenuItem = new JMenuItem("Choose File");
        chooseFileMenuItem.addActionListener(e -> showFileChooser());
        fileMenu.add(chooseFileMenuItem);

        // Welcome label
        JLabel welcomeLabel = new JLabel("Welcome to BASIC (Bed And Breakfast In Cyprus)");
        welcomeLabel.setHorizontalAlignment(JLabel.CENTER);
        frame.add(welcomeLabel, BorderLayout.NORTH);

        // Panel to hold radio buttons
        radioPanel = new JPanel(new GridLayout(13, 1));
        radioPanel.setBackground(Color.MAGENTA);

        // Create a ButtonGroup to group the radio buttons
        ButtonGroup buttonGroup = new ButtonGroup();

        // Add the user options
        String[] options = {
                "Add user",
                "Delete user",
                "Get user details",
                "Add property",
                "Delete property",
                "Get property details",
                "Add booking",
                "Get booking information",
                "Get booking cost",
                "Add inspection",
                "List users",
                "List properties",
                "Compare properties by price per day"
        };

        for (String option : options) {
            JRadioButton radioButton = new JRadioButton(option);
            radioButton.setActionCommand(option);
            buttonGroup.add(radioButton);
            radioPanel.add(radioButton);
        }

        frame.add(new JScrollPane(radioPanel), BorderLayout.CENTER);

        // Submit button
        JButton submitButton = new JButton("Submit");
        submitButton.setBackground(Color.PINK);  // Set background color for the button
        submitButton.addActionListener(e -> {
            ButtonModel selectedButton = buttonGroup.getSelection();
            if (selectedButton != null) {
                String selectedOption = selectedButton.getActionCommand();
                if ("Add user".equals(selectedOption)) {
                    showAddUserFrame();
                }
                if ("Delete user".equals(selectedOption)) {
                    showDeleteUserFrame();
                }
                if ("Get user details".equals(selectedOption)) {
                    showGetUserDetailsFrame();
                }
                if ("Add property".equals(selectedOption)) {
                    showAddPropertyFrame();
                }
                if ("Delete property".equals(selectedOption)) {
                    showDeletePropertyFrame();
                }
                if ("Get property details".equals(selectedOption)) {
                    showGetPropertyDetailsFrame();
                }
                if ("Add booking".equals(selectedOption)) {
                    showAddBookingFrame();
                }
                if ("Get booking information".equals(selectedOption)) {
                    showGetBookingDetailsFrame();
                }
                if ("Get booking cost".equals(selectedOption)) {
                    showGetBookingCostFrame();
                }
                if ("Add inspection".equals(selectedOption)) {
                    showAddInspectionFrame();
                }
                if ("List users".equals(selectedOption)) {
                    showUserListFrame();
                }
                if ("List properties".equals(selectedOption)) {
                    showPropertyListFrame();
                }
                if ("Compare properties by price per day".equals(selectedOption)) {
                    showComparePricesFrame();
                }
            } else {
                JOptionPane.showMessageDialog(frame, "Please select an option");
            }
        });
        frame.add(submitButton, BorderLayout.SOUTH);

        frame.setSize(400, 500);
        frame.setLocationRelativeTo(null);
        frame.setVisible(true);
    }

    private static void showFileChooser() {
        JFileChooser fileChooser = new JFileChooser();
        FileNameExtensionFilter filter = new FileNameExtensionFilter("Text Files", "txt");
        fileChooser.setFileFilter(filter);

        int returnVal = fileChooser.showOpenDialog(frame);
        if (returnVal == JFileChooser.APPROVE_OPTION) {
            // User selected a file
            String selectedFile = fileChooser.getSelectedFile().getAbsolutePath();
            JOptionPane.showMessageDialog(frame, "Selected File: " + selectedFile);
        }
    }

    private static void setPanelColor(Color color) {
        frame.getContentPane().setBackground(color);
        radioPanel.setBackground(color);
    }

    private static void showAddPropertyFrame() {
        JFrame addPropertyFrame = new JFrame("Add Property");
        addPropertyFrame.setLayout(new GridLayout(0, 2));

        // Property type combobox
        String[] propertyTypes = {"Shared Property", "Full Property"};
        JComboBox<String> propertyTypeComboBox = new JComboBox<>(propertyTypes);
        addPropertyFrame.add(new JLabel("Property Type: "));
        addPropertyFrame.add(propertyTypeComboBox);

        // Number of bedrooms
        JTextField numberOfBedroomsTextField = new JTextField();
        addPropertyFrame.add(new JLabel("Number of bedrooms: "));
        addPropertyFrame.add(numberOfBedroomsTextField);

        // Number of rooms
        JTextField numberOfRoomsTextField = new JTextField();
        addPropertyFrame.add(new JLabel("Number of rooms: "));
        addPropertyFrame.add(numberOfRoomsTextField);

        // City
        JTextField cityTextField = new JTextField();
        addPropertyFrame.add(new JLabel("City: "));
        addPropertyFrame.add(cityTextField);

        // Price per day
        JTextField pricePerDayTextField = new JTextField();
        addPropertyFrame.add(new JLabel("Price per day: "));
        addPropertyFrame.add(pricePerDayTextField);

        // Host id
        JTextField hostIdTextField = new JTextField();
        addPropertyFrame.add(new JLabel("Host ID: "));
        addPropertyFrame.add(hostIdTextField);

        // Property Size
        JTextField sizeTextField = new JTextField();

        // Button
        JButton addPropertyButton = new JButton("Add Property");

        propertyTypeComboBox.addActionListener(e -> {
            // Clear the frame content before adding new components
            addPropertyFrame.getContentPane().removeAll();
            addPropertyFrame.setLayout(new GridLayout(0, 2)); // Set to 0 rows for dynamic rows
            addPropertyFrame.revalidate();
            addPropertyFrame.repaint();

            // Add the components again
            addPropertyFrame.add(new JLabel("Property Type: "));
            addPropertyFrame.add(propertyTypeComboBox);
            addPropertyFrame.add(new JLabel("Number of bedrooms: "));
            addPropertyFrame.add(numberOfBedroomsTextField);
            addPropertyFrame.add(new JLabel("Number of rooms: "));
            addPropertyFrame.add(numberOfRoomsTextField);
            addPropertyFrame.add(new JLabel("City: "));
            addPropertyFrame.add(cityTextField);
            addPropertyFrame.add(new JLabel("Price per day: "));
            addPropertyFrame.add(pricePerDayTextField);
            addPropertyFrame.add(new JLabel("Host ID: "));
            addPropertyFrame.add(hostIdTextField);

            String selectedType = (String) propertyTypeComboBox.getSelectedItem();

            if (selectedType.equals("Full Property")) {
                addPropertyFrame.add(new JLabel("Property Size:"));
                addPropertyFrame.add(sizeTextField);
            }

            addPropertyFrame.add(addPropertyButton);
            addPropertyFrame.revalidate();
            addPropertyFrame.repaint();
        });

        // Submit button for adding a property
        addPropertyButton.addActionListener(e -> {
            String propertyType = (String) propertyTypeComboBox.getSelectedItem();
            String noBedrooms = numberOfBedroomsTextField.getText();
            String noRooms = numberOfRoomsTextField.getText();
            String city = cityTextField.getText();
            double pricePerDay = Double.parseDouble(pricePerDayTextField.getText());
            String hostId = hostIdTextField.getText();

            if (noBedrooms.isEmpty() || noRooms.isEmpty() || city.isEmpty() || hostId.isEmpty()) {
                JOptionPane.showMessageDialog(addPropertyFrame, "Please fill in all the required fields", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                return;
            }

            if (propertyType.equals("Full Property")) {
                double size = Double.parseDouble(sizeTextField.getText());
                if (BASIC.addProperty(Integer.parseInt(noBedrooms), Integer.parseInt(noRooms), city, pricePerDay, Integer.parseInt(hostId), size)) {
                    JOptionPane.showMessageDialog(addPropertyButton, "Property added successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(addPropertyFrame, "Please enter a valid Host ID", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                }
            } else if (propertyType.equals("Shared Property")) {
                if (BASIC.addProperty(Integer.parseInt(noBedrooms), Integer.parseInt(noRooms), city, pricePerDay, Integer.parseInt(hostId))) {
                    JOptionPane.showMessageDialog(addPropertyButton, "Property added successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(addPropertyFrame, "Please enter a valid Host ID", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                }
            } else {
                JOptionPane.showMessageDialog(addPropertyFrame, "Some error has occurred", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                return;
            }

            // Close the add user frame
            addPropertyFrame.dispose();
        });

        addPropertyFrame.add(addPropertyButton);

        addPropertyFrame.setSize(300, 400);
        addPropertyFrame.setLocationRelativeTo(null);
        addPropertyFrame.setVisible(true);
    }

    private static void showAddBookingFrame() {
        JFrame addBookingFrame = new JFrame("Add booking");
        addBookingFrame.setLayout(new GridLayout(0, 2));

        // User id
        JTextField userIdTextField = new JTextField();
        addBookingFrame.add(new JLabel("User ID: "));
        addBookingFrame.add(userIdTextField);

        // Property id
        JTextField propertyIdTextField = new JTextField();
        addBookingFrame.add(new JLabel("Property ID: "));
        addBookingFrame.add(propertyIdTextField);

        // Start date
        JTextField startDateTextField = new JTextField();
        addBookingFrame.add(new JLabel("Start date (dd/mm/yyyy): "));
        addBookingFrame.add(startDateTextField);

        // End date
        JTextField endDateTextField = new JTextField();
        addBookingFrame.add(new JLabel("End date (dd/mm/yyyy): "));
        addBookingFrame.add(endDateTextField);

        JButton addBookingButton = new JButton("Add Booking");
        addBookingFrame.add(addBookingButton);
        addBookingButton.addActionListener(e -> {
            String userId = userIdTextField.getText();
            String propertyId = propertyIdTextField.getText();
            String startDate = startDateTextField.getText();
            String endDate = endDateTextField.getText();

            if (userId.isEmpty() || propertyId.isEmpty() || startDate.isEmpty() || endDate.isEmpty()) {
                JOptionPane.showMessageDialog(addBookingFrame, "Please fill in all the required fields", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                return;
            }

            if (BASIC.addBooking(Integer.parseInt(userId), Integer.parseInt(propertyId), startDate, endDate)) {
                JOptionPane.showMessageDialog(addBookingButton, "Booking added successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                addBookingFrame.dispose();
            } else {
                JOptionPane.showMessageDialog(addBookingFrame, "Property or user doesn't exist", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
            }
        });

        addBookingFrame.setSize(300, 400);
        addBookingFrame.setLocationRelativeTo(null);
        addBookingFrame.setVisible(true);
    }

    private static void showAddUserFrame() {
        JFrame addUserFrame = new JFrame("Add User");
        addUserFrame.setLayout(new GridLayout(0, 2));

        // User type combobox
        String[] userTypes = {"Gold Customer", "Standard Customer", "Host"};
        JComboBox<String> userTypeComboBox = new JComboBox<>(userTypes);
        addUserFrame.add(new JLabel("User Type: "));
        addUserFrame.add(userTypeComboBox);

        // Date of birth
        JTextField dobTextField = new JTextField();
        addUserFrame.add(new JLabel("Date of Birth (dd/mm/yyyy): "));
        addUserFrame.add(dobTextField);

        // First name
        JTextField firstNameTextField = new JTextField();
        addUserFrame.add(new JLabel("First Name: "));
        addUserFrame.add(firstNameTextField);

        // Last name
        JTextField lastNameTextField = new JTextField();
        addUserFrame.add(new JLabel("Last Name: "));
        addUserFrame.add(lastNameTextField);

        // Registration date
        JTextField regDateTextField = new JTextField();
        addUserFrame.add(new JLabel("Registration Date (dd/mm/yyyy): "));
        addUserFrame.add(regDateTextField);

        // Additional fields based on user type
        JComboBox<Integer> goldLevelComboBox = new JComboBox<>(new Integer[]{1, 2, 3});
        JTextField paymentMethodTextField = new JTextField();
        JTextField taxNumberTextField = new JTextField();

        addUserFrame.add(new JLabel("Preferred Payment Method: "));
        addUserFrame.add(paymentMethodTextField);
        addUserFrame.add(new JLabel("Gold Level: "));
        addUserFrame.add(goldLevelComboBox);

        JButton addUserButton = new JButton("Add User");

        userTypeComboBox.addActionListener(e -> {
            // Clear the frame content before adding new components
            addUserFrame.getContentPane().removeAll();
            addUserFrame.setLayout(new GridLayout(0, 2)); // Set to 0 rows for dynamic rows
            addUserFrame.revalidate();
            addUserFrame.repaint();

            // Add the common components
            addUserFrame.add(new JLabel("User Type: "));
            addUserFrame.add(userTypeComboBox);
            addUserFrame.add(new JLabel("Date of Birth (dd/mm/yyyy):"));
            addUserFrame.add(dobTextField);
            addUserFrame.add(new JLabel("First Name:"));
            addUserFrame.add(firstNameTextField);
            addUserFrame.add(new JLabel("Last Name:"));
            addUserFrame.add(lastNameTextField);
            addUserFrame.add(new JLabel("Registration Date (dd/mm/yyyy):"));
            addUserFrame.add(regDateTextField);

            String selectedType = (String) userTypeComboBox.getSelectedItem();

            switch (selectedType) {
                case "Gold Customer":
                    addUserFrame.add(new JLabel("Preferred Payment Method: "));
                    addUserFrame.add(paymentMethodTextField);
                    addUserFrame.add(new JLabel("Gold Level: "));
                    addUserFrame.add(goldLevelComboBox);
                    break;
                case "Standard Customer":
                    addUserFrame.add(new JLabel("Preferred Payment Method: "));
                    addUserFrame.add(paymentMethodTextField);
                    break;
                case "Host":
                    addUserFrame.add(new JLabel("Tax Number:"));
                    addUserFrame.add(taxNumberTextField);
                    break;
            }
            addUserFrame.add(addUserButton);

            addUserFrame.revalidate();
            addUserFrame.repaint();
        });

        // Submit button for adding a user
        addUserButton.addActionListener(e -> {
            String userType = (String) userTypeComboBox.getSelectedItem();
            String dob = dobTextField.getText();
            String firstName = firstNameTextField.getText();
            String lastName = lastNameTextField.getText();
            String regDate = regDateTextField.getText();

            if (dob.isEmpty() || firstName.isEmpty() || lastName.isEmpty() || regDate.isEmpty()) {
                JOptionPane.showMessageDialog(addUserFrame, "Please fill in all the required fields", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                return;
            }

            if (userType != null) {
                switch (userType) {
                    case "Gold Customer":
                        String paymentMethodGold = paymentMethodTextField.getText();
                        int goldLevel = (Integer) goldLevelComboBox.getSelectedItem();
                        if (!BASIC.addUser(dob, firstName, lastName, regDate, paymentMethodGold, goldLevel)) {
                            JOptionPane.showMessageDialog(addUserFrame, "Wrong format. Please enter the dates correctly", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                            return;
                        }
                        break;
                    case "Standard Customer":
                        String paymentMethodStandard = paymentMethodTextField.getText();
                        if (!BASIC.addUser(dob, firstName, lastName, regDate, paymentMethodStandard)) {
                            JOptionPane.showMessageDialog(addUserFrame, "Wrong format. Please enter the dates correctly", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                            return;
                        }
                        break;
                    case "Host":
                        double taxNumber = Double.parseDouble(taxNumberTextField.getText());
                        if (!BASIC.addUser(dob, firstName, lastName, regDate, taxNumber)) {
                            JOptionPane.showMessageDialog(addUserFrame, "Wrong format. Please enter the dates correctly", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                            return;
                        }
                        break;
                }
            }

            JOptionPane.showMessageDialog(addUserFrame, "User added successfully", "Success", JOptionPane.INFORMATION_MESSAGE);

            // Close the add user frame
            addUserFrame.dispose();
        });

        addUserFrame.add(addUserButton);

        addUserFrame.setSize(300, 400);
        addUserFrame.setLocationRelativeTo(null);
        addUserFrame.setVisible(true);
    }

    private static void showDeletePropertyFrame() {
        JFrame deletePropertyFrame = new JFrame("Delete Property");
        deletePropertyFrame.setLayout(new GridLayout(3, 1));

        JTextField propertyIdTextField = new JTextField();
        JButton deletePropertyButton = new JButton("Delete");

        deletePropertyFrame.add(new JLabel("Enter Property ID to delete: "));
        deletePropertyFrame.add(propertyIdTextField);
        deletePropertyFrame.add(deletePropertyButton);

        deletePropertyButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String propertyIdText = propertyIdTextField.getText();
                if (propertyIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(deletePropertyFrame, "Please enter a Property ID", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int propertyId = Integer.parseInt(propertyIdText);

                if (BASIC.deleteProperty(propertyId)) {
                    JOptionPane.showMessageDialog(deletePropertyFrame, "Property deleted successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                    deletePropertyFrame.dispose();
                } else {
                    JOptionPane.showMessageDialog(deletePropertyFrame, "Please enter a correct Property ID", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        deletePropertyFrame.setSize(300, 150);
        deletePropertyFrame.setLocationRelativeTo(null);
        deletePropertyFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        deletePropertyFrame.setVisible(true);
    }

    private static void showDeleteUserFrame() {
        JFrame deleteUserFrame = new JFrame("Delete User");
        deleteUserFrame.setLayout(new GridLayout(3, 1));

        JTextField userIdTextField = new JTextField();
        JButton deleteUserButton = new JButton("Delete");

        deleteUserFrame.add(new JLabel("Enter User ID to delete: "));
        deleteUserFrame.add(userIdTextField);
        deleteUserFrame.add(deleteUserButton);

        deleteUserButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userIdText = userIdTextField.getText();
                if (userIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(deleteUserFrame, "Please enter a User ID", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int userId = Integer.parseInt(userIdTextField.getText());

                if (BASIC.deleteUser(userId)) {
                    JOptionPane.showMessageDialog(deleteUserFrame, "User deleted successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                    deleteUserFrame.dispose();
                } else {
                    JOptionPane.showMessageDialog(deleteUserFrame, "Please enter a correct User ID", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        deleteUserFrame.setSize(300, 150);
        deleteUserFrame.setLocationRelativeTo(null);
        deleteUserFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        deleteUserFrame.setVisible(true);
    }

    private static void showGetPropertyDetailsFrame() {
        getPropertyDetailsFrame = new JFrame("Property Details");
        getPropertyDetailsFrame.setLayout(new BorderLayout());

        JPanel inputPanel = new JPanel(new FlowLayout());
        JTextField propertyIdTextField = new JTextField(10);
        JButton getPropertyDetailsButton = new JButton("Get the details");
        inputPanel.add(new JLabel("Enter Property ID: "));
        inputPanel.add(propertyIdTextField);
        inputPanel.add(getPropertyDetailsButton);

        tableModel = new DefaultTableModel();
        JTable propertyDetailsTable = new JTable(tableModel);
        JScrollPane tableScrollPane = new JScrollPane(propertyDetailsTable);

        getPropertyDetailsFrame.add(inputPanel, BorderLayout.NORTH);
        getPropertyDetailsFrame.add(tableScrollPane, BorderLayout.CENTER);

        getPropertyDetailsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String propertyIdText = propertyIdTextField.getText();
                if (propertyIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(getUserDetailsFrame, "Please enter a User ID", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int propertyId = Integer.parseInt(propertyIdText);
                updatePropertyDetailsTable(propertyId);
            }
        });

        getPropertyDetailsFrame.setSize(500, 300);
        getPropertyDetailsFrame.setLocationRelativeTo(null);
        getPropertyDetailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getPropertyDetailsFrame.setVisible(true);
    }

    private static void showGetBookingDetailsFrame() {
        JFrame getBookingDetailsFrame = new JFrame("Booking Details");
        getBookingDetailsFrame.setLayout(new BorderLayout());

        JPanel inputPanel = new JPanel(new FlowLayout());
        JTextField userIdTextField = new JTextField(10);
        JButton getBookingDetailsButton = new JButton("Get the details");
        inputPanel.add(new JLabel("Enter User ID: "));
        inputPanel.add(userIdTextField);
        inputPanel.add(getBookingDetailsButton);

        tableModel = new DefaultTableModel();
        JTable bookingDetailsTable = new JTable(tableModel);
        JScrollPane tableScrollPane = new JScrollPane(bookingDetailsTable);

        getBookingDetailsFrame.add(inputPanel, BorderLayout.NORTH);
        getBookingDetailsFrame.add(tableScrollPane, BorderLayout.CENTER);

        getBookingDetailsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userIdText = userIdTextField.getText();
                if (userIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(getUserDetailsFrame, "Please enter a User ID", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int userId = Integer.parseInt(userIdText);
                updateBookingDetailsTable(userId);
            }
        });

        getBookingDetailsFrame.setSize(500, 300);
        getBookingDetailsFrame.setLocationRelativeTo(null);
        getBookingDetailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getBookingDetailsFrame.setVisible(true);
    }

    private static void showAddInspectionFrame() {
        JFrame addInspectionFrame = new JFrame("Add Inspection");
        addInspectionFrame.setLayout(new GridLayout(4, 2, 5, 5)); // 4 rows, 2 columns, horizontal and vertical gaps

        // Property ID
        JTextField propertyIdTextField = new JTextField();
        addInspectionFrame.add(new JLabel("Property ID: "));
        addInspectionFrame.add(propertyIdTextField);

        // Inspection TextArea
        JTextArea inspectionTextArea = new JTextArea(5, 20);
        JScrollPane inspectionScrollPane = new JScrollPane(inspectionTextArea);
        addInspectionFrame.add(new JLabel("Inspection: "));
        addInspectionFrame.add(inspectionScrollPane);

        // Submit button for adding an inspection
        JButton addInspectionButton = new JButton("Add Inspection");

        addInspectionButton.addActionListener(e -> {
            String propertyId = propertyIdTextField.getText();
            String inspection = inspectionTextArea.getText();

            if (propertyId.isEmpty() || inspection.isEmpty()) {
                JOptionPane.showMessageDialog(addInspectionFrame, "Please fill in all the required fields", "Incomplete Form", JOptionPane.WARNING_MESSAGE);
                return;
            }

            if (BASIC.addInspectionToProperty(Integer.parseInt(propertyId), inspection)) {
                JOptionPane.showMessageDialog(addInspectionButton, "Inspection added successfully", "Success", JOptionPane.INFORMATION_MESSAGE);
                // Close the add inspection frame
                addInspectionFrame.dispose();
            } else {
                JOptionPane.showMessageDialog(addInspectionFrame, "Property doesn't exist or there is an inspection for this date already", "Error", JOptionPane.WARNING_MESSAGE);
            }
        });

        // Add the button at the bottom
        addInspectionFrame.add(addInspectionButton);

        addInspectionFrame.setSize(400, 300);
        addInspectionFrame.setLocationRelativeTo(null);
        addInspectionFrame.setVisible(true);
    }

    private static void showComparePricesFrame() {
        JFrame comparePricesFrame = new JFrame("Compare Prices");
        comparePricesFrame.setLayout(new GridLayout(3,1));

        JTextField property1TextField = new JTextField();
        comparePricesFrame.add(new JLabel("Property1 ID: "));
        comparePricesFrame.add(property1TextField);

        JTextField property2TextField = new JTextField();
        comparePricesFrame.add(new JLabel("Property2 ID: "));
        comparePricesFrame.add(property2TextField);

        JButton compareButton = new JButton("Compare");
        compareButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String property1IdText = property1TextField.getText();
                String property2IdText = property2TextField.getText();

                if (property1IdText.isEmpty() || property2IdText.isEmpty()) {
                    JOptionPane.showMessageDialog(getUserDetailsFrame, "Please fill all the required fields", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int property1Id = Integer.parseInt(property1IdText);
                int property2Id = Integer.parseInt(property2IdText);
                int result = BASIC.comparePropertyPricesPerDay(property1Id, property2Id);
                String message = "";

                if (result == 2) {
                    message = "Property with ID " + property1Id + " is more expensive than Property with ID " + property2Id;
                } else if (result == 0) {
                    message = "They have the same price";
                } else if (result == 1) {
                    message = "Property with ID" + property2Id + "is more expensive than Property with ID " + property1Id;
                } else {
                    JOptionPane.showMessageDialog(getUserDetailsFrame, "Property doesn't exist", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                JOptionPane.showMessageDialog(comparePricesFrame, message, "Success", JOptionPane.INFORMATION_MESSAGE);
            }
        });

        comparePricesFrame.add(compareButton);

        comparePricesFrame.setSize(300, 400);
        comparePricesFrame.setLocationRelativeTo(null);
        comparePricesFrame.setVisible(true);
    }

    private static void showGetBookingCostFrame() {
        JFrame getBookingCostFrame = new JFrame("Booking Cost");
        getBookingCostFrame.setLayout(new GridLayout(3, 1));

        JTextField userIdTextField = new JTextField(10);
        getBookingCostFrame.add(new JLabel("Enter user ID: "));
        getBookingCostFrame.add(userIdTextField);

        JTextField propertyIdTextField = new JTextField(10);
        getBookingCostFrame.add(new JLabel("Enter property ID"));
        getBookingCostFrame.add(propertyIdTextField);

        JButton getCostButton = new JButton("Get Cost");
        getCostButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userIdText = userIdTextField.getText();
                String propertyIdText = propertyIdTextField.getText();
                if (userIdText.isEmpty() || propertyIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(getBookingCostFrame, "Please fill all the required fields", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int userId = Integer.parseInt(userIdText);
                int propertyId = Integer.parseInt(propertyIdText);
                double cost = BASIC.getBookingCost(userId, propertyId);

                if (cost != -1) {
                    JOptionPane.showMessageDialog(getBookingCostFrame, "The total cost is " + cost, "Success", JOptionPane.INFORMATION_MESSAGE);
                } else {
                    JOptionPane.showMessageDialog(getBookingCostFrame, "There is no booking", "Error", JOptionPane.ERROR_MESSAGE);
                }

            }
        });
        getBookingCostFrame.add(getCostButton);

        getBookingCostFrame.setSize(300, 400);
        getBookingCostFrame.setLocationRelativeTo(null);
        getBookingCostFrame.setVisible(true);
    }

    private static void showGetUserDetailsFrame() {
        getUserDetailsFrame = new JFrame("User Details");
        getUserDetailsFrame.setLayout(new BorderLayout());

        JPanel inputPanel = new JPanel(new FlowLayout());
        userIdTextField = new JTextField(10);
        JButton getUserDetailsButton = new JButton("Get the details");
        inputPanel.add(new JLabel("Enter User ID: "));
        inputPanel.add(userIdTextField);
        inputPanel.add(getUserDetailsButton);

        tableModel = new DefaultTableModel();
        JTable userDetailsTable = new JTable(tableModel);
        JScrollPane tableScrollPane = new JScrollPane(userDetailsTable);

        getUserDetailsFrame.add(inputPanel, BorderLayout.NORTH);
        getUserDetailsFrame.add(tableScrollPane, BorderLayout.CENTER);

        getUserDetailsButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String userIdText = userIdTextField.getText();
                if (userIdText.isEmpty()) {
                    JOptionPane.showMessageDialog(getUserDetailsFrame, "Please enter a User ID", "Error", JOptionPane.ERROR_MESSAGE);
                    return;
                }

                int userId = Integer.parseInt(userIdText);
                // Get the details
                updateUserDetailsTable(userId);
            }
        });

        getUserDetailsFrame.setSize(500, 300);
        getUserDetailsFrame.setLocationRelativeTo(null);
        getUserDetailsFrame.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        getUserDetailsFrame.setVisible(true);
    }

    private static void updatePropertyDetailsTable(int propertyId) {
        // Clear existing data
        tableModel.setColumnCount(0);
        tableModel.setRowCount(0);

        // Add columns
        String[] columns = {"Property ID", "No Bedrooms", "No Rooms", "City", "Price per day", "Inspections"};
        for (String column : columns) {
            tableModel.addColumn(column);
        }

        Property property = BASIC.getPropertyById(propertyId);

        // Add property details to the table
        if (property != null) {
            Vector<Object> rowData = new Vector<>();
            rowData.add(property.getPropertyId());
            rowData.add(property.getNoBedRooms());
            rowData.add(property.getNoRooms());
            rowData.add(property.getCity());
            rowData.add(property.getPricePerDay());

            // Format inspections
            Map<Date, String> inspections = property.getInspections();
            StringBuilder inspectionsText = new StringBuilder();

            for (Map.Entry<Date, String> entry : inspections.entrySet()) {
                inspectionsText.append(formatDate(entry.getKey())).append(": ").append(entry.getValue()).append("\n");
            }

            rowData.add(inspectionsText.toString());

            if (property instanceof FullProperty) {
                rowData.add("Size: " + ((FullProperty) property).getPropertySize());
            }

            tableModel.addRow(rowData);
        } else {
            JOptionPane.showMessageDialog(getPropertyDetailsFrame, "Property not found", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }


    private static void updateBookingDetailsTable(int userId) {
        // Clear existing data
        tableModel.setColumnCount(0);
        tableModel.setRowCount(0);

        // Add columns
        String[] columns = {"Start Date", "End Date", "Is Paid"};
        for (String column: columns) {
            tableModel.addColumn(column);
        }

        ArrayList<Booking> bookings = BASIC.getUserBooking(userId);

        if (bookings != null) {
            for (Booking booking : bookings) {
                // Add a row for each booking
                Object[] rowData = {
                        formatDate(booking.getStartDate()),
                        formatDate(booking.getEndDate()),
                        booking.isPaid()
                };
                tableModel.addRow(rowData);
            }
        } else {
            JOptionPane.showMessageDialog(getPropertyDetailsFrame, "User not found or doesn't have any bookings", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private static void showPropertyListFrame() {
        JFrame propertyListFrame = new JFrame("Property List");

        // Column names
        String[] columnNames = {"Property ID", "No Bedrooms", "No Rooms", "City", "Price per day", "Inspections"};

        // Create JTable with property data and column names
        DefaultTableModel model = new DefaultTableModel(columnNames, 0);
        JTable propertyTable = new JTable(model);

        // Populate the table with property data
        for (Property property: BASIC.properties) {
            // Format inspections
            Map<Date, String> inspections = property.getInspections();
            StringBuilder inspectionsText = new StringBuilder();

            for (Map.Entry<Date, String> entry : inspections.entrySet()) {
                inspectionsText.append(formatDate(entry.getKey())).append(": ").append(entry.getValue()).append("\n");
            }

            model.addRow(new Object[]{property.getPropertyId(), property.getNoBedRooms(), property.getNoRooms(), property.getCity(), property.getPricePerDay(), inspectionsText.toString()});
        }

        // Set up layout
        JScrollPane scrollPane = new JScrollPane(propertyTable);
        propertyListFrame.getContentPane().add(scrollPane, BorderLayout.CENTER);

        propertyListFrame.setSize(600, 400);
        propertyListFrame.setLocationRelativeTo(null);
        propertyListFrame.setVisible(true);
    }

    private static void showUserListFrame() {
        JFrame userListFrame = new JFrame("User List");

        // Column names
        String[] columnNames = {"User ID", "Birthday", "First Name", "Last Name", "Registration Date"};

        // Create JTable with user data and column names
        DefaultTableModel model = new DefaultTableModel(columnNames, 0);
        JTable userTable = new JTable(model);

        // Populate the table with user data
        for (User user : BASIC.users) {
            model.addRow(new Object[]{user.getUserId(), formatDate(user.getDateOfBirth()), user.getFirstName(), user.getLastName(), formatDate(user.getRegistrationDate())});
        }

        // Set up layout
        JScrollPane scrollPane = new JScrollPane(userTable);
        userListFrame.getContentPane().add(scrollPane, BorderLayout.CENTER);

        userListFrame.setSize(600, 400);
        userListFrame.setLocationRelativeTo(null);
        userListFrame.setVisible(true);
    }

    private static void updateUserDetailsTable(int userId) {
        // Clear existing data
        tableModel.setColumnCount(0);
        tableModel.setRowCount(0);

        // Add columns
        String[] columns = {"User ID", "Birthday", "First Name", "Last Name", "Registration Date", "Details"};
        for (String column: columns) {
            tableModel.addColumn(column);
        }

        User user = null;
        for (User foundUser: BASIC.users) {
            if (foundUser.getUserId() == userId) {
                user = foundUser;
            }
        }

        // Add user details to the table
        if (user != null) {
            Vector<Object> rowData = new Vector<>();
            rowData.add(user.getUserId());
            rowData.add(formatDate(user.getDateOfBirth()));
            rowData.add(user.getFirstName());
            rowData.add(user.getLastName());
            rowData.add(formatDate(user.getRegistrationDate()));

            if (user instanceof Host) {
                rowData.add("Tax Number: " + ((Host) user).getTaxNumber());
            } else if (user instanceof Gold) {
                rowData.add("Gold Level: " + ((Gold) user).getGoldLevel());
                rowData.add("Preferred Payment Method: " + ((Gold) user).getPreferredPaymentMethod());
            } else if (user instanceof Standard) {
                rowData.add("Preferred Payment Method: " + ((Standard) user).getPreferredPaymentMethod());
            }

            tableModel.addRow(rowData);
        } else {
            JOptionPane.showMessageDialog(getUserDetailsFrame, "User not found", "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    private static String formatDate(java.util.Date date) {
        SimpleDateFormat dateFormat = new SimpleDateFormat("dd/MM/yyyy");
        return dateFormat.format(date);
    }

    public static void showModificationWarningDialog() {
        SwingUtilities.invokeLater(() -> {
            JOptionPane.showMessageDialog(null,
                    "WARNING: User data has been modified.",
                    "Data Modification Warning",
                    JOptionPane.WARNING_MESSAGE);
        });
    }
}
