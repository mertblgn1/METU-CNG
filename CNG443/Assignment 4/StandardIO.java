import java.io.*;
import java.util.ArrayList;
import java.util.Date;

/**
 * Write and read standard users
 */
public class StandardIO {
    public static void writeToFile(ArrayList<User> users) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new FileOutputStream("standard.dat"))) {
            // Extract the standard users from the users list
            ArrayList<Standard> standardUsers = new ArrayList<>();
            for (User user : users) {
                if (user instanceof Standard) {
                    standardUsers.add((Standard) user);
                }
            }

            // Write the number of users to the file
            dataOutputStream.writeInt(standardUsers.size());

            // Write each user's data to the file
            for (Standard standardUser : standardUsers) {
                dataOutputStream.writeInt(standardUser.getUserId());
                dataOutputStream.writeLong(standardUser.getDateOfBirth().getTime());
                dataOutputStream.writeUTF(standardUser.getFirstName());
                dataOutputStream.writeUTF(standardUser.getLastName());
                dataOutputStream.writeLong(standardUser.getRegistrationDate().getTime());
                dataOutputStream.writeUTF(standardUser.getPreferredPaymentMethod());
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static ArrayList<User> readFromFile() {
        ArrayList<User> standardUsers = new ArrayList<>();

        try (DataInputStream dataInputStream = new DataInputStream(new FileInputStream("standard.dat"))) {
            // Read the number of users from the file
            int numUsers = dataInputStream.readInt();

            // Read each user's data from the file
            for (int i = 0; i < numUsers; i++) {
                int userId = dataInputStream.readInt();
                long dobMillis = dataInputStream.readLong();
                String firstName = dataInputStream.readUTF();
                String lastName = dataInputStream.readUTF();
                long regDateMillis = dataInputStream.readLong();
                String preferredPaymentMethod = dataInputStream.readUTF();

                // Convert millis to Date
                Date dob = new Date(dobMillis);
                Date regDate = new Date(regDateMillis);

                standardUsers.add(new Standard(userId, dob, firstName, lastName, regDate, preferredPaymentMethod));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return standardUsers;
    }
}
