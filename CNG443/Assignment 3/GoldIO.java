import java.io.*;
import java.util.ArrayList;
import java.util.Date;

/**
 * Write and read Gold users
 */
public class GoldIO {
    public static void writeToFile(ArrayList<User> users) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new FileOutputStream("gold.dat"))) {
            // Extract the gold users from the users list
            ArrayList<Gold> goldUsers = new ArrayList<>();
            for (User user : users) {
                if (user instanceof Gold) {
                    goldUsers.add((Gold) user);
                }
            }

            // Write the number of users to the file
            dataOutputStream.writeInt(goldUsers.size());

            // Write each user's data to the file
            for (Gold goldUser : goldUsers) {
                dataOutputStream.writeInt(goldUser.getUserId());
                dataOutputStream.writeLong(goldUser.getDateOfBirth().getTime());
                dataOutputStream.writeUTF(goldUser.getFirstName());
                dataOutputStream.writeUTF(goldUser.getLastName());
                dataOutputStream.writeLong(goldUser.getRegistrationDate().getTime());
                dataOutputStream.writeUTF(goldUser.getPreferredPaymentMethod());
                dataOutputStream.writeInt(goldUser.getGoldLevel());
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }

    public static ArrayList<User> readFromFile() {
        ArrayList<User> goldUsers = new ArrayList<>();

        try (DataInputStream dataInputStream = new DataInputStream(new FileInputStream("gold.dat"))) {
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

                int goldLevel = dataInputStream.readInt();
                goldUsers.add(new Gold(userId, dob, firstName, lastName, regDate, preferredPaymentMethod, goldLevel));
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
        return goldUsers;
    }
}
